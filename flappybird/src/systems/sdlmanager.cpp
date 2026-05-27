#include <sdlmanager.h>
#include <iostream>

SDLManager::SDLManager():
renderer(nullptr),
window(nullptr),

left_win(0),
right_win(1000),
top_win(0),
down_win(1000)
{}


void SDLManager::destroy()
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

bool SDLManager::init()
{
    // bắt đầu nói chuyện với phần cứng , phần mềm
    // để nhờ xử lý video hộ 
    int result = SDL_Init(SDL_INIT_VIDEO);

    if (result != 0)
    {   
        std::cerr << "SDL system can't open" << std::endl;
        return false;
    }

    bool has_window = create_window();

    if (!has_window)
    {
        return false;
    }

    bool has_renderer = create_renderer();

    if (!has_renderer)
    {
        return false;
    }

    return true;
}

bool SDLManager::create_window()
{
    window = SDL_CreateWindow(
        "sexy bird",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        right_win,
        down_win,
        SDL_WINDOW_SHOWN
    );

    if (!window)
    {
        std::cerr << "can't create window" << std::endl;
        return false;
    }

    return true;
}

bool SDLManager::create_renderer()
{
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer)
    {
        std::cerr << "can't create renderer" << std::endl;
        return false;
    }

    return true;
}

int SDLManager::read_event()
{
    int result = SDL_PollEvent(&event);

    return result;
}

void SDLManager::setup_window()
{
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderPresent(renderer);
}

void SDLManager::draw_everything()
{
    SDL_RenderClear(renderer);
}

