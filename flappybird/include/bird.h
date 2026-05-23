#pragma once 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Bird
{
    public:

    Bird();
    ~Bird();
    void clean();

    bool init(SDL_Renderer *renderer);
    void input(SDL_Event &event);
    void update(float dt);
    void render(SDL_Renderer *renderer);

    
    private:
    SDL_Texture* bird_texture;
    SDL_Rect rect;
    
    float GRAVITY;
    float velY;
};