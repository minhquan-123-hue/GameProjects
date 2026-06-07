#pragma once
#include <entities/pipe.h>
#include <SDL2/SDL.h>

// systems
#include <systems/AudioManager.h>

class Bird
{
    public:
    
    Bird();

    void init();
    void input(SDL_Event &event, AudioManager &audio_manager);
    void process_logic(float dt);
    void render(SDL_Renderer *renderer, SDL_Texture *bird_texture);
    bool collide(Pipe &pipe);


    SDL_Rect rect;

    float velY;

    float GRAVITY;
};
