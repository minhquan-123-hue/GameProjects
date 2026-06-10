#pragma once
#include <SDL2/SDL.h>
#include <systems/imagemanager.h>

class Medals
{
    public:

    Medals();

    void init();
    void render(SDL_Renderer *renderer ,IMGManager &img_manager, int &score);

    SDL_Rect copper_rect;
    SDL_Rect silver_rect;
    SDL_Rect gold_rect;
};