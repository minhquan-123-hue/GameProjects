// sau khi đã khởi tạo header (chữ ký hàm , bản thiết kế ta sẽ làm gì) thì ta sẽ tạo các hàm hoạt động được thật sự ở đây
// vẫn là sử dụng công cụ nào thì nhập khẩu = #include (để preprocessor copy + paste code vào đây) , rồi lát nữa khi compile để mà compiler biết là xem ghi đúng chữ ký mà chưa

#include <Game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

// tạo constructor(hàm khởi tạo) , initialize tất cả biến thành viên và giá trị ban đầu của nó , để tránh có rác trong biến đó , hoặc con trỏ đó , gây ra undefined behaviors
BreakOut::BreakOut() : // chưa trỏ tới đâu cả
                       window(nullptr),
                       renderer(nullptr),
                       // hệ thống video , cửa sổ, cây bút vẽ chưa được tạo => vòng lặp chưa thể hoạt động
                       is_running(false),

                       // vị trí + kích thước của vợt + velocity
                       platformWidth(100.0f),
                       platformHeight(20.0f),
                       platformX(10.0f),
                       platformY(970.0f),
                       platformSpeed(800.0f),

                       // vị trí , kích thước, velocity của bóng
                       ballSize(30.0f),
                       ballX(500.0f),
                       ballY(500.0f),
                       ballVelX(600.0f),
                       ballVelY(600.0f),

                       // viên gạch: vị trí, kích thước
                       brickWidth(80.0f),
                       brickHeight(10.0f),
                       brickX(10.0f),
                       brickY(150.0f),
                       // wall min max
                       windowMax(1000.0f),
                       windowMin(0.0f),

                       // point + health
                       points(0),
                       health(0),

                       // dừng chương trình khi thắng hoặc thua
                       is_ballFrozen(false),
                       is_platformFrozen(false),

                       // màn hình hiện tại lúc đầu
                       currentScreen(Screen::MENU),
                       // chưa trỏ để nơi chứa file nào cả
                       font(nullptr)

{
}

// tiếp theo là khởi động SDL để "ghi danh" nói chuyện với OS
bool BreakOut::init()
{
    std::cout << "bắt đầu khởi tạo tài nguyên" << std::endl;
    int initResult = SDL_Init(SDL_INIT_VIDEO);
    // kiểm tra xem có tài nguyên phần cứng phục vụ cho VIDEO có hoạt động không
    if (initResult != 0)
    {
        std::cerr << "không khởi tạo được hệ thống VIDEO: " << SDL_GetError() << std::endl;
        return false;
    }

    // tạo một cửa số thật (os quản lý) , trả về một handle (sdl đưa cho bạn) để lát xử lý nó
    window = SDL_CreateWindow(
        "breakout",
        0,
        0,
        1000,
        1000,
        SDL_WINDOW_SHOWN // cai bien nay de lam gi ?
    );
    // kiem tra xem thong so cua so co duoc tao thành công hay không
    if (!window)
    {
        std::cerr << "thông số cửa sổ không được khởi tạo thành công!" << SDL_GetError() << std::endl;
        return false;
    }

    //
    renderer = SDL_CreateRenderer(
        window,
        -1,                                                  // chọn cái backend nào đang hỗ trợ => có thể là Open_GL
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // cái cờ này có phải nghĩa là chọn GPU Không ?
    );
    // kiểm tra xem là backend này đã được kết nối với SDL chưa ?
    if (!renderer)
    {
        std::cerr << "không khởi tạo được hệ thống backend: " << SDL_GetError() << std::endl;
        return false;
    }

    // khởi tạo hệ thống xử lý hệ thống font
    int initFontSystem = TTF_Init();

    // kiểm tra nếu mà hệ thống xử lý font khởi tạo không thành công trả lại false để thóat sớm
    if (initFontSystem == -1)
    {
        std::cerr << "không khởi tạo hệ thống xử lý font thành công." << TTF_GetError() << std::endl;
        return false;
    }

    // mở font vừa tải về
    font = TTF_OpenFont("../assets/font.ttf", 48);

    // kiểm tra xem có kết nối được với đường dẫn tới font thành công không
    if (font == nullptr)
    {
        std::cerr << "đường dẫn không kết nối thành công." << std::endl;
        return false;
    }

    // sau khi tạo xong tài nguyên của 3 khối chữ thì gọi tạo khởi tạo để không địt nhau với tài nguyên (gọi - phân bổ - dùng xong - xóa) khiến cho Ram không còn chỗ , game tụt trĩ
    createFontResource();

    // sau khi toàn bộ hệ thống của SDL , cửa sổ, backend hoạt động được rồi , ta sẽ trả về true và thiết lập trạng thái cờ running = true để mà cho vòng lặp chạy được (gửi lệnh vẽ cho GPU)
    is_running = true;
    return true;
}

// hàm tạo ảnh trong vram
SDL_Texture *BreakOut::createTextTexture(const std::string &text, SDL_Rect rect)
{

    // tạo màu của khối bằng struct chứa 4 thành phần : R G B A
    SDL_Color color = {255, 255, 0, 255};

    // tạo bitmap trong RAM
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);

    // kiểm tra xem con trỏ surface có phải nullptr
    if (surface == nullptr)
    {
        std::cerr << "không tạo được bitmap trong surface" << std::endl;
    }

    // copy ảnh trong ram sang vram
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    // khối text kích thước và vị trí
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = 10;
    rect.y = 10;

    // đã copy xong trả tài nguyên cho chương trình (ảnh ram -> vram)
    SDL_FreeSurface(surface);

    // trả lại texture
    return texture;
}

// tạo 3 khối chữ cho 3 trạng thái
void BreakOut::createFontResource()
{
    textureMenu = createTextTexture("MENU | chọn RETURN để chơi địt nhau game", textMenu);

    textureGameover = createTextTexture("THUA tí cho mút lồn  | chọn R để về MENU", textGameover);

    textureWin = createTextTexture("THẮNG tí cho bú cu | chọn R đề về MENU", textWin);
}

// tạo bệ đỡ
void BreakOut::renderPlatform()
{
    // tạo một struct của SDL chứa các tham số: vị trí + kích thước của bệ đỡ
    SDL_Rect platform;
    platform.x = static_cast<int>(platformX);
    platform.y = static_cast<int>(platformY);
    platform.w = static_cast<int>(platformWidth);
    platform.h = static_cast<int>(platformHeight);

    // tạo trạng thái màu
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // tô màu cho "bệ đỡ"
    SDL_RenderFillRect(renderer, &platform);
}

// vẽ quả bóng
void BreakOut::renderBall()
{

    SDL_Rect ball; // struct chứa kích thước và vị trí của bóng
    ball.x = static_cast<int>(ballX);
    ball.y = static_cast<int>(ballY);
    ball.w = static_cast<int>(ballSize);
    ball.h = static_cast<int>(ballSize);

    // khởi tạo màu cho qủa bóng
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    // tô màu cho bóng
    SDL_RenderFillRect(renderer, &ball); // dùng & để vào đọc nội dung của bóng để vẽ
}

// vẽ "viên gạch"
void BreakOut::renderBrick()
{
    for (int i = 0; i < 6; i++)
    {
        SDL_Rect brick;
        brick.x = static_cast<int>(brickX) + i * (80 + 100);
        brick.y = static_cast<int>(brickY);
        brick.w = static_cast<int>(brickWidth);
        brick.h = static_cast<int>(brickHeight);
        // thiết lập màu
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // tô màu cho gạch
        SDL_RenderFillRect(renderer, &brick);
    }
}

// vẽ khung chứa: điểm , mạng
void BreakOut::renderFrame()
{

    // vẽ khung ngang
    SDL_Rect frame_horizontal;
    frame_horizontal.x = 0;
    frame_horizontal.y = 100;
    frame_horizontal.w = 1000;
    frame_horizontal.h = 4;

    // vẽ khung dọc
    SDL_Rect frame_vertical;
    frame_vertical.x = (windowMax / 2) - 2;
    frame_vertical.y = 0;
    frame_vertical.w = 4;
    frame_vertical.h = 100;

    // thiết lập màu
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    // tô màu khung
    SDL_RenderFillRect(renderer, &frame_horizontal);
    SDL_RenderFillRect(renderer, &frame_vertical);

    // vẽ điểm
    for (int i = 0; i < points; i++)
    {
        SDL_Rect block_points;
        block_points.x = 10 + i * 25;
        block_points.y = 20;
        block_points.w = 20;
        block_points.h = 20;

        // thiết lập màu
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        // tô màu cho điểm
        SDL_RenderFillRect(renderer, &block_points);
    }

    // vẽ mạng (tạm thời nếu bị va chạm vào đáy + khối chứ chưa trừ được khối)
    // điểm nhỏ hơn 3 tức là chỉ vẽ 3 lần
    int maxHealth = 3;
    for (int i = 0; i < maxHealth - health; i++)
    {
        SDL_Rect block_health;
        block_health.x = 550 + i * 25;
        block_health.y = 20;
        block_health.w = 20;
        block_health.h = 20;

        // thiết lập màu
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        // tô màu cho điểm
        SDL_RenderFillRect(renderer, &block_health);
    }
}
// tiếp theo là sẽ vẽ "cửa sổ" sau khi SDL đã kết nối được với backend của OS để nói chuyện với rendering driver
void BreakOut::render()
{
    // vẽ màn hình : thiết lập trạng thái màu sắc, tô màu, hiển thị
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // tạo điều kiện để điều khiển hình vẽ trong từng trang thái màn hình
    if (currentScreen == Screen::MENU)
    {
        SDL_RenderCopy(renderer, textureMenu, nullptr, &textMenu);
    }
    if (currentScreen == Screen::PLAYING)
    {
        // vẽ "bệ đỡ"
        renderPlatform();
        // vẽ bóng
        renderBall();
        // vẽ "gạch"
        renderBrick();
        // vẽ khung chứa : điểm + mạng
        renderFrame();
    }
    if (currentScreen == Screen::WIN)
    {
        SDL_RenderCopy(renderer, textureWin, nullptr, &textWin);
    }

    if (currentScreen == Screen::GAMEOVER)
    {
        SDL_RenderCopy(renderer, textureGameover, nullptr, &textGameover);
    }

    SDL_RenderPresent(renderer);
}

// tạo hàm xử lý các xử kiện từ phím và chuột
void BreakOut::handleEvents()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            is_running = false;
        }
        // xử lý sự kiện: phím gõ 1 lần để chuyển trạng thái game
        if (event.type == SDL_KEYDOWN)
        {
            std::cout << "phím đang được ấn: " << event.key.keysym.scancode << std::endl;
            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN && currentScreen == Screen::MENU)
            {
                currentScreen = Screen::PLAYING;
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_R && (currentScreen == Screen::GAMEOVER || currentScreen == Screen::WIN))
            {
                std::cout << "đang ở màn MENU" << std::endl;
                currentScreen = Screen::MENU;
            }
        }
    }
}

// sau khi xử lý nhận phím và xác nhận cờ di chuyển ta sẽ cập nhật vị trí
void BreakOut::update(float delta)
{
    // nếu mà điều kiện dừng chương bóng và bệ đúng bỏ qua update để ball và bệ không thể di chuyển
    if (is_platformFrozen == true && is_ballFrozen == true)
    {
        std::cout << "dừng cập nhật update" << std::endl;
        return;
    }

    if (currentScreen == Screen::PLAYING)
    {
        std::cout << "màn chơi" << std::endl;
        // kiểm tra trạng thái của key trong "mảng" xem nó là 0 hay 1 rồi từ đó thay đổi logic di chuyển
        // cái trạng thái phím này là phím "giữ"
        // tham số nullptr nghĩa là không cần nó trả lại tổng số lượng key nó xử lý, và inó sẽ trả lại một "mảng" nằm trong bộ nhớ (vị của từng enum)
        const Uint8 *keyState = SDL_GetKeyboardState(nullptr);

        // dùng toán con trỏ để đi vào trong mảng , vì con trỏ luôn trỏ vào vị trí đầu tiên của mảng mà enum tạo ra , nên là khi dùng 1 biến trong enum thì hoàn toàn có thể dùng pointer là vị trí đầu tiên cộng với luật con trỏ để đến được vị của cái biến đó nằm
        if (keyState[SDL_SCANCODE_A])
        {
            platformX -= platformSpeed * delta;
        }
        if (keyState[SDL_SCANCODE_D])
        {
            platformX += platformSpeed * delta;
        }
        if (keyState[SDL_SCANCODE_LEFT])
        {
            platformX -= platformSpeed * delta;
        }
        if (keyState[SDL_SCANCODE_RIGHT])
        {
            platformX += platformSpeed * delta;
        }

        // DỪNG "bệ" KHI VA CHẠM VỚI TƯỜNG
        if (platformX <= windowMin)
        {
            platformX = windowMin;
        }
        if (platformX >= windowMax - platformWidth)
        {
            platformX = windowMax - platformWidth; // 1000 - 100 = 900 dừng ở đây
        }

        // làm bóng di chuyển
        ballX += ballVelX * delta;
        ballY += ballVelY * delta;

        // va chạm với tường
        if (ballX <= windowMin)
        {
            ballX = windowMin;
            ballVelX = -ballVelX;
        }
        if (ballX >= windowMax - ballSize)
        {
            ballX = windowMax - ballSize;
            ballVelX = -ballVelX;
        }
        // cần chỉnh sửa đoạn này vì nó va chạm với cả khung chứa điểm
        // độ cao của khung là 104  ghi tạm nhưng này vậy (vì thanh ngang cao 4 , thanh dọc 100)
        frameHeight = 100;
        if (ballY <= windowMin + frameHeight + 4)
        {
            ballY = windowMin + frameHeight + 4;
            ballVelY = -ballVelY;
        }
        // va chạm với đáy
        if (ballY >= windowMax - ballSize)
        {
            std::cout << "-1 mạng" << std::endl;
            health += 1;
            ballY = windowMax - ballSize;
            ballVelY = -ballVelY;
        }

        // va chạm với vợt
        bool overlapX = ballX <= platformX + platformWidth && ballX + ballSize >= platformX;
        bool overlapY = ballY + ballSize >= platformY && ballY <= platformY + platformHeight;

        if (overlapX && overlapY && ballVelY > 0)
        {
            ballY = (platformY)-ballSize;
            ballVelY = -ballVelY;

            float middleBall = ballX + (ballSize / 2);
            float middlePlatform = platformX + (platformWidth / 2);
            // chuẩn hóa độ lệch : độ lệch thật sự giữa tâm vợt tâm bóng/ độ lệch tối đa khoảng cách tâm vợt và tâm bóng
            float normalize_offset = (middleBall - middlePlatform) / ((platformWidth / 2) + (ballSize / 2));
            // toc do co dinh
            const float fix_speed = 600.0f;
            ballVelX = fix_speed * normalize_offset;
        }

        // va chạm với viên gạch
        bool overlapBrickX = ballX <= brickX + brickWidth;
        bool overlapBrickY = ballY <= brickY + brickHeight && ballY + ballSize >= brickY;

        if (overlapBrickY && overlapBrickX)
        {

            std::cout << "+1 điểm" << std::endl;
            points += 1;
            ballVelX = -ballVelX;
            ballVelY = -ballVelY;
        }

        // nếu mà 10 điểm thì chiến thắng dừng game
        if (points == 10)
        {
            std::cout << "bạn đã thắng" << std::endl;
            is_platformFrozen = true;
            is_ballFrozen = true;

            // sau khi đã chiến thắng nhảy về màn chiến thắng
            currentScreen = Screen::WIN;
        }

        // nếu mà 0 mạng thì thua dừng game
        if (health == 3)
        {
            std::cout << "bạn đã thua" << std::endl;
            is_platformFrozen = true;
            is_ballFrozen = true;
            currentScreen = Screen::GAMEOVER;
        }
    }

    // sau mà bóng đã có được nhảy về thái : GAMEOVER hoặc WIN
    // thiết lập lại trạng thái của điểm số và cờ
    if (currentScreen == Screen::GAMEOVER || currentScreen == Screen::WIN)
    {
        std::cout << "màn Thắng / KẾT THÚC GAME" << std::endl;
        resetState();
    }
}

// thiết lập lại toàn bộ điểm số và cờ
void BreakOut::resetState()
{
    points = 0;
    health = 0;
    is_platformFrozen = false;
    is_ballFrozen = false;
    ballX = 500;
    ballY = 500;
    platformX = 500;
}
// giờ chạy vòng lặp để gửi lệnh vẽ liên tiếp
void BreakOut::run()
{
    // tạo ra thời gian chên lệch giữa 2 frame (tức thời gian di chuyển)
    Uint32 previousTime = SDL_GetTicks();
    while (is_running == true)
    {
        Uint32 now = SDL_GetTicks();

        float delta = (now - previousTime) / 1000.0f;
        // gắn thời gian hiện tại thành thời gian vừa nãy để tiếp tục đo độ lệch 2 frame mới
        previousTime = now;
        handleEvents();
        update(delta);
        render();
    }
    cleanUp();
}

// dọn dẹp tài nguyên hỏi SDL tạo
void BreakOut::cleanUp()
{

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    std::cout << "hoàn thành trả lại tài nguyên" << std::endl;
}

// dọng tài nguyên của C++
BreakOut::~BreakOut()
{
}