// include
#include <SDL2/SDL.h>
#include <Game.h>
#include <iostream>
#include <cassert>

// CONSTRUCTOR AND INITIALIZE
Game::Game() : running(false),
               window(nullptr),
               renderer(nullptr),
               paddleLeftX(10.0f),
               paddleLeftY(10.0f),
               paddleRightX(970.0f),
               paddleRightY(10.0f),
               paddleSpeed(800.0f),
               ballX(500.0f),
               ballY(500.0f),
               ballVelX(400.0f),
               ballVelY(400.0f) {}

// DESTRUCTOR
Game::~Game()
{
    // cleanUp(): destroy after using done
    cleanUp();
}

// init()
bool Game::init()
{

    std::cout << "starting game..." << std::endl;
    int initResult = SDL_Init(SDL_INIT_VIDEO);

    if (initResult != 0)
    {
        return false;
    }

    window = SDL_CreateWindow(
        "pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000,
        1000,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cerr << "cant create window" << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cerr << "can't create renderer" << std::endl;
        return false;
    }

    running = true;
    return true;
}

// RUN()
void Game::run()
{

    Uint32 preciousTime = SDL_GetTicks();
    while (running)
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - preciousTime) / 1000.0f;
        preciousTime = currentTime;

        render();
        update(deltaTime);
        handleEvents(deltaTime);
    }
}

// update
void Game::update(float delta)
{

    ballX += ballVelX * delta;
    ballY += ballVelY * delta;

    const int windowH = 1000;
    const int windowW = 1000;
    const int ballsize = 30;
    const int paddleW = 20;
    const int paddleH = 100;

    const int stopTopLeft = 0;
    const int stopDownRight = 970;

    // ballX = -ballX
    if (ballX <= stopTopLeft)
    {
        ballX = stopTopLeft;
        ballVelX = -ballVelX;
    }
    if (ballX >= stopDownRight)
    {
        ballX = stopDownRight;
        ballVelX = -ballVelY;
    }
    // ballY = -ballY
    if (ballY <= stopTopLeft)
    {
        ballY = stopTopLeft;
        ballVelY = -ballVelY;
    }
    if (ballY >= stopDownRight)
    {
        ballY = stopDownRight;
        ballVelY = -ballVelY;
    }

    bool overlapLeftX = ballX <= paddleLeftX && ballX + ballsize >= paddleLeftX + paddleW;
    bool overlapLeftY = ballY >= paddleLeftY && ballY + ballsize <= paddleLeftY + paddleH;

    if (overlapLeftX && overlapLeftY && ballVelX < 0)
    {
        ballX = paddleLeftX + paddleW;
        ballVelX = -ballVelX;

        float PaddleCenter = paddleLeftY + paddleW * 0.5f;
        float BallCenter = ballY + ballsize * 0.5f;
        float offset = (BallCenter - PaddleCenter) * ballVelY;
    }
}

// render
void Game::render()
{
    // draw window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // paddleLeft
    SDL_Rect paddleLeft;
    paddleLeft.x = static_cast<int>(paddleLeftX);
    paddleLeft.y = static_cast<int>(paddleLeftY);
    paddleLeft.w = 20;
    paddleLeft.h = 100;

    // paddleRight
    SDL_Rect paddleRight;
    paddleRight.x = static_cast<int>(paddleRightX);
    paddleRight.y = static_cast<int>(paddleRightY);
    paddleRight.w = 20;
    paddleRight.h = 100;

    // ball
    SDL_Rect ball;
    ball.x = static_cast<int>(ballX);
    ball.y = static_cast<int>(ballY);
    ball.w = 30;
    ball.h = 30;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddleLeft);
    SDL_RenderFillRect(renderer, &paddleRight);
    SDL_RenderFillRect(renderer, &ball);
    SDL_RenderPresent(renderer);
}

// handleEvents
void Game::handleEvents(float delta)
{

    const Uint8 *keystate = SDL_GetKeyboardState(nullptr);

    // CONST STOP X Y
    const int stopUpY = 0;
    const int stopDownY = 900;

    if (keystate[SDL_SCANCODE_W])
    {
        paddleLeftY -= paddleSpeed * delta;
    }
    if (keystate[SDL_SCANCODE_S])
    {
        paddleLeftY += paddleSpeed * delta;
    }
    if (keystate[SDL_SCANCODE_UP])
    {
        paddleRightY -= paddleSpeed * delta;
    }
    if (keystate[SDL_SCANCODE_DOWN])
    {
        paddleRightY += paddleSpeed * delta;
    }

    if (paddleLeftY <= stopUpY)
    {
        paddleLeftY = stopUpY;
    }
    if (paddleLeftY >= stopDownY)
    {
        paddleLeftY = stopDownY;
    }
    if (paddleRightY <= stopUpY)
    {
        paddleRightY = stopUpY;
    }
    if (paddleRightY >= stopDownY)
    {
        paddleRightY = stopDownY;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
    }
}

void Game::cleanUp()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}