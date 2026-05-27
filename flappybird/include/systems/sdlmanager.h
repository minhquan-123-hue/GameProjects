#include <SDL2/SDL.h>

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

    // window size
    int left_win;
    int right_win;
    int top_win;
    int down_win;
    
    SDL_Renderer *renderer;
    SDL_Event event;

};