
#include <iostream>
#include <SDL2/SDL.h>
#include <game.h>

// tạo constructor
SpaceInvaders::SpaceInvaders() : renderer(nullptr),
                                 window(nullptr),

                                 isRunning(false)
{
}

bool SpaceInvaders::init()
{

    // khởi tạo hệ thống SDL , chắc là đoạn này là nạp code của SDL từ ssd vào ram phải không ?

    int initResult = SDL_Init(SDL_INIT_VIDEO);

    if (initResult != 0)
    {
        std::cout << "không khởi tạo hệ thống video thành công: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "SpaceInvaders",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000,
        1000,
        0);

    // ! là đảo logic , nếu mà pointer thì sai không chạy thân code , nếu mà nullpointer thì false false = true chạy thân code
    if (!window)
    {
        std::cout << "không khởi tạo được cửa sổ: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        0 // mình không biết cái tham số này là biểu diễn cho cái gì
    );

    // kiểm tra có backend hỗ trợ không
    if (!renderer) // dùng ! để đảo logic , nếu true tức có backend đảo thành false => vòng lặp không chạy , nếu false đảo thành true và bên trong câu điều kiện sẽ chạy
    {
        std::cout << "backend không hỗ trợ: " << SDL_GetError() << std::endl;
        return false;
    }

    isRunning = true;
    return true;
}

void SpaceInvaders::handleEvents()
{

    SDL_Event event;

    if (SDL_PollEvent(&event) == SDL_QUIT)
    {
        isRunning = false;
    }
}

// sau khi đã nạp code của sdl bắt đầu tạo lệnh vẽ theo chỉ số sau đây
void SpaceInvaders::renderFrame()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

// sau khi đã vẽ rồi giờ tạo vòng lặp để gọi lệnh vẽ liên tục
void SpaceInvaders::run()
{

    while (isRunning)
    {
        handleEvents();
        renderFrame();
    }
}

// xóa tài nguyên của SDL khi không còn xử dụng nữa
void SpaceInvaders::cleanUp()
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
}

// gọi destructor để xóa tài nguyên của C++
SpaceInvaders::~SpaceInvaders()
{
    cleanUp();
}