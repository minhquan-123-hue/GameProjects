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
    float paddleY;
    float paddleX;
    float paddleSpeed;
    const float targetFrameTime = 1.0f / 60.0f;
};