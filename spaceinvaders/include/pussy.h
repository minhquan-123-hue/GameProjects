#pragma once // các file khác mà include thì chỉ được incluce 1 lần
#include <SDL2/SDL.h>
#include <vector>

class Pussy
{
public:
    Pussy();

    bool loadTexture(SDL_Renderer *renderer);
    void create();

    void render(SDL_Renderer *renderer);
    void clean();

    struct Body
    {
        SDL_Rect rect;
    };

    Body body;
    SDL_Texture *texture;
    std::vector<Body> pussies;
};