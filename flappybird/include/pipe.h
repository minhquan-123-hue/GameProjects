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
    void update(float dt, int down_win);
    void render(SDL_Renderer *renderer);
    
    void spawn(float dt, int down_win);
    void movement(float dt);
    void clear();

    private:

    SDL_Texture *texture;
    SDL_Rect rect;
    float speed;

    float spawn_timer;
    std::vector<SDL_Rect> pipes;
};