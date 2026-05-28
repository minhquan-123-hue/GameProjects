#include <systems/sdlmanager.h>
#include <iostream>

SDLManager::SDLManager():
renderer(nullptr),
window(nullptr)
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
    // create window size ,pos
    w_size.left = 0;
    w_size.right = 1000;
    w_size.top = 0;
    w_size.down = 1000;

    window = SDL_CreateWindow(
        "sexy bird",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w_size.right,
        w_size.down,
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

