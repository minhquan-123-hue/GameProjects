#pragma once
#include <SDL2/SDL_image.h>
#include <vector>

class Sperm
{
public:
    Sperm();
    ~Sperm();

    bool loadTexture(SDL_Renderer *renderer);
    void create(int x, int y);

    void updateMovement();
    void updateCollision();
    void render(SDL_Renderer *renderer);

    struct Body
    {
        SDL_Rect rect;
        float speed;
    };

    Body body;
    std::vector<Body> sperms;
    SDL_Texture *texture;

    void clean();
};
