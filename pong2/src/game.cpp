#include <game.h>
#include <iostream>

Pong::Pong() : renderer(nullptr),
               window(nullptr),

               isRunning(false)
{
}

Pong::~Pong()
{
    clean();
}

void Pong::clean()
{
    if (window)
    {
        SDL_DestroyWindow(window);
    }

    if (renderer)
    {
        SDL_DestroyRenderer(renderer); // đây là vùng heap [RAM + VRAM]
    }

    SDL_Quit();
}

bool Pong::init()
{
    bool hasVideo = initVideoSys(); // 3 hàm này chưa viết định nghĩa
    bool hasWin = createWin();
    bool hasRen = createRen();

    if (!hasVideo || !hasWin || !hasRen)
    {
        std::cerr << "không khởi tạo tài nguyên thành công: " << SDL_GetError() << std::endl;
        return false;
    }

    isRunning = true;
    return true;
}

void Pong::run()
{
    while (isRunning)
    {
        handleInputs();
        updateSim();
        renderFrame();
    }
}

void Pong::handleInputs()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
    }
}

void Pong::updateSim()
{
}

void Pong::renderFrame()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

bool Pong::initVideoSys()
{
    int initResult = SDL_Init(SDL_INIT_VIDEO);

    if (initResult != 0)
    {
        std::cerr << "hệ thống video không khởi tạo được: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool Pong::createWin()
{
    window = SDL_CreateWindow(
        "Pong",
        0,
        0,
        1000,
        1000,
        SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cerr << "không tạo được cửa sổ: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool Pong::createRen()
{
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr)
    {
        std::cerr << "không kết được với backend (bộ não phía sau xử lý logic): " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}