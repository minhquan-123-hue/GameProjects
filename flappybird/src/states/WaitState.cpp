#include <states/WaitState.h>
#include <iostream>

WaitState::WaitState():
countdown_timer(1.75f),
ct(0.0f),
wait_time(3)
{}

bool WaitState::process_logic(float dt,SDL_Renderer *renderer , FontManager &font_manager)
{
    ct += dt;

    if (ct >= countdown_timer)
    {
        ct = 0.0f;
        wait_time -= 1;
    }
    font_manager.create_wait(renderer, wait_time);

    if (wait_time == 0)
    {
        return true;
    }
    return false;
}

void WaitState::render(SDL_Renderer *renderer, FontManager &font_manager)
{   
    SDL_RenderCopy(renderer, font_manager.wait_texture, nullptr, &font_manager.wait_rect);
}