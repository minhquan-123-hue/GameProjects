#pragma once
#include <SDL2/SDL.h>

class SDL_Manager
{
    public:

    SDL_Manager();
    ~SDL_Manager();

    void Clean();

    bool Init();
    bool Create_win();
    bool Create_ren();
    void Handle_input(bool is_running);
    void Render();

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Event event;

};