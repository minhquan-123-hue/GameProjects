#include "../../lib/systems/sdl_manager.h"

#include <iostream>

SDLManager::SDLManager():
window(nullptr),
renderer(nullptr)
{
    w_size.left = 0;
    w_size.right = 800;
    w_size.top = 0;
    w_size.down = 600;
}

void SDLManager::destroy()
{
    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

bool SDLManager::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

bool SDLManager::create_Window()
{
    window = SDL_CreateWindow(
        "Breakout 2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w_size.right,
        w_size.down,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

bool SDLManager::create_Renderer()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

int SDLManager::read_Event()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return 1;
        }

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            return 2;
        }
    }

    return 0;
}

bool SDLManager::pollEvent(SDL_Event &outEvent)
{
    if (SDL_PollEvent(&outEvent))
    {
        // keep a copy in the manager's last-event as well
        event = outEvent;
        return true;
    }
    return false;
}

void SDLManager::setup_Window()
{
    if (renderer == nullptr)
    {
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SDLManager::draw_Everything()
{
    if (renderer != nullptr)
    {
        SDL_RenderPresent(renderer);
    }
}
