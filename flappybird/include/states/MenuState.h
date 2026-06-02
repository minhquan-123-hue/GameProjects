#pragma once
#include <SDL2/SDL.h>
#include <systems/FontManager.h>

class MenuState
{
    public:

    MenuState();

    void init(SDL_Renderer *renderer , FontManager &font_manager);

    bool input(SDL_Event &event);
    void render(SDL_Renderer *renderer, FontManager &f_manager);


    std::string menu_text; 
};