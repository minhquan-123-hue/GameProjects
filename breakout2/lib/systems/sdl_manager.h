#pragma once
#include <SDL2/SDL.h>


struct Window
{
    // window size
    int left;
    int right;
    int top;
    int down;   
};


class SDLManager
{
    public:

    SDLManager();


    void destroy();

    bool init();
    bool create_Window();
    bool create_Renderer();

    int read_Event();
    void setup_Window();
    void draw_Everything();
    
    SDL_Window *window;

    Window w_size;
    
    SDL_Renderer *renderer;
    SDL_Event event;

};