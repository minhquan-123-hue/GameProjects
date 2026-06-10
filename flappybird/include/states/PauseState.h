#pragma once
#include <systems/imagemanager.h>
#include <systems/AudioManager.h>
#include <SDL2/SDL.h>

class PauseState
{
    public:

    PauseState();

    void init();

    void input(SDL_Event &event, AudioManager &audio_manager);
    void render(SDL_Renderer *renderer , IMGManager &img_manager);

    SDL_Rect pause_rect;

    bool is_pause;
};