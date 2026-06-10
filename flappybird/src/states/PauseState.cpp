#include <states/PauseState.h>

PauseState::PauseState():
is_pause(false)
{}

void PauseState::init()
{
    pause_rect.x = 460;
    pause_rect.y = 460;
    pause_rect.w = 150;
    pause_rect.h = 150;

}

void PauseState::input(SDL_Event &event, AudioManager &audio_manager)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_P)
        {
            audio_manager.play_pause_sound();
            is_pause = true;
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_C)
        {
            is_pause = false;
        }
    }
}

void PauseState::render(SDL_Renderer *renderer , IMGManager &img_manager)
{
    SDL_RenderCopy(renderer, img_manager.pause, nullptr, &pause_rect);
}