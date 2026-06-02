#include <states/MenuState.h>
#include <string>
#include <iostream>

MenuState::MenuState():
menu_text("SEXY BIRD,PRESS RETURN TO PLAY")
{
}

void MenuState::init(SDL_Renderer *renderer, FontManager &font_manager)
{
    font_manager.create_menu(renderer, menu_text);

    std::cout << font_manager.menu_texture << std::endl;
}

bool MenuState::input(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
        {
            return true;
        }
    }

    return false;
}

void MenuState::render(SDL_Renderer *renderer , FontManager &font_manager)
{
    SDL_RenderCopy(renderer, font_manager.menu_texture, nullptr, &font_manager.menu_rect);
}