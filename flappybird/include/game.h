#pragma once 
#include <SDL2/SDL.h>

// tạo objects == cách thêm phần khai báo
// bản thiết kế của object 
#include <background.h>
#include <ground.h>
#include <bird.h>

class Game
{
    public:

    Game();
    ~Game();

    bool init();
    void run();
    
    private:

    void clean_Up();


    // kết nối với phần cứng
    bool wakeup_SDL();
    bool create_Win();
    bool connect_Backend();
    bool image_Handler();


    void handle_Input();
    void update_Sim(float dt);
    void render_Frame();


    // SDL vars 
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    // Window 
    int top_win;
    int down_win;
    int left_win;
    int right_win;
    
    // flags 
    bool is_Running;

    // tạo object
    Background background;
    Ground ground;
    Bird bird;
};
