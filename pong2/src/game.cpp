#include <game.h>
#include <iostream>

Pong::Pong() : renderer(nullptr),
               window(nullptr),

               isRunning(false),

               leftWin(0),
               rightWin(1000),
               topWin(0),
               downWin(1000)
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

    createResource();

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
    Uint32 previousTime = SDL_GetTicks();
    while (isRunning)
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - previousTime) / 1000.0f; // đổi ms -> s = / 1000
        previousTime = currentTime;

        handleInputs();
        updateSim(deltaTime);
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

void Pong::updateSim(float deltaTime)
{
    paddle1.updateMovement(1, deltaTime);
    paddle1.updateCollision(topWin, downWin);

    paddle2.updateMovement(2, deltaTime);
    paddle2.updateCollision(topWin, downWin);
}

void Pong::renderFrame()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer); // làm sạch màn hình

    paddle1.render(renderer);
    paddle2.render(renderer);

    SDL_RenderPresent(renderer); // hiển thị
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
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        std::cerr << "không kết được với backend (bộ não phía sau xử lý logic): " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Pong::createResource()
{
    paddle1.create(leftWin + 20, topWin + 20);
    paddle2.create(rightWin - 40, topWin + 20);
}