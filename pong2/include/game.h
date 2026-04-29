#pragma once
#include <SDL2/SDL.h>

// tạo object Paddle, Ball
#include <ball.h>

class Pong
{
public:
    Pong();
    ~Pong();

    bool init();
    void run();

private:
    bool initVideoSys();
    bool createWin();
    bool createRen();
    void createResource();

    void handleInputs();
    void updateSim(float deltaTime);
    void renderFrame();

    void clean();

    bool isRunning;

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Event event;

    // kích thước của sổ
    int leftWin;
    int rightWin;
    int topWin;
    int downWin;

    // tạo object
    Paddle paddle1;
    Paddle paddle2;
    Ball ball;
};
