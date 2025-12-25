// include SDL2/SDL.2

#pragma once
#include <SDL2/SDL.h>

// declare class class_name
class Game
{
    // function use outside
public:
    // Constructor
    Game();
    // Destructor
    ~Game();

    // INIT()
    bool init();
    // run()
    void run();

    // function only class can access
private:
    // 4 function: handleEvents , render, cleanUp, update
    void render();
    void handleEvents(float delta);
    void update(float delta);
    void cleanUp();
    void resetBall(int direction);

    // running
    bool running;
    // SDL
    SDL_Window *window;
    SDL_Renderer *renderer;
    // paddleLeft
    float paddleLeftX;
    float paddleLeftY;
    // paddleRight
    float paddleRightX;
    float paddleRightY;
    // paddleSpeed
    float paddleSpeed;
    // ball
    float ballX;
    float ballY;
    // ballVel
    float ballVelX;
    float ballVelY;
    // score
    int scoreLeft = 0;
    int scoreRight = 0;
};