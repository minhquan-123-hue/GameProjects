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
    bool create_window();
    bool create_renderer();

    int read_event();
    void setup_window();
    void draw_everything();
    
    SDL_Window *window;

    Window w_size;
    
    SDL_Renderer *renderer;
    SDL_Event event;

};