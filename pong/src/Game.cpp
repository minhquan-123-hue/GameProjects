#include "Game.h"
#include <iostream>

Game::Game() : running(false), window(nullptr), renderer(nullptr) {}

Game::~Game()
{
    cleanUp();
}

bool Game::init()
{
    std::cout << "program run ..." << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(
        "pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        400,
        SDL_WINDOW_SHOWN);

    std::cout << "address of poniter var window: " << window << std::endl;

    std::cout << "flag constats: " << SDL_WINDOWPOS_CENTERED << "," << SDL_WINDOW_SHOWN << std::endl;

    if (!window)
    {
        std::cerr << "[DEBUG] Fail to create window: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    std::cout << "address of pointer var renderer: " << renderer << std::endl;
    std::cout << "flags constant: " << SDL_RENDERER_ACCELERATED << std::endl;

    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        return false;
    }

    running = true;
    return true;
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
                std::cout << "quit bitmask: " << event.type << std::endl;
                running = false;
            }
        }
        int colorstate = SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set state

        int drawcolor = SDL_RenderClear(renderer); // draw

        SDL_RenderPresent(renderer); // display
    }
}

void Game::cleanUp()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}
