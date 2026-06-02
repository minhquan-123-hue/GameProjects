#pragma once
#include <SDL2/SDL_image.h>

class IMGManager
{
    public:

    IMGManager();

    void destroy();

    bool init(SDL_Renderer *renderer);

    SDL_Texture *bg;
    SDL_Texture *bird;
    SDL_Texture *ground;
    SDL_Texture *pipe;

};