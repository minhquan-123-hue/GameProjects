#pragma once
#include <SDL2/SDL.h>

// tạo object Paddle, Ball
#include <ball.h>
#include <paddle.h>
#include <font.h>

class Pong
{
public:
    Pong();
    ~Pong();

    bool init();
    void run();

private:

    enum class State
    {
        MENU,
        PLAYING,
        PLAYER1_WIN,
        PLAYER2_WIN
    };

    State currentState;
    
    bool initVideoSys();
    bool createWin();
    bool createRen();
    void createResource();

    void handleInputs();
    void updateSim(float deltaTime);
    void updateScore();
    void resetScore();
    void renderFrame();
    void renderScore();

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

    // tạo điểm ăn cho vợt
    int scoreL;
    SDL_Rect rectScoreL;
    int scoreR;
    SDL_Rect rectScoreR;

    // tạo object
    Paddle paddle1;
    Paddle paddle2;
    Ball ball;
    Font font;
};
