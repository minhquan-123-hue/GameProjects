#pragma once
#include <systems/FontManager.h>

class WaitState
{
    public:

    WaitState();

    bool process_logic(float dt, SDL_Renderer *renderer, FontManager &font_manager); // init + update

    void render(SDL_Renderer *renderer , FontManager &font_manager);

    void reset();
    
    float countdown_timer;
    float ct;
    int wait_time;
};