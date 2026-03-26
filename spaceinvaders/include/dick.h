#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Dick
{
public:
    Dick();

    bool loadTexture(SDL_Renderer *renderer);
    void create();

    void updateMovement();
    void updateCollision(int leftWall, int rightWall);
    void render(SDL_Renderer *renderer);
    void clean();

    struct Body
    {
        SDL_Rect rect;
        float speed;
    };

    Body body;
    SDL_Texture *texture;
};