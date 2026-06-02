#include <systems/FontManager.h>
#include <iostream>

FontManager::FontManager():
menu_texture(nullptr),
wait_texture(nullptr),
play_texture(nullptr),
lose_texture(nullptr),
font(nullptr)
{}

void FontManager::destroy()
{
    if (menu_texture)
    {
        SDL_DestroyTexture(menu_texture);
    }

    if (wait_texture)
    {
        SDL_DestroyTexture(wait_texture);
    }

    if (play_texture)
    {
        SDL_DestroyTexture(play_texture);
    }

    if (lose_texture)
    {
        SDL_DestroyTexture(lose_texture);
    }

    if (font)
    {
        TTF_CloseFont(font);
    }

    TTF_Quit();
}

bool FontManager::init()
{
    int result = TTF_Init();

    if (result == -1)
    {
        std::cerr << "can't connect font_handler" << std::endl;
        return false;
    }

    font = TTF_OpenFont("../assets/fonts/font.ttf", 55);

    if (!font)
    {
        std::cerr << "can't store the path of font" << std::endl;
        return false;
    }

    return true;
}

SDL_Texture* FontManager::copy_texture_to_vram(SDL_Renderer *renderer, SDL_Rect &rect, std::string &text)
{
    SDL_Color color = {255,255,255,255};

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (!surface)
    {
        std::cerr << "can't creat surface" << std::endl;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!texture)
    {
        std::cerr << "can't create texture" << std::endl;

    }

    rect.w = surface->w;
    rect.h = surface->h;

    SDL_FreeSurface(surface);

    return texture;
}

void FontManager::create_menu(SDL_Renderer *renderer, std::string &menu_text)
{
    menu_rect.x = 0;
    menu_rect.y = 0;
    menu_texture = copy_texture_to_vram(renderer, menu_rect, menu_text);
}

void FontManager::create_lose(SDL_Renderer *renderer, std::string &lose_text, int &score)
{

}