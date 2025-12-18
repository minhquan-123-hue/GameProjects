#include <Game.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <cassert>

Game::Game() : running(false), window(nullptr), renderer(nullptr) {}

Game::~Game()
{
    cleanUp();
}

bool Game::init()
{

    std::cout << "Start program ..." << "\n\n";

    int initResult = SDL_Init(SDL_INIT_VIDEO);
    assert(initResult == 0 && "fail to init");

    if (initResult != 0)
    {
        std::cout << "fail to init" << std::endl;
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
        std::cout << "fail to create the window" << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cout << "failed to create renderer" << std::endl;
        return false;
    }

    running = true;
    return true; // ???? return true for what
}

void Game::run()
{
    Uint32 lastTick = SDL_GetTicks();
    std::cout << "last Tick: " << lastTick << "\n";
    SDL_Event event;
    while (running)
    {
        Uint32 currentTick = SDL_GetTicks();
        std::cout << "current tick: " << currentTick << "\n";
        float deltaTime = (currentTick - lastTick) / 1000.0f;
        std::cout << "delta time: " << deltaTime << "\n";
        lastTick = currentTick;

        update(deltaTime);
        render();
        handleEvents();
    }
}

void Game::update(float dt)
{
    // what kind of (void)dt ? syntax , keyword, statement , or else... ? , what does "dt" stand for ? why update() not use lastTick and currentTick but run() do ? and in here not have any code to ask cpu how can frames update like the time we want ?
    (void)dt; // silence unused warning
    std::cout << "dt: " << dt << std::endl;
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // what does SDL_Rect do ? how does it behave ? why does it exists ? what does x , y ,w , h mean ? how to align it ?
    SDL_Rect paddle;
    paddle.x = 50;
    paddle.y = 150;
    paddle.w = 20;
    paddle.h = 100;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // why renderer don't need & , but paddle need ? what is the different between * and & ? what does SDL_RenderFillRect do ? how does it behave(or return) ?
    SDL_RenderFillRect(renderer, &paddle);

    SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            std::cout << "end loop" << std::endl;
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
