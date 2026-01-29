// đầu tiên là include Game.h vào và SDL cùng với iostream , và cmath để dùng std::abs (free funciton)

// nếu mà đã include trong header thì còn cần phải include trong .cpp nữa không , vậy một số thư viện chỉ dùng trong cpp có include vào header xong không phải include trong cpp nữsa?

// cái này thì có gì khác với "Pong.h"
#include <Pong.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
// thư viện xây dựng tiêu chuẩn tự -I
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>

// hàm khởi tạo constructor :để khởi tạo các biến thành viên (các chỉ số của chúng) không phải gán mà là đi kèm khi sinh ra luôn
Pong::Pong() : // window : min max
               MaxWindowH(1000),
               MinWindowH(0),
               MaxWindowW(1000),
               MinWindowW(0),
               // ball: size , position , speed
               ballSize(30),
               ballVelX(700.0f),
               ballVelY(700.0f),
               ballX(MaxWindowW / 2),
               ballY(MaxWindowH / 2),
               // paddle: size, position, speed
               paddleH(100),
               paddleW(20),
               paddleLeftX(MinWindowW + 10),
               paddleLeftY(MinWindowH + 10),
               paddleRightX(MaxWindowW - 10 - paddleW),
               paddleRightY(MinWindowH + 10),
               paddleSpeed(1000.0f),
               // pointer: được thiết lập là trống nghĩa là chưa chứa địa chỉ nào ở thời điểm hiện tại , và ngăn chặn hành vi bất thương xảy ra với hàm hủy diệt (destructor)
               window(nullptr),
               renderer(nullptr),
               font(nullptr),
               menuText(nullptr),
               gameOverText(nullptr),
               // loop control: đúng khi mà khởi tạo thành công "tờ giấy" + "cây chổi cọ"
               running(false),
               // màn hình hiện tại
               currentScreen(Screen::MENU),
               // bóng bị đóng băng
               ballFrozen(true),
               // vợt bị đóng băng
               paddleFroze(false),
               // điểm
               rightScore(0),
               leftScore(0),
               // tạo biến kiểm soát : làm chậm trước khi nhảy sang thua
               endDelay(false) // cái y/n trì hoãn đồng hồ chưa được bật

{
}

// hàm tạo ra "giấy" và "chổi"
bool Pong::init()
{

    // đánh thức SDL kết nôi với OS (nếu mà không đánh thức nó chỉ là một đống code nằm trong ssd)
    // khởi tạo môi trường làm việc của SDL và kết nối với các tài nguyên của hệ điều hành
    int initResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    // kiểm tra xem có khởi tạo subsystem thành công hay không
    if (initResult != 0)
    {
        std::cerr << "SDL can't work" << SDL_GetError() << std::endl;
        return false;
    }

    // tạo struct đặc tả âm thanh , và dùng {} để biến mọi giá trị rác bên trong thành zero và nullptr
    SDL_AudioSpec want{};
    want.freq = 44100;               // tiêu chuẩn mẫu âm thanh / 1 giây
    want.channels = 1;               // phát tất cả các sóng cùng 1 kênh
    want.format = AUDIO_F32SYS;      // 1 sample == khối 4 byte (float)
    want.samples = 512;              // xử lý 512 samples 1 lần callback
    want.userdata = this;            // biến con trỏ Pong* thành void để nhét được vào đúng hàm (chuẩn chữ ký) mà SDL yêu cầu
    want.callback = fillAudioBuffer; // viết hàm với không () nghĩa là địa chỉ hàm

    // sau khi đã tạo đặc tả âm thanh mong muốn sẽ hỏi SDL thương lượng với phần cứng , và kết nối với thiết bị âm thanh
    // tham số 1: tên thiết bị âm thanh muốn kết nối , tham số 2: muốn phát hay thu , tham số thứ 3: đặc tả âm thanh mong muốn, tham số 4: đặc tả âm thanh đã thương lượng được với phần cứng (cần tạo 1 SDL_AudioSpec để lưu lại) , tham số cuối : có muốn thay đổi gì không ????
    // audioDevice == mã đại diện tài nguyên
    audioDevice = SDL_OpenAudioDevice(nullptr, 0, &want, nullptr, 0);

    // kiểm tra xem thiết bị mở có bị lỗi không
    if (audioDevice == 0)
    {
        std::cerr << "không mở được thiết bị âm thanh: " << SDL_GetError() << std::endl;
        return false;
    }
    // sau khi đã mở được thiết bị ta sẽ sử dụng nó (bằng cái mã tài nguyên được trả lại)
    SDL_PauseAudioDevice(audioDevice, 0);

    // thuê một mảnh đất : chưa làm bất kỳ cái gì cả , chỉ liên hệ với OS hỏi là tao cần một màn hình với kích thước như này , rồi nó lại hỏi các tầng thấp hơn nữa... rồi đưa lại cho mình một các thông số của cái của sổ mình muốn tạo , ghi vào con trỏ window
    window = SDL_CreateWindow(
        "pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        MaxWindowW,
        MaxWindowH,
        SDL_WINDOW_SHOWN);

    // kiểm tra xem tờ giấy có được tạo ra không => nếu không sẽ trả lại nullptr
    if (!window)
    {
        std::cerr << "can't create window" << SDL_GetError() << std::endl;
        return false;
    }

    // nói chuyện với API backend điều khiển gpu driver để xin quyền "điều khiển" (nơi vẽ, cách vẽ, bộ đệm , màu sắc)
    renderer = SDL_CreateRenderer(
        window,
        -1,                      // chọn cái rendering driver (tức OpenGL) của linux , cái này nói chuyện với phần cứng
        SDL_RENDERER_ACCELERATED // chọn GPU nếu có
    );

    if (!renderer)
    {
        std::cerr << "can't create renderer" << SDL_GetError() << std::endl;
        return false;
    }

    // sau khi đã có : hệ thống video subsystem mà OS trao cho SDL , và có màn hình cùng để vẽ lên, và gpu (cây chổi) để vẽ , ta lần nữa sẽ khởi thêm hệ thống xử lý chữ để vẽ khối chữ lên màn hình
    int initTextSystem = TTF_Init();

    // ta sẽ kiểm tra là hệ thống chữ có khởi tạo thành công không bằng cách so sánh điều kiện với con số nó trả lại
    if (initTextSystem == -1)
    {
        std::cerr << "hệ thống chữ không được khởi tạo: " << TTF_GetError() << std::endl;
        return false;
    }

    // sau khi có hệ thống chữ rồi ta mới tải font từ đường dẫn lưu lại vào pointer để tí sử dụng để vẽ
    // hàm TTF_OpenFont cần 2 tham số là đường mà font đã ở , và size của font mà mình muốn dùng , theo như comment của người tạo thì sau khi mà sử dụng xong tài nguyên tài cần trả lại bằng hàm TTF_CloseFont() để tránh rò rì bộ nhớ
    font = TTF_OpenFont("../assets/font.ttf", 48);

    // sau khi đã load font , ta sẽ check là đường dẫn có hoạt động được không bằng điều kiện
    if (!font)
    {
        std::cerr << "đường mở file ttf không vào được" << std::endl;
        return false;
    }

    // sau khi đã có cả khởi hệ thống xử lý chữ thành công, và truy cập được vào font trong đường dẫn ta sẽ khởi tạo thêm 2 dùng khối chữ trong VRAM chứa dữ liệu ảnh bitmap
    renderMenuTextVram();
    renderGameOverTextVram();

    running = true;
    // 2 hàm này được gọi ở trong này là bởi vì tài nguyên này là tạo font và dùng lại không phải thay đổi liên tục nên được gọi ngay khi khởi tạo các tài nguyên

    return true;
}

// sau khi OS hỏi SDL trả lại tham số cho callback và yêu cầu viết nội dung vào buffer thì ta hàm fillAudioBuffer sẽ hoạt động
// fillAudioBuffer là member function thuộc về class Pong nhưng khi dịch về binary thì vẫn tương thích với C vì nó vẫn chỉ là một địa chỉ
// con trỏ void này thật sự đang trỏ đến chính Object Pong này , nhưng mình phải dùng this để biến nó thành void* giống với chữ ký mà SDL(C) yêu cầu ,và khi mà fillAudioBuffer được gọi thì sẽ được trả lại con trỏ void* (Pong*) này
// outputBuffer chính là nơi mình ghi sample vào
// bufferSize là số lượng SDL thương lượng được với phần cứng cho phép mình có thể xử lý mỗi lần (có thể là 256,512,1024,..)
void Pong::fillAudioBuffer(void *userdata, Uint8 *outputBuffer, int bufferSize)
{
    // bước đầu tiên là ta cần phải ép lại con trỏ void về con trỏ Pong* để mà thao túng dữ liệu bên trong rồi để mà có thể ghi nó vào buffer
    Pong *game = static_cast<Pong *>(userdata);
    // sau đó ta sẽ biến con trỏ ouputBuffer về thành float, vì mỗi một sample ta xử lý có kích thước 4 bytes , mà Unit8* == unsigend char dùng con trỏ bằng cách đi từng byte một không đúng với cách ta xử lý từng sample
    // ép kiểu C-style
    float *buffer = (float *)outputBuffer;
    // đổi số lượng byte (tổng kích thước được thượng lượng mỗi lần cho xử lý) về sample để ghi dữ liệu
    // samples ở đây chưa phải là nội dung ghi được vào buffer chỉ là số lượng buffer mà ta sẽ được xử lý để không bị ghi tràn ra mà thôi
    // và nó nằm ở một chỗ khác trong ram , tí nữa gán từng sample vào trong buffer(tức bộ nhớ) thì nó mới thành dữ liệu trong bộ nhớ
    float samples = bufferSize / sizeof(float);

    // ta tạo vòng lặp đi qua từng sample (trong RAM) để ghi dữ liệu
    for (int i = 0; i < samples; i++)
    {
        // biến từng sample đang chưa rác thành "sạch sẽ"
        float sample = 0.0f;

        // tiếp tục tạo vòng lặp đi qua từng beep tức trong mảng động để đọc thông tin , vào thao túng dữ liều rồi ghi vào sample
        for (auto &beep : game->playingSounds)
        {
            // nếu mà beep đã hết "tuổi thọ" tức số sample cạn thì bỏ qua tiến đển beep theo theo để lấy dữ liệu , nhưng bước này chỉ là bỏ qua tạm thời chưa hề xóa rác đi
            if (beep.samplesRemaining <= 0)
            {
                continue;
            }

            // giờ ta sẽ thao túng dữ liệu : của biên độ và phase (góc đường cung)
            // cộng dồn biên độ của cả 3 âm thanh beep va chạm (tại mỗi thời điểm)
            // sinf là bảng tra radian , loudness : âm lượng (khuếch đại to nhỏ hình dạng sóng) tăng giảm biên độ
            sample += sinf(beep.phase) * beep.loudness;
            // cập nhật góc_pha (vị trí đường cung tiến thêm) mỗi sample của từng sóng (3 sóng beep)
            // chiều dài tối đa của 1 chu kỳ * (số chu tiến được mỗi sample) == (tổng tần số trên giây / tổng mẫu âm thanh trên giây)
            beep.phase += (2.0f * M_PI) * (beep.frequency / 44100.0f);
            // trừ đi số sample còn lại của mỗi âm thanh "giảm tuổi thọ" == thời gian nó sống
            // dùng -- == -= 1 nhưng đây là mô tả âm thanh
            beep.samplesRemaining--;
        }
        // gán dữ liệu của sample (4bytefloat) vào trong buffer(Ram)
        buffer[i] = sample;
    }

    // sau ghi một đợt âm thanh hoàn thành , thì có beep trong mảng động hết sample và đã được bỏ qua bởi continue , nhưng tài nguyên của mảng vẫn được được dùng => chậm đi nếu có nhiều âm thanh bị hết sample mà không được xóa
    // dùng thuật toán để sắp xếp lại mảng sau đó xóa nhưng beep đã không còn sample đi
    // newEnd tra lại iterator: con trỏ ngăn cách chỉ đến phần ở giữa 2 nhóm dữ liệu đã được phân chia (không điều kiện bên trái , khớp điều kiện bên phải)
    auto newEnd = std::remove_if(
        game->playingSounds.begin(),
        game->playingSounds.end(),
        [](const auto &beep)
        {
            return beep.samplesRemaining <= 0;
        });

    game->playingSounds.erase(newEnd, game->playingSounds.end());
}

// hàm xử lý ảnh : tạo bitmap trong ram sau đó đưa qua vram , trả tài nguyên
// hàm cần 2 tham số : tham số 1 là object chứa một chuỗi các ký tự , tham số 2 là địa chỉ hình chữ nhật
SDL_Texture *Pong::CreateTextTexture(
    const std::string &text,
    SDL_Rect &rect)
{
    // ta tạo ra struct để chứa màu sắc để đưa vào hàm TTF_RenderText_Solid()
    // SDL_Color là một kiểu của SDL2 là để mô tả màu sắc là một struct : là một gói gồm nhiều biến khác loại gộp lại với nhau có 4 chỉ số Uint8 { red, green , blue , alpha }
    SDL_Color Red = {255, 0, 0, 255};

    // sau khi đã có màu ta sẽ kết hợp với text và font để tạo ra bitmap trong ram
    // vì text trong c++ là một object mà SDL được viết bởi C không có object nên phải dùng hàm c_str() để mượn địa chỉ từ pointer và trả về kiểu mảng const char*
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), Red);

    // dùng điều kiện để kiểm tra bitmap đã được tạo thành công trong ram chưa
    if (!surface)
    {
        std::cerr << "không tạo thành công surface" << std::endl;
    }

    // sau khi đã có được surface ta sẽ tiến đến việc copy dữ liệu bitmap từ ram vào vram để có thể vẽ bằng gpu
    // ta dùng hàm SDL_CreateTextureFromSurface cần 2 tham số : 1 là gpu => renderer , 2 dữ liệu ram để copy vào vram
    // texture là một pointer chứa địa chỉ của SDL đại diện cho giá trị của bitmap trong vram chứ không trực tiếp can thiệp vào
    // sau khi  dùng xong ở phần hàm dọn dẹp cleanUp() sẽ dùng một hàm để trả lại tài nguyên cho vram
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    // ta kiểm tra dữ liệu xem là đã copy được trong vram chưa bằng điều kiện
    if (!texture)
    {
        std::cerr << "không copy được dữ liệu từ surface sang texture" << std::endl;
    }

    // sau khi mà đã copy thành công dữ liệu thì ta sẽ làm bươc cuối là reference vào trong pointer surface lấy ra width và height gắn cho struct SDL_Rect
    rect.w = (*surface).w;
    rect.h = (*surface).h;
    rect.x = 0;
    rect.y = 0;

    // sau khi hoàn thành được toàn bộ công việc trong surface tức dữ liệu trong ram ta sẽ free tài nguyên để không rò rỉ tài nguyên
    SDL_FreeSurface(surface);

    // và ta trả lại dữ liệu trong vram để tí dùng hàm SDL_RenderCopy() để gửi lệnh vẽ text lên màn hình
    return texture;
}

// sau khi ta tạo xong hàm CreateTextTexture() ta sẽ biến text thành nội dung có thể vẽ được trong vram , vì nó là tài nguyên "đắt" nên phải sử dụng 2 hàm rendermenuTextVram() , rendereGameOverTextVram() chứa 2 biến SDL_Texture* (pointer chứa địa chỉ) khởi tạo ngay trong  hàm init() để đỡ tốn tài nguyên (tức là tạo 1 lần vẽ hàng 1000 lần chứ không tạo ở render() rồi đưa vào trong vòng lặp)
void Pong::renderMenuTextVram()
{
    // tạo ra tham số cần thiết để đưa vào trong tham số của hàm cần , ở trong hàm CreateTextTexture() cần một const std::string , và một struct SDL_Rect&
    const std::string &text = "choose 1 or 2 to play";
    menuText = CreateTextTexture(text, menuTextBlock);
}

void Pong::renderGameOverTextVram()
{
    const std::string &text = "Game Over - choose R";
    gameOverText = CreateTextTexture(text, gameOverTextBlock);
}

// vẽ bóng và vợt
void Pong::renderPaddleBall()
{

    // vợt trai
    SDL_Rect paddleLeft;
    paddleLeft.x = paddleLeftX;
    paddleLeft.y = paddleLeftY;
    paddleLeft.w = paddleW;
    paddleLeft.h = paddleH;

    // vợt phai
    SDL_Rect paddleRight;
    paddleRight.x = paddleRightX;
    paddleRight.y = paddleRightY;
    paddleRight.w = paddleW;
    paddleRight.h = paddleH;

    // ball
    SDL_Rect ball;
    ball.x = ballX;
    ball.y = ballY;
    ball.w = ballSize;
    ball.h = ballSize;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddleLeft);
    SDL_RenderFillRect(renderer, &paddleRight);
    SDL_RenderFillRect(renderer, &ball);
}

// vẽ đường kẻ ở giữa
void Pong::renderMiddleLine()
{

    SDL_Rect middleLine;

    // đây là dùng công thức của ngày hôm qua
    for (int i = 0; i <= 20; i++)
    {
        middleLine.x = 498;
        middleLine.y = 0 + i * 60;
        middleLine.w = 4;
        middleLine.h = 50;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &middleLine);
    }
}

// vẽ bảng điểm bằng khối
void Pong::renderScore()
{
    // câu hỏi: tại sao cái này của tôi nó lại vẽ luôn 2 block đầu tiên luôn ngay cả khi chưa ghi điểm ? và giải thích cho tôi nó hoạt động như thế nào , tôi vẫn chưa hiểu tại sao khi lông nó vào trong loop running mỗi lần chạm vào cái tường trục X 2 bên trái phải nó mới bắt đầu vẽ ra window không giống như các cái (vợt , vạch , bóng) vẽ ra từ đầu

    // tao ra một object SDL_Rect và member var (kích thước của nó)
    // dùng thêm cả công thức for loop : x = x_bắt đầu + i * khoảng cách (lớn hơn kích thước chiều cao của vật)

    SDL_Rect scoreBlockLeft;

    // vòng lặp for cần điều kiện start , end, step , và dùng ; để kết thúc từng statement , i++ là cộng +=
    for (int i = 0; i < leftScore; i++)
    {
        scoreBlockLeft.x = 200 + i * 20; // 20 là khoảng cách lớn hơn kích thước vật dự tính là 15
        scoreBlockLeft.y = 100;
        scoreBlockLeft.w = 15;
        scoreBlockLeft.h = 15;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &scoreBlockLeft);
    }

    // score ben phai
    SDL_Rect scoreBlockRight;

    for (int i = 0; i < rightScore; i++)
    {
        scoreBlockRight.x = 600 + i * 20;
        scoreBlockRight.y = 100;
        scoreBlockRight.w = 15;
        scoreBlockRight.h = 15;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &scoreBlockRight);
    }
}

// thiết lập điều kiện để nhay sang các trạng thái
void Pong::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // so sánh biến currentScreen với giá trị của enum truy cập == scope
    if (currentScreen == Screen::MENU)
    {
        // ta sẽ vẽ text lên màn hình dùng gpu, ta gừi lệnh vẽ cái text đang nằm trong ở vram cho gpu để vẽ, trong hàm SDL_RenderCopy thì gồm có 4 tham số : renderer(gpu nào sẽ vẽ) , menuText(dữ liệu ảnh nằm trong vram) , srcrect (lấy hình từ vị trị (0,0) nào - có cắt hình không) , dstrect (vị trí của nó nằm trong window) , tham số dstrect thì ta sẽ nhét rect mà ta đã gắn cho rect ở trong CreateTextTure() và giờ đang nằm ở hai biến chứa địa chỉ &menuTextBlock, &gameOverTextBlock của bốn cái chỉ số (x,y,w,h)
        SDL_RenderCopy(renderer, menuText, nullptr, &menuTextBlock);
    }
    else if (currentScreen == Screen::ONE_PLAYER)
    {
        renderPaddleBall();
        renderMiddleLine();
        renderScore();
    }
    else if (currentScreen == Screen::TWO_PLAYER)
    {
        renderPaddleBall();
        renderMiddleLine();
        renderScore();
    }
    else if (currentScreen == Screen::GAMEOVER)
    {
        SDL_RenderCopy(renderer, gameOverText, nullptr, &gameOverTextBlock);
    }

    // sau khi vẽ xong hết rồi đổi từ back buffer các hình vẽ sang front buffer (hiển thị lên màn hình để người chơi thấy)
    SDL_RenderPresent(renderer);
}

// tạo hàm xử lý sự kiện để nhảy qua nhảy lại 4 sự kiện
void Pong::handleEvents(float delta)
{
    // đầu tiên kiểm tra đang ở màn hình MENU sau đó nghe phím enter để bắt đầu game dùng PollEvent (hàm này ghi lại sự kiện mà SDL nghe từ OS cái sự kiện vừa diễn ra) toàn bộ sự kiện này nên đưa vào vòng lặp để lắng nghe toàn bộ sự kiện
    // Có 3 sự kiện mà ta phải kiểm tra bằng phím vừa ấn (SDL_PollEvent(&event)) đó là từ MENU sang ONE_PLAYER or TWO_PLAYER , và từ GAMEOVER về MENU và cả sự kiện thoát toàn bộ game SDL_QUIT

    // hàm này làm gì ? thay đổi cái gì ? tại sao lại dùng ở đây ?
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {

        // giờ sẽ là sự kiện yêu cầu kết thúc : có thể là hủy window bằng chuột , có thể dùng super + Q , có thể tắt máy nên không quan trọng là yêu cầu hủy bằng cái nào chỉ gom lại thành 1 loại sự kiện duy nhất gửi về từ OS ghi lại VÀ TRAO CHO SDL và SDL_PollEvent sẽ đọc và ghi vào Event đó chính là SDL_QUIT
        // không quan trọng là đang ở trạng thái nào khi có lệnh yêu cầu hủy là phải hủy thế thôi
        if (event.type == SDL_QUIT)
        {
            // ta sẽ tắt toàn bộ trò chơi bằng cách tắt loop chính đi => running = false;
            running = false;
        }

        if (event.type == SDL_KEYDOWN)
        {

            if (currentScreen == Screen::MENU && event.key.keysym.scancode == SDL_SCANCODE_1)
            {
                // ta sẽ nhảy về màn hình của 1 người chơi
                currentScreen = Screen::ONE_PLAYER;
                // cho thêm hàm startGame() vào trong màn khởi đầu (1 người chơi) đẻ thiết lập lại trạng thái của trò , bóng không còn đứng yên , điểm thì về 0 , và vị trí được tái thiết lập về ban đầu bóng sẽ di chuyển để có va chạm
                startGame(1);
            }
            // event là object kiểu SDL_Event được PollEvent ghi sự kiện xảy ra vào các biến thành viên của nó , nên ta phải truy cập theo dạng chuỗi để đọc được nội dung của sự kiện đó , có một sự trường hợp khác nhau như event.type là kiểu của sự kiện , event.key.keysym.scancode là phím vật lý nào đang được ấn
            if (currentScreen == Screen::MENU && event.key.keysym.scancode == SDL_SCANCODE_2)
            {
                // ta sẽ nhảy vào màn 2 người chơi
                currentScreen = Screen::TWO_PLAYER;
                // màn này cũng cân tái thiết lập mọi trạng thái của game
                startGame(1);
            }
            if (currentScreen == Screen::GAMEOVER && event.key.keysym.scancode == SDL_SCANCODE_R)
            {
                currentScreen = Screen::MENU;
            }
        }
    }

    const Uint8 *keystate = SDL_GetKeyboardState(nullptr); // ta cho nullptr vì ta chỉ cần địa chỉ con trỏ không phải là số lượng keystate mà GetKeyboardState chứa

    // Xử lý trạng thái một người chơi với máy
    if (currentScreen == Screen::ONE_PLAYER && paddleFroze == false)
    {
        // lắng nghe phím cho người chơi bên trais
        if (keystate[SDL_SCANCODE_W])
        {
            // tại sao tôi viết code như này thì nó lại di chuyển được làm gì có lệnh vẽ nào đâu chỉ cần viết logic sau đó là CPU tự biết hỏi GPU vẽ nó lên  màn hình window* mà tạo trong init() à ?
            paddleLeftY -= paddleSpeed * delta;
        }
        if (keystate[SDL_SCANCODE_S])
        {
            paddleLeftY += paddleSpeed * delta;
        }

        // giờ là máy 0.1 đuổi theo tâm bóng
        float ballCenter = ballY + ballSize * 0.5f;
        float paddleCenter = paddleRightY + paddleH * 0.5f;

        if (ballCenter < paddleCenter)
        {
            paddleRightY -= paddleSpeed * delta;
        }
        if (ballCenter > paddleCenter)
        {
            paddleRightY += paddleSpeed * delta;
        }

        // ngăn lại không cho vợt di chuyển qua khỏi màn hình trên trục Y
        if (paddleLeftY <= MinWindowH)
        {
            paddleLeftY = MinWindowH;
        }
        if (paddleLeftY >= MaxWindowH - paddleH)
        {
            paddleLeftY = MaxWindowH - paddleH;
        }
        if (paddleRightY <= MinWindowH)
        {
            paddleRightY = MinWindowH;
        }
        if (paddleRightY >= MaxWindowH - paddleH)
        {
            paddleRightY = MaxWindowH - paddleH;
        }
    }

    // màn hai người chơi nghe 4 phím : W , S , UP , DOWN , và có cả ngăn va chạm trượt ra khỏi màn hình
    if (currentScreen == Screen::TWO_PLAYER && paddleFroze == false)
    {

        // dùng toán con trỏ , mảng đến tính được vị trí của phím sau đó kiểm tra trạng thái (0 hoặc 1) , a[b] = *(a + b)
        if (keystate[SDL_SCANCODE_W])
        {
            paddleLeftY -= paddleSpeed * delta;
        }
        if (keystate[SDL_SCANCODE_S])
        {
            paddleLeftY += paddleSpeed * delta;
        }
        if (keystate[SDL_SCANCODE_UP])
        {
            paddleRightY -= paddleSpeed * delta;
        }
        if (keystate[SDL_SCANCODE_DOWN])
        {
            paddleRightY += paddleSpeed * delta;
        }

        // không di chuyển trượt ra khỏi màn hình
        if (paddleLeftY <= MinWindowH)
        {
            paddleLeftY = MinWindowH;
        }
        if (paddleLeftY >= MaxWindowH - paddleH)
        {
            paddleLeftY = MaxWindowH - paddleH;
        }
        if (paddleRightY <= MinWindowH)
        {
            paddleRightY = MinWindowH;
        }
        if (paddleRightY >= MaxWindowH - paddleH)
        {
            paddleRightY = MaxWindowH - paddleH;
        }
    }

    if (currentScreen == Screen::ONE_PLAYER || currentScreen == Screen::TWO_PLAYER)
    {
        if (endDelay == false && (rightScore == 10 || leftScore == 10))
        {
            // đo thời điểm game bắt đầu dừng sau khi đã kết chiến thắng / thua
            delayGameOver = SDL_GetTicks();
            // thiết lập bool bằng đúng để bằng đầu so sánh thời gian đã được 3 giây chưa
            endDelay = true;
            // cho bóng và vợt dừng lại
            ballFrozen = true;
            // cho vợt dừng lại => paddleFroze == true
            paddleFroze = true;
            // chỉnh lại vị trí 2 vợt về giữa
            paddleLeftY = 500.0f;
            paddleRightY = 500.0f;
        }
    }

    if (endDelay == true)
    {
        Uint32 now = SDL_GetTicks();
        if ((now - delayGameOver) >= 5000)
        {
            // sau điều kiện khớp , ta nhảy đến màn hình kết thúc , điểm thiết lập lại thành 0 để khi nhảy vào ONE_PLAYER , TWO_PLAYER thì không bị bật về GAMEOVER do chưa reset game
            currentScreen = Screen::GAMEOVER;

            // thiết lại trạng thái trì hoãn kết thúc (endDelay = false) để chơi ván mới không bị nhảy về màn Screen::GAMEOVER
            endDelay = false;
        }
    }
}
// hàm cập nhật : va chạm , bóng đóng băng
void Pong::update(float delta)
{

    // đầu tiên là kiểm tra điều kiện nếu mà : màn hình là GAMEOVER ,hoặc MENU thì bóng sẽ đóng băng
    if ((currentScreen == Screen::MENU || currentScreen == Screen::GAMEOVER) && ballFrozen == true)
    {
        return;
    }

    // vì bóng không dừng lại ở cả trạng thái một người chơi và hai người chơi nên ta phải làm thêm một điều kiện nữa
    if ((currentScreen == Screen::ONE_PLAYER || currentScreen == Screen::TWO_PLAYER) && ballFrozen == true)
    {
        return;
    }

    // tái tạo lại 3 cờ về false mỗi frame để âm thanh không bị kêu vang ??

    HitPaddleThisFrame = false;
    HitWallThisFrame = false;
    ScoreThisFrame = false;

    // nếu mà điều kiện bóng không đóng băng == false thì ta sẽ nhay sang điều kiện này mà không cần nằm trong if
    ballX += ballVelX * delta;
    ballY += ballVelY * delta;

    // tính toán va chạm cho bong với tuongwf  và đập lại , ghi điểm được tính cho người đánh
    if (ballX <= MinWindowW)
    {
        rightScore++;
        // thiết lập trạng thái ăn điểm thành đúng
        resetBall(1);
        // thiết lập cờ ăn điểm thành đúng đẻ tạo âm thanh
        ScoreThisFrame = true;
    }
    if (ballX >= MaxWindowW - ballSize)
    {
        leftScore++;
        resetBall(-1);
        ScoreThisFrame = true;
    }

    // tính va chạm với trục top/bottom tường
    if (ballY <= MinWindowH)
    {
        // tạo cờ trạng thái va chạm với trường trên là đúng
        HitWallThisFrame = true;
        ballY = MinWindowH;
        ballVelY = -ballVelY;
    }
    if (ballY >= MaxWindowH - ballSize)
    {
        // tạo trạng thái va chạm với tường dưới là đúng
        HitWallThisFrame = true;
        ballY = MaxWindowH - ballSize;
        ballVelY = -ballVelY;
    }

    bool overlapLeftX = ballX <= paddleLeftX + paddleW;
    bool overlapLeftY = ballY + ballSize >= paddleLeftY && ballY <= paddleLeftY + paddleH;

    // thiết lập trạng thái cờ va chạm giữa bóng và vợt thành đúng
    if (overlapLeftX && overlapLeftY && ballVelX < 0)
    {
        HitPaddleThisFrame = true;
        ballX = paddleLeftX + paddleW;
        ballVelX = -ballVelX;
        float ballCenter = ballY + ballSize * 0.5f;
        float paddleCenter = paddleLeftY + paddleH * 0.5f;
        float offset = (ballCenter - paddleCenter) / (paddleH * 0.5f); // chuẩn hóa độ lệch : công thức của chatGpt độ lệch thật / chia độ lệch tối đa
        const float fixSpeed = 700.0f;
        ballVelY = fixSpeed * offset;
    }

    // tạo thêm điều kiện va chạm với vợt phải

    bool overlapRightX = ballX + ballSize >= paddleRightX;
    bool overlapRightY = ballY + ballSize >= paddleRightY && ballY <= paddleRightY + paddleH;

    // thiết lập cờ trạng thái va chạm thành đúng (giữa bóng và vợt)
    if (overlapRightX && overlapRightY && ballVelX > 0)
    {
        HitPaddleThisFrame = true;
        ballX = paddleRightX - ballSize;
        ballVelX = -ballVelX;

        float ballCenter = ballY + ballSize * 0.5f;
        float paddleCenter = paddleRightY + paddleH * 0.5f;
        float offset = (ballCenter - paddleCenter) / (paddleH * 0.5f);
        const float fixSpeed = 700.0f;
        ballVelY = fixSpeed * offset;
    }

    // tạo âm thanh khi các điều kiện đúng
    if (HitPaddleThisFrame == true)
    {
        // phuong thuc emplace_back tao phan tu beep ghi vao phan cuoi cua mang dong
        playingSounds.emplace_back(Pong::Beep{
            330.0f,                        // tần số
            0.0f,                          // pha khởi động
            0.2f,                          // độ to của loa
            static_cast<int>(44100 * 0.04) // tính thời gian sống của âm thanh <=> tổng số sample mà âm thanh có
        });
    }
    if (HitWallThisFrame == true)
    {
        // phuong thuc emplace_back tao phan tu beep ghi vao phan cuoi cua mang dong
        playingSounds.emplace_back(Pong::Beep{
            330.0f,                        // tần số
            0.0f,                          // pha khởi động
            0.2f,                          // độ to của loa
            static_cast<int>(44100 * 0.04) // tính thời gian sống của âm thanh <=> tổng số sample mà âm thanh có
        });
    }
    if (ScoreThisFrame == true)
    {
        // phuong thuc emplace_back tao phan tu beep ghi vao phan cuoi cua mang dong
        playingSounds.emplace_back(Pong::Beep{
            880.0f,                        // tần số
            0.0f,                          // pha khởi động
            0.2f,                          // độ to của loa
            static_cast<int>(44100 * 0.04) // tính thời gian sống của âm thanh <=> tổng số sample mà âm thanh có
        });
    }
}

// tạo hàm thiết lập về ban đầu khi mà bóng va chạm vào Trục X (trái / phải)
void Pong::resetBall(int direction)
{
    paddleLeftY = MaxWindowH / 2;

    paddleRightY = MaxWindowH / 2;
    ballX = MaxWindowW / 2;
    ballY = MaxWindowH / 2;

    ballVelY = 0.0f;
    ballVelX = direction * std::abs(ballVelX);
}

// logic của hàm startGame
void Pong::startGame(int direction)
{
    resetBall(direction);
    ballFrozen = false;
    paddleFroze = false;
    rightScore = 0;
    leftScore = 0;
}
// dùng run để test xem từng bước đã hoạt động được chưa
void Pong::run()
{
    // tính thời gian độ lệch giữa 2 frame dịch chuyển: tạo ra 2 khung thời gian để đo được khoảng khắc bóng đã di chuyển được bao xa rồi
    Uint32 previousTime = SDL_GetTicks();
    while (running)
    {
        Uint32 currentTime = SDL_GetTicks();
        float delta = (currentTime - previousTime) / 1000.0f; // đổi sang second để tính
        // phải gắn gian của frame mới nhất về thành frame hiện tại để tính
        previousTime = currentTime; // #lỗi : khi thời gian mà làm sai thì di chuyển sai (vật lý bựa)
        // tức là handleEvent là để thay giá trị của các biến vợt trong RAM trước (CPU tính)
        handleEvents(delta);
        // và sau đó là thay đổi giá trị của bóng trong RAM (CPU tính)
        update(delta);
        // rồi từ đó dự theo dữ liệu vị trí vừa tính toán của RAM (hoặc copy sang vram) để GPU hoặc CPU tạo hình vẽ lên màn hình
        render();
    }
}

// don tam tai nguyen
void Pong::cleanUp()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    // sau khi đã khởi tạo một số tài nguyên mới từ thư viện con SDL2_ttf ở trong ram và vram ta cần trả lại tài nguyên bằng một số hàm hủy các pointer (biến chứa địa chỉ)
    if (menuText)
    {
        SDL_DestroyTexture(menuText);
    }
    if (gameOverText)
    {
        SDL_DestroyTexture(gameOverText);
    }
    if (font)
    {
        TTF_CloseFont(font);
    }
    TTF_Quit();
    SDL_Quit();
}

// gọi hàm phá hủy sau khi đã vượt ra khỏi phạm vi của hàm main
Pong::~Pong()
{
    cleanUp();
}