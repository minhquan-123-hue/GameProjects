#pragma once
#include <SDL2/SDL.h>

#include <systems/FontManager.h>
#include <systems/imagemanager.h>
#include <string>

// object
#include <entities/medals.h>


class LoseState
{
    public:

    LoseState();

    void init(int &score,SDL_Renderer *renderer ,  FontManager &font_manager);

    bool input(SDL_Event &event);

    void render(SDL_Renderer *renderer, FontManager &font_manager, IMGManager &img_manager, int &score);

    std::string lose_text;

    Medals medals;
};