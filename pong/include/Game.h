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
    void update(float dt);
    void render();
    void handleEvents();
    void cleanUp();

    bool running;

    SDL_Window *window;
    SDL_Renderer *renderer;
    // what does const float do ? what does this division mean ?
    const float targetFrameTime = 1.0f / 60.0f;
};