#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Pipe
{
    public:

    Pipe();
    ~Pipe();

    void clean(); // clean image resource

    bool init(SDL_Renderer *renderer, int right_win);
    void update(float dt);
    void render(SDL_Renderer *renderer);
    
    SDL_Rect rect;

    private:

    SDL_Texture *texture;
    float speed;

};