// include
#include <Game.h>
#include <iostream>
#include <SDL2/SDL.h>

// contructor , initialize : member struct
Game::Game() : window(nullptr),
               renderer(nullptr),
               running(false),
               paddleLeftX(10.0f),
               paddleLeftY(10.0f),
               paddleRightX(970.0f),
               paddleRightY(10.0f),
               paddleSpeed(500.0f),
               ballX(500.0f),
               ballY(500.0f),
               ballVelX(500.0f),
               ballVelY(500.0f),
               rightPoint(0),
               leftPoint(0),
               currentScreen(Screen::MENU),
               ballFrozen(true) {}

// destructor call cleanUp() after int main in main.cpp out of the scope
Game::~Game()
{
    cleanUp();
}

// init
bool Game::init()
{
    std::cout << "starting game..." << std::endl;

    int initResult = SDL_Init(SDL_INIT_VIDEO);

    if (initResult != 0)
    {
        std::cerr << "can't init";
        return false;
    }

    // create window
    // tôi không hiểu tại sao lại phải tạo window sau khi khởi tạo SDL_Init() , và tại sao window lại nằm trong tham số của renderer và renderer thì làm nhiệm vụ gì ?
    window = SDL_CreateWindow(
        "pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000,
        1000,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cerr << "cant create window";
        return false;
    }

    // create renderer
    // cái tham số "-1" này có ý nghĩa gì ? và nó nằm tầng nào trong phần mềm?
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED

    );

    if (!renderer)
    {
        std::cerr << "Cant create renderer";
        return false;
    }

    running = true;
    return true;
}

// create run:delta, loop , render , handleEvents, update:(resetBall)

void Game::run()
{
    Uint64 previousTime = SDL_GetTicks();
    while (running)
    {
        Uint64 currentTime = SDL_GetTicks();
        float delta = (currentTime - previousTime) / 1000.0f; // convert milisecond to second
        previousTime = currentTime;

        handleEvents(delta);
        update(delta);
        render();
    }
}

// render: ball , paddle: left , right , setstate , draw , change color , draw , show
void Game::render()
{

    // set color state to black
    // tại sao renderer lại ở trong SetRenderDrawColor
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

    // MENU
}

// update
void Game::update(float delta)
{
    if (ballFrozen == true)
    {
        return;
    }
    if (ballFrozen == false)
    {
        // cai nay cap nhat moi frame
        ballX += ballVelX * delta;
        ballY += ballVelY * delta;

        const int ballSize = 30;
        const int paddleW = 20;
        const int paddleH = 100;
        const float minX = 0.0f;
        const float maxX = 1000.0f;
        const float minY = 0.0f;
        const float maxY = 1000.0f;

        // object vs wall
        // add point
        if (ballX <= minX)
        {
            rightPoint++;
            resetBall(-1);
            std::cout << "+1 right" << '\n';
        }
        if (ballX >= maxX - ballSize)
        {
            leftPoint++;
            resetBall(1);
            std::cout << "+1 left" << '\n';
        }

        if (ballY <= minY)
        {
            ballY = minY;
            ballVelY = -ballVelY;
        }
        if (ballY >= maxY - ballSize)
        {
            ballY = maxY - ballSize;
            ballVelY = -ballVelY;
        }

        // object vs object
        // leftpaddle
        bool overlapLeftX = ballX <= paddleLeftX + paddleW;
        bool overlapLeftY = ballY + ballSize >= paddleLeftY && ballY <= paddleLeftY + paddleH;

        if (overlapLeftX && overlapLeftY && ballVelX < 0)
        {
            ballX = paddleLeftX + paddleW;
            ballVelX = -ballVelX;

            // tinh tam bong va tam vot de co duoc do lech
            float paddleCenter = paddleLeftY + (paddleH * 0.5f);
            float ballCenter = ballY + (ballSize * 0.5f);
            float offset = (ballCenter - paddleCenter) / (paddleH * 0.5f); // actualoffset / maxoffset => normalize ratio
            const float maxSpeed = 500.0f;
            ballVelY = offset * maxSpeed;
        }

        // rightpaddle
        bool overlapRightX = ballX + ballSize >= paddleRightX;
        bool overlapRightY = ballY + ballSize >= paddleRightY && ballY <= paddleRightY + paddleH;

        if (overlapRightX && overlapRightY && ballVelX > 0)
        {
            ballX = paddleRightX - paddleW;
            ballVelX = -ballVelX;

            float paddleCenter = paddleRightY + (paddleH * 0.5f);
            float ballCenter = ballY + (ballSize * 0.5f);

            float offset = (ballCenter - paddleCenter) / (paddleH * 0.5f);
            const float maxSpeed = 500.0f;
            ballVelY = offset * maxSpeed;
        }
    }
}

// resetBall
void Game::resetBall(int direction)
{
    const int MAXSCREEN = 1000;
    ballX = MAXSCREEN / 2;
    ballY = MAXSCREEN / 2;
    // after touch wall left or right
    ballVelX = direction * 300.0f;
    ballVelY = 0.0f;
}
// handleEvents
void Game::handleEvents(float delta)
{
    // pointer to address (of an array)
    const Uint8 *statekey = SDL_GetKeyboardState(nullptr);

    // const
    const float paddleH = 100;
    const float min_Y = 0;
    const float max_Y = 1000;

    // FIST SCREEN
    if (currentScreen == Screen::MENU)
    {
        if (statekey[SDL_SCANCODE_RETURN])
        {
            currentScreen = Screen::PLAYING;
            ballFrozen = false;
        }
    }

    // MOVE TO SCREEN PLAYING
    if (currentScreen == Screen::PLAYING)
    {
        // left
        if (statekey[SDL_SCANCODE_W])
        {
            paddleLeftY -= paddleSpeed * delta;
        }
        if (statekey[SDL_SCANCODE_S])
        {
            paddleLeftY += paddleSpeed * delta;
        }
        // right
        if (statekey[SDL_SCANCODE_UP])
        {
            paddleRightY -= paddleSpeed * delta;
        }
        if (statekey[SDL_SCANCODE_DOWN])
        {
            paddleRightY += paddleSpeed * delta;
        }

        // left
        if (paddleLeftY <= min_Y)
        {
            paddleLeftY = min_Y;
        }
        if (paddleLeftY >= max_Y - paddleH)
        {
            paddleLeftY = max_Y - paddleH;
        }
        // right
        if (paddleRightY <= min_Y)
        {
            paddleRightY = min_Y;
        }
        if (paddleRightY >= max_Y - paddleH)
        {
            paddleRightY = max_Y - paddleH;
        }
        // move to SCREEN GAME OVER
        if (rightPoint == 5 || leftPoint == 5)
        {
            currentScreen = Screen::GAMEOVER;
            ballFrozen = true;
        }
    }

    // RESET GAME TO START
    if (currentScreen == Screen::GAMEOVER)
    {
        if (statekey[SDL_SCANCODE_R])
        {
            currentScreen = Screen::MENU;
            ballFrozen = true;
            rightPoint = 0;
            leftPoint = 0;
        }
    }

    // check quit
    // create normal var type sdl_envent
    SDL_Event event;

    // use SDL_PollEvent and & to access value inside that address
    // loop
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
    }
}
// cleanUps
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
