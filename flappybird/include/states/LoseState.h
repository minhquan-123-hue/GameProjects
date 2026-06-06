#pragma once
#include <SDL2/SDL.h>
#include <systems/FontManager.h>
#include <string>

class LoseState
{
    public:

    LoseState();

    void init(int &score,SDL_Renderer *renderer ,  FontManager &font_manager);

    bool input(SDL_Event &event);

    void render(SDL_Renderer *renderer, FontManager &font_manager);

    std::string lose_text;
};