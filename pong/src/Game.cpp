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
    std::cout << "start game..." << std::endl;

    // hỏi OS,driver tạo ra hệ thống video để ta có thể tạo ra "tờ giấy chuyển động"
    // khởi tạo thêm cả hệ thống Âm Thanh
    // khi dùng SDL_Init thì cho VIDEO và AUDIO thì từng bước để từ phần mêm đến phần cứng là gì để có thê thao túng được phần cứng, vì bạn giải thích cho tôi là SDL là API vậy có phải nó sẽ hỏi OS subsytem rồi OS subsystem sẽ hỏi driver hỏi CPU và GPU và Card âm thanh khởi động "nghĩa là cho nó quyền tạo video và âm thanh (không trực tiếp)" phải không ?
    int initResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    // kiểm tra xem có khởi tạo subsystem thành công hay không
    if (initResult != 0)
    {
        std::cerr << "SDL can't work" << SDL_GetError() << std::endl;
        return false;
    }

    // cái này một struct và khởi tạo biến (object) với {} là để biến các trường dữ liệu "sạch sẽ" về không hoặc về nullptr
    // cái này đặc tả định dạng và cấu hình âm thanh mà mình muốn nhưng mà SDL+OS sẽ cho mình hay không thì phải phụ thuộc và nó không phải mình muốn như nào cũng được
    SDL_AudioSpec want{};
    // cái này là tần số: nhưng mà để mô ta độ mịn (kiểu FPS) chứ không phải mô tả độ cao thấp để tạo âm thanh
    want.freq = 44100;
    // ADIO_F32SYS là một mã định dang không có ý nghĩa toán học để nói với SDL biết:
    // cái này định dạng cho mỗi sample : 32bit 1 sample , và là float , sắp xếp thứ tự byte theo hệ thống
    want.format = AUDIO_F32SYS;
    // channels: cái này là chọn bao nhiêu kênh được phân phát bao nhiêu sóng mỗi kênh
    // số 1 không phải là chể độ phát sóng mà là , trộn tất cả các sóng vào một kênh rồi phát , hệ quả là tất loa trái phải đều phát âm thanh đã được trộn
    want.channels = 1;
    // samples ở đây là mỗi khối samples mà ta sẽ xử lý , và phát ra chữ không phát ra từng sample một , ta xử lý theo cụm , 512 là số samples 1 khối được xử lý
    // cần phân biệt : sample >< chu kỳ >< âm thanh.
    want.samples = 512;
    // trường dữ liệu này là để hợp thức hóa : object của C++ thành một địa chỉ vô danh tính sau đó đưa vào trong hàm C như một tham số "chuẩn" và sau đó ép lại thành đúng kiểu void => Pong sau đó thao túng logic của dữ liệu vector struct Beep bên trong
    want.userdata = this;
    // trường dữ liệu này: là chứa địa chỉ của hàm , và SDL yêu là mình tạo hàm này phải đúng tham số mà nó yêu , và đúng kiểu trả về để nó còn kiểm soát tài nguyên (hủy khi dùng xong)
    // callback là một pointer function : void (*callback)(void* gameState Unit8* outputBuffer, int bufferSize)
    // fillAudioBuffer không cần & vì nó là hàm và hàm trong c/c++ mà không có () tức là địa chỉ
    want.callback = &fillAudioBuffer;

    // audioDevice chứa 1 số nguyên là handle(mã đại diện cho tài nguyên) mà SDL_OpenAudioDevice() trả lại khi thành công
    // hàm SDL_OpenAudioDevice xin hệ điều hành cấp cho bạn một thiết bị âm thanh thật ,gắn nó với callback của bạn để tí bạn có thể tạo âm thanh
    // hàm này chỉ là mở cổng "mở thiết bị âm thanh" , còn việc tạo âm phải do callback
    // lý do nó trả lại số nguyên mà dùng SDL_AudioDeviceID mà không phải vì int là vì semantic type (kiểu mang ý nghĩa) độ dài 32bit 1 số nguyên và để nói với SDL là đang dùng thiết bị nào ,bla bla,...
    // tham số thứ 4 là nơi mà OS+SDL thống nhất thông số "thương lượng" với cấu hình và định dạng và sẽ báo lại nếu mình dùng kiểu SDL_AudioSpec have và &have để vào đó lấy thông tin
    audioDevice = SDL_OpenAudioDevice(nullptr, 0, &want, nullptr, 0);
    // đầy là : câu lệnh điều khiển luồng , và để kiểm tra là thiết bị có được bật thành công không ? Phụ thuộc vào (OS,DRIVER,LOA) nếu chúng lỗi thì báo lại và thoát sớm
    if (audioDevice == 0)
    {
        std::cerr << "Audio open failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // hàm này ra lệnh cho thiết bị âm thanh (bật/tắt) , tham số 1 là thiết bị âm thanh (chỉ hoạt động sau khi mà SDL_OpenAudioDevice mở thành công thiết bị loa và trả lại 1 số nguyên đại diện cho loa thật) , tham số thứ 2 là 0 (nghĩa là start)
    SDL_PauseAudioDevice(audioDevice, 0);

    // tạo tờ giấy chuyển động để vẽ lên
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

    // tạo cây chổi cọ bự => nếu không tạo được chổi sẽ trả lại nullptr
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

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

// dùng hàm âm thanh để tạo ra âm thanh
// hàm này không hề phụ thuộc vào object nhờ static(sẽ không có this trong chữ ký hàm), thì suy ra nó là một hàm đúng chuẩn kiểu của C , nhưng vì nó nằm trong namespace của Pong (static member function) tức là ta có thể truy cập = :: để viết được logic bên trong nó
// và khi compile code thì Pong::fillAudioBuffer sẽ dịch thành địa chỉ hàm (void*)(void*,Uint8*,int)
// hàm này lấy dữ liệu của (this(Pong*)==void*) để thao túng xong viết vào *outputBuffer để thiết bị loa đọc và chuyển đổi sang âm thanh
void Pong::fillAudioBuffer(void *userdata, Uint8 *outputBuffer, int bufferSize)
{
    // dòng này là ép lại con trỏ trỏ tới dữ liệu của this(Pong*) đã bị biến thành void* về dữ liệu ban đầu của nó (Pong*), rồi sau đó tạo một con trỏ để trở tới nơi Pong* đang ở
    Pong *game = static_cast<Pong *>(userdata);
    // outputBuffer là vùng bộ nhớ byte thô (Uint8*).
    // Ép sang float* để diễn giải vùng nhớ này như mảng các mẫu âm thanh
    // dạng float (32-bit), giúp con trỏ nhảy theo sizeof(float)
    // khi truy cập từng sample.
    float *buffer = (float *)outputBuffer;
    // biểu thức này tính tổng số samples = số buffer mà SDL (phần cứng) đưa / kích thước của mỗi sample : 4
    // Audio callback luôn làm việc với buffer theo byte, còn âm thanh được tư duy theo sample, nên ta phải quy đổi từ byte sang sample để ghi đúng số dữ liệu cho mỗi khối.
    int samples = bufferSize / sizeof(float);

    // ghi giá trị vào mỗi sample (đủ tổng samples mà chương trình đưa) và ghi nó vào buffer
    // vòng lặp này từ động tiến đến sample tiếp theo (từ 0 đến 512 giả dụ) theo i++ , và không quan gì đến số lượng sample của từng beep
    for (int i = 0; i < samples; i++)
    {
        // chủ động "im lặng"
        float sample = 0.0f;

        // auto là để compiler xác định được kiểu dựa vào game->playingSound cho mình
        // khi mà compiler dùng toán con trỏ (*game).playingSounds nó sẽ tính độ lệch offset để đến được nơi Beep beep đầu tiên tồn tại và suy ra được kiểu cho auto == Beep
        // tiếp theo đó trở đi là dùng for như bình thường : với mỗi Beep beep được tạo ra trong mảng động => tổng số lượng beep và khi nào lặp qua đủ toàn bộ các phần từ beep thì hoàn thành vòng lặp for
        for (auto &beep : game->playingSounds)
        {
            // cái vòng lặp này sẽ kiểm tra xem từng beep là còn thời gian không , nếu mà đã hết sẽ bỏ qua để cập nhật beep khác
            if (beep.samplesRemaining <= 0)
            {
                // tạm thời bỏ qua beep hiện tại (đã hết sample)
                continue;
            }

            /* sinf(beep.phase) đọc radian vừa tiến lên của đoạn cung mới
→ hỏi: tại vị trí này trên sóng, biên độ là bao nhiêu?

* beep.loudness
→ khuếch đại rung đó lên mạnh hay nhẹ

+=
→ cộng rung của nhiều nguồn âm tại cùng khoảnh khắc */
            sample += sinf(beep.phase) * beep.loudness;
            // tính mỗi thời điểm , sample sẽ tiến thêm bao nhiêu radian để từ đó có thể biết được vị trí của biên độ
            // 2.0f * M_PI là độ dài của đoạn sóng (1 chu kỳ) hay có thể gọi là đoạn dây ~ 6.28
            // mỗi sample sẽ đi bao nhiêu phần nhỏ của chu kỳ trên tổng số chu kỳ = tổng số chu kỳ(chu kỳ/giây) / tổng số samples(samples/giây)
            beep.phase += (2.0f * M_PI) * (beep.frequency / 44100.0f);

            beep.samplesRemaining--;
        }
        buffer[i] = sample;
    }

    static int tick = 0;
    if (++tick % 44100 == 0)
    {
        std::cout << "audio tick\n";
    }

    // xóa beep đã hết , lưu nội dung đã tính toán được về struct đây
    game->playingSounds.erase(std::remove_if(game->playingSounds.begin(), game->playingSounds.end(), [](const Beep &b)
                                             { return b.samplesRemaining <= 0; }),
                              game->playingSounds.end());
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

// logic của hàm startGame
void Pong::startGame(int direction)
{
    resetBall(direction);
    ballFrozen = false;
    rightScore = 0;
    leftScore = 0;
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
            std::cout << "Key down: scancode="
                      << event.key.keysym.scancode
                      << " keycode="
                      << event.key.keysym.sym
                      << std::endl;

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
                std::cout << "2 pressed" << std::endl;
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
    if (currentScreen == Screen::ONE_PLAYER)
    {
        // lắng nghe phím cho người chơi bên trais
        if (keystate[SDL_SCANCODE_W])
        {
            std::cout << "w pressed" << std::endl;
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
    if (currentScreen == Screen::TWO_PLAYER)
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
        }
    }

    if (endDelay == true)
    {
        Uint32 now = SDL_GetTicks();
        if ((now - delayGameOver) >= 3000)
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
    if ((currentScreen == Screen::MENU || currentScreen == Screen::GAMEOVER) && ballFrozen)
    {
        return;
    }

    // thêm logic va chạm tạo âm thanh
    // thiết lập lại "gây nên" mỗi khung hình
    ballHitPaddleThisFrame = false;
    ballHitWallThisFrame = false;
    scoreThisFrame = false;

    // nếu mà điều kiện bóng không đóng băng == false thì ta sẽ nhay sang điều kiện này mà không cần nằm trong if
    ballX += ballVelX * delta;
    ballY += ballVelY * delta;

    // tính toán va chạm cho bong với tuongwf  và đập lại , ghi điểm được tính cho người đánh
    if (ballX <= MinWindowW)
    {
        rightScore++;
        std::cout << "totalpoint:(rightpaddle): " << rightScore << std::endl;
        // thiết lập trạng thái ăn điểm thành đúng
        scoreThisFrame = true;
        resetBall(1);
    }
    if (ballX >= MaxWindowW - ballSize)
    {
        leftScore++;
        std::cout << "totalpoint:(leftPaddle): " << leftScore << std::endl;
        // thiết lập trạng thái ăn điểm thành đúng
        scoreThisFrame = true;
    }

    // tính va chạm với trục top/bottom tường
    if (ballY <= MinWindowH)
    {
        std::cout << "va chạm với tường bên trên" << std::endl;
        // tạo trạng thái va chạm với trường trên là đúng
        ballHitWallThisFrame = true;
        ballY = MinWindowH;
        ballVelY = -ballVelY;
    }
    if (ballY >= MaxWindowH - ballSize)
    {
        std::cout << "va chạm với tường bên dưới" << std::endl;
        // tạo trạng thái va chạm với tường dưới là đúng
        ballHitWallThisFrame = true;
        ballY = MaxWindowH - ballSize;
        ballVelY = -ballVelY;
    }

    bool overlapLeftX = ballX <= paddleLeftX + paddleW;
    bool overlapLeftY = ballY + ballSize >= paddleLeftY && ballY <= paddleLeftY + paddleH;

    // thiết lập trạng thái va chạm giữa bóng và vợt thành đúng
    if (overlapLeftX && overlapLeftY && ballVelX < 0)
    {
        ballHitPaddleThisFrame = true;
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

    // thiết lập trạng thái va chạm thành đúng (giữa bóng và vợt)
    if (overlapRightX && overlapRightY && ballVelX > 0)
    {
        ballHitPaddleThisFrame = true;
        ballX = paddleRightX - ballSize;
        ballVelX = -ballVelX;

        float ballCenter = ballY + ballSize * 0.5f;
        float paddleCenter = paddleRightY + paddleH * 0.5f;
        float offset = (ballCenter - paddleCenter) / (paddleH * 0.5f);
        const float fixSpeed = 700.0f;
        ballVelY = fixSpeed * offset;
    }

    // thêm âm thanh vào trong update
    if (ballHitPaddleThisFrame)
    {
        playingSounds.emplace_back(Pong::Beep{
            330.0f, // frequency: trầm vừa, không chói
            0.0f,
            0.22f,                             // volumne nhẹ
            static_cast<int>(44100 * 0.04f)}); // ~35ms
    }
    if (ballHitWallThisFrame)
    {
        playingSounds.emplace_back(Pong::Beep{
            330.0f, // cao hơn paddle để phân biệt
            0.0f,
            0.22f,
            static_cast<int>(44100 * 0.04)}); // ~45ms
    }
    if (scoreThisFrame)
    {
        playingSounds.emplace_back(Pong::Beep{
            880.0f, // đủ sáng để báo thành tích
            0.0f,
            0.28f,
            static_cast<int>(44100 * 0.09f)}); // ~90ms
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
        handleEvents(delta);
        update(delta);
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