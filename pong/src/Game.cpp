#include <Game.h>
#include <iostream>
#include <cassert>
#include <SDL2/SDL.h>

// why paddleY == 150.0f and paddleSpeed 300.0f ?
Game::Game() : running(false), window(nullptr), renderer(nullptr), paddleY(150.0f), paddleX(30.0f), paddleSpeed(10.0f) {}

Game::~Game()
{
    cleanUp();
}

bool Game::init()
{

    std::cout << "Program starting ... " << std::endl;

    int count;
    const Uint8 *keystat = SDL_GetKeyboardState(&count);
    for (int i = 0; i < 2; ++i)
    {
        std::cout << "size:" << count << std::endl;
    }

    int initresult = SDL_Init(SDL_INIT_VIDEO);

    if (initresult != 0)
    {
        std::cout << "can't init SDL_INIT_VIDEO" << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000,
        1000,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cout << "fail to create window" << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cout << "can't create renderer" << std::endl;
        return false;
    }

    running = true;
    return true;
}

void Game::run()
{
    Uint32 previoustime = SDL_GetTicks();

    previoustime = previoustime / 1000;
    while (running)
    {

        Uint32 currenttime = SDL_GetTicks();
        float deltatime = currenttime - previoustime;
        deltatime = deltatime / 1000.0f;

        handleEvents();
        update(deltatime);
        render();
    }
}

void Game::update(float dt)
{
    (void)dt;
}

void Game::render()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect paddle;

    paddle.x = paddleX;
    // what does static_cast<int>(paddleY) do ? what does it return ? what does it called in c++ ?
    paddle.y = static_cast<int>(paddleY);
    paddle.h = 100;
    paddle.w = 45;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);
    SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{

    // SDL_GetKeyboardState return Unit8 : first value of the pointer keystate = 0
    //
    const Uint8 *keystate = SDL_GetKeyboardState(nullptr);
    std::cout << "adress" << keystate << std::endl;
    std::cout << "pointer address" << &keystate << std::endl;
    std::cout << "int:" << (int)(*keystate) << std::endl;

    // is keystate[SDL_SCANCODE_A] == (keystate + 26)
    std::cout << "int sdl_scan: " << (int)keystate[SDL_SCANCODE_W] << std::endl;
    if (keystate[SDL_SCANCODE_W])
    {
        // explain this expresstion , why paddleSpeed need to multiply with targetFrameTime
        paddleY -= paddleSpeed * targetFrameTime;
        std::cout << paddleY << std::endl;
    }
    if (keystate[SDL_SCANCODE_D])
    {
        paddleX += paddleSpeed * targetFrameTime;
        std::cout << paddleX << std::endl;
    }
    if (keystate[SDL_SCANCODE_S])
    {
        paddleY += paddleSpeed * targetFrameTime;
        std::cout << paddleY << std::endl;
    }
    if (keystate[SDL_SCANCODE_A])
    {
        paddleX -= paddleSpeed * targetFrameTime;
        std::cout << paddleX << std::endl;
    }

    // explain this condition
    if (paddleY < 0)
    {
        paddleY = 1000;
    }
    // explain this condition
    if (paddleY > 1000)
    {
        paddleY = 0;
    }

    if (paddleX > 1000)
    {
        paddleX = 0;
    }

    if (paddleX < 0)
    {
        paddleX = 1000;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
    }
}

void Game::cleanUp()
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
