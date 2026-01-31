// sau khi đã khởi tạo header (chữ ký hàm , bản thiết kế ta sẽ làm gì) thì ta sẽ tạo các hàm hoạt động được thật sự ở đây
// vẫn là sử dụng công cụ nào thì nhập khẩu = #include (để preprocessor copy + paste code vào đây) , rồi lát nữa khi compile để mà compiler biết là xem ghi đúng chữ ký mà chưa

#include <Game.h>
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

// tạo constructor(hàm khởi tạo) , initialize tất cả biến thành viên và giá trị ban đầu của nó , để tránh có rác trong biến đó , hoặc con trỏ đó , gây ra undefined behaviors
BreakOut::BreakOut() : window(nullptr), // chưa trỏ tới bất kỳ tài nguyên nào cả
                       renderer(nullptr),
                       running(false) // hệ thống video , cửa sổ, cây bút vẽ chưa được tạo => vòng lặp chưa thể hoạt động
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

    // sau đó là tạo thông số cho cửa sổ mà ta muốn tạo
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

    // sau đó là ta sẽ tạo ra một cây bút để vẽ được "cửa sổ" == window lên màn hình , (chọn backend) tức là API Nói chuyện với rendering driver để điểu kiển GPU/CPU ĐỂ "VẼ"
    renderer = SDL_CreateRenderer(
        window,
        -1,                      // chọn cái backend nào đang hỗ trợ => có thể là Open_GL
        SDL_RENDERER_ACCELERATED // cái cờ này có phải nghĩa là chọn GPU Không ?
    );
    // kiểm tra xem là backend này đã được kết nối với SDL chưa ?
    if (!renderer)
    {
        std::cerr << "không khởi tạo được hệ thống backend: " << SDL_GetError() << std::endl;
        return false;
    }

    // sau khi toàn bộ hệ thống của SDL , cửa sổ, backend hoạt động được rồi , ta sẽ trả về true và thiết lập trạng thái cờ running = true để mà cho vòng lặp chạy được (gửi lệnh vẽ cho GPU)
    running = true;
    return true;
}

// tiếp theo là sẽ vẽ "cửa sổ" sau khi SDL đã kết nối được với backend của OS để nói chuyện với rendering driver
void BreakOut::render()
{
    // vẽ màn hình : thiết lập trạng thái màu sắc, tô màu, hiển thị
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

// tạo hàm xử lý các xử kiện từ phím và chuột
void BreakOut::handleEvents(float delta)
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
    }
}

// giờ chạy vòng lặp để gửi lệnh vẽ liên tiếp
void BreakOut::run()
{
    while (running == true)
    {
        handleEvents(0.0016);
        render();
    }
}

// trả lại tài nguyên cho RAM
BreakOut::~BreakOut()
{
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    SDL_Quit();
    std::cout << "hoàn thành trả lại tài nguyên" << std::endl;
}