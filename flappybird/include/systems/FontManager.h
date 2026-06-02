#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class FontManager
{
    public:

    FontManager();

    void destroy();

    bool init(); 

    SDL_Texture* copy_texture_to_vram(SDL_Renderer *renderer , SDL_Rect &rect, std::string &text);

    // string in this fucntion is static
    // so we don't need to take parameter from other objects
    void create_menu(SDL_Renderer *renderer, std::string &menu_text);
    void create_lose(SDL_Renderer *renderer, std::string &lose_text,int &score);

    // take from object: PlaytState , WaitState
    void create_play(SDL_Renderer *renderer, std::string &play_text, int &score);
    void create_wait(SDL_Renderer *renderer, std::string &wait_text, int &count_down);
    
    TTF_Font *font;

    SDL_Texture *menu_texture;
    SDL_Rect menu_rect;

    SDL_Texture *wait_texture;
    SDL_Rect wait_rect;

    SDL_Texture *play_texture;
    SDL_Rect play_rect;

    SDL_Texture *lose_texture;
    SDL_Rect lose_rect;

};