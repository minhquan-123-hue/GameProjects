#include <systems/imagemanager.h>
#include <iostream>

IMGManager::IMGManager():
bg(nullptr),
ground(nullptr),
bird(nullptr),
pipe(nullptr)
{}

void IMGManager::destroy()
{
    if (bg)
    {
        SDL_DestroyTexture(bg);
    }

    if (ground)
    {
        SDL_DestroyTexture(ground);

    }

    if (bird)
    {
        SDL_DestroyTexture(bird);
    }

    if (pipe)
    {
        SDL_DestroyTexture(pipe);
    }

    IMG_Quit();
}

bool IMGManager::init(SDL_Renderer *renderer)
{
    int result = IMG_Init(IMG_INIT_PNG);
    
    if (result == 0)
    {
        std::cerr << "can't init IMG handler system" << std::endl;
        return false;
    }

    bg = IMG_LoadTexture(renderer, "../assets/images/background_lab.png");
    ground = IMG_LoadTexture(renderer, "../assets/images/ground.png");
    bird = IMG_LoadTexture(renderer, "../assets/images/bird.png");
    pipe = IMG_LoadTexture(renderer, "../assets/images/pipe.png");

    if (!bg || !ground || !bird || !pipe)
    {
        std::cerr << "can't open image path" << std::endl;
        return false;
    }

    return true;
}