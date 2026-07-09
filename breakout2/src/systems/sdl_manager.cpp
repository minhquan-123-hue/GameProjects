#include <systems/sdl_manager.h>
#include <iostream>
#include <SDL2/SDL.h>

SDL_Manager::SDL_Manager():
window(nullptr),
renderer(nullptr)
{}

SDL_Manager::~SDL_Manager()
{
    Clean();
}

void SDL_Manager::Clean()
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

bool SDL_Manager::Init()
{
    bool init_result = SDL_Init(SDL_INIT_VIDEO);

    if (init_result != 0)
    {
        std::cerr << "can't connect with sdl" << std::endl;
        return false;
    }

    bool has_win = Create_win();
    bool has_ren = Create_ren();

    if (!has_win | !has_ren)
    {
        return false;
    }

    return true;
}

void SDL_Manager::Handle_input(bool is_running)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.type == SDL_QUIT)
        {
            is_running = false;
        }
    }
}

void SDL_Manager::Render()
{
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

bool SDL_Manager::Create_win()
{
    window = SDL_CreateWindow(
        "breakout2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000,
        1000,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        std::cerr << "can't create window" << std::endl;
        return false;
    }

    return true;
}

bool SDL_Manager::Create_ren()
{
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == nullptr)
    {
        std::cerr << "can't create renderer" << std::endl;
        return false;
    }

    return true;
}