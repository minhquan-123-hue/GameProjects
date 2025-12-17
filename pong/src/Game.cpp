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

    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                std::cout << "end loop" << std::endl;
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
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
