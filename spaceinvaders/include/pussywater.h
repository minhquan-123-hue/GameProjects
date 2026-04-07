#pragma once // include file này chỉ được 1 lần
#include <SDL2/SDL.h>
#include <vector>

class PussyWater
{
public:
    PussyWater();
    ~PussyWater();

    bool loadTexture(SDL_Renderer *renderer);
    void create(int x, int y);

    void updateMovement();
    void updateCollision(int bottomWall);

    void render(SDL_Renderer *renderer);
    void clean();

    struct Body
    {
        SDL_Rect rect;
        float speed;
    };

    Body pussyWater;
    std::vector<Body> watersSystem;

private:
    SDL_Texture *texture;
};