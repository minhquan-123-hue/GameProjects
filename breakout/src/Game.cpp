// sau khi đã khởi tạo header (chữ ký hàm , bản thiết kế ta sẽ làm gì) thì ta sẽ tạo các hàm hoạt động được thật sự ở đây
// vẫn là sử dụng công cụ nào thì nhập khẩu = #include (để preprocessor copy + paste code vào đây) , rồi lát nữa khi compile để mà compiler biết là xem ghi đúng chữ ký mà chưa

#include <Game.h>
#include <SDL2/SDL.h>
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
                       ballVelX(30.0f),
                       ballVelY(30.0f),
                       // wall min max
                       windowMax(1000.0f),
                       windowMin(0.0f)

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

    // sau khi toàn bộ hệ thống của SDL , cửa sổ, backend hoạt động được rồi , ta sẽ trả về true và thiết lập trạng thái cờ running = true để mà cho vòng lặp chạy được (gửi lệnh vẽ cho GPU)
    is_running = true;
    return true;
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
// tiếp theo là sẽ vẽ "cửa sổ" sau khi SDL đã kết nối được với backend của OS để nói chuyện với rendering driver
void BreakOut::render()
{
    // vẽ màn hình : thiết lập trạng thái màu sắc, tô màu, hiển thị
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // vẽ "bệ đỡ"
    renderPlatform();
    // vẽ bóng
    renderBall();

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
    }
}

// sau khi xử lý nhận phím và xác nhận cờ di chuyển ta sẽ cập nhật vị trí
void BreakOut::update(float delta)
{

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
    ballY -= ballVelY * delta;

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
    if (ballY <= windowMin)
    {
        ballY = windowMin;
        ballVelY = -ballVelY;
    }
    if (ballY >= windowMax - ballSize)
    {
        ballY = windowMax - ballSize;
        ballVelY = -ballVelY;
    }

    // va chạm với vợt
    bool overlapX = ballX <= platformX + platformWidth && ballX + ballSize >= platformX;
    bool overlapY = ballY + ballSize >= platformY + platformHeight;

    if (overlapX && overlapY && ballVelY > 0)
    {
        ballY = (platformY)-ballSize;
        ballVelX = -ballVelX;
    }
}

// giờ chạy vòng lặp để gửi lệnh vẽ liên tiếp
void BreakOut::run()
{
    // tạo ra thời gian chên lệch giữa 2 frame (tức thời gian di chuyển)
    Uint32 previousTime = SDL_GetTicks();
    std::cout << "previousTime: " << previousTime << std::endl;
    while (is_running == true)
    {
        Uint32 now = SDL_GetTicks();
        std::cout << "now: " << now << std::endl;

        float delta = (now - previousTime) / 1000.0f;
        std::cout << "delta: " << delta << std::endl;
        // gắn thời gian hiện tại thành thời gian vừa nãy để tiếp tục đo độ lệch 2 frame mới
        previousTime = now;
        std::cout << "previous: " << previousTime << std::endl;
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