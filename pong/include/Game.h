#pragma once
#include <SDL2/SDL.h>

class Game
{
public:
    Game();
    ~Game();

    bool init();
    void run();

private:
    void handleEvents();
    void render();
    void cleanUp();

    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
};