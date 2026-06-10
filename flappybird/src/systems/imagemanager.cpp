#include <systems/imagemanager.h>
#include <iostream>

IMGManager::IMGManager():
bg(nullptr),
ground(nullptr),
bird(nullptr),
pipe(nullptr),
copper(nullptr),
silver(nullptr),
gold(nullptr)
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

    if (copper)
    {
        SDL_DestroyTexture(copper);
    }

    if (silver)
    {
        SDL_DestroyTexture(silver);
    }

    if (gold)
    {
        SDL_DestroyTexture(gold);
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

    // medals
    copper = IMG_LoadTexture(renderer , "../assets/images/copper.png");
    silver = IMG_LoadTexture(renderer, "../assets/images/silver.png");
    gold = IMG_LoadTexture(renderer, "../assets/images/gold.png");

    if (!bg || !ground || !bird || !pipe || 
    !copper || !silver || !gold)
    {
        std::cerr << "can't open image path" << std::endl;
        return false;
    }

    return true;
}