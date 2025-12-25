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
        handleEvents(deltaTime);
        update(deltaTime);
    }
}

// resetBall(int direction )
void Game::resetBall(int direction)
{
    // tôi nên viết số trực tiếp như thế này , hay tạo ra một biến ngay từ ban đầu quy định , và các biến tạo ở trong Game::Game(): gọi là gì , member variable à ?
    ballX = 1000 / 2.0f;
    ballY = 1000 / 2.0f;

    // mỗi lần gắn trạng thái mới cho tốc độ của quả bóng là toàn bộ , trạng thái trước đó sẽ bị viết đè lên đúng không ? sau đó khi va chạm tiếp nó sẽ xử dụng vật lý của cái va chạm cạnh đúng không ?
    ballVelX = direction * 300.0f;
    ballVelY = 0.0f;
}

// update
void Game::update(float delta)
{

    ballX += ballVelX * delta;
    ballY += ballVelY * delta;

    const int ballsize = 30;
    const int paddleW = 20;
    const int paddleH = 100;

    // ballX = -ballX
    if (ballX <= 0)
    {
        ballX = 0;
        ballVelX = -ballVelX;
    }
    if (ballX >= 1000)
    {
        ballX = 1000;
        ballVelX = -ballVelX;
    }
    // ballY = -ballY
    if (ballY <= 0)
    {
        ballY = 0;
        ballVelY = -ballVelY;
    }
    if (ballY >= 1000)
    {
        ballY = 1000;
        ballVelY = -ballVelY;
    }

    bool overlapLeftX = ballX <= paddleLeftX + paddleW;
    bool overlapLeftY = ballY + ballsize >= paddleLeftY && ballY <= paddleLeftY + paddleH;

    if (overlapLeftX && overlapLeftY && ballVelX < 0)
    {
        ballX = paddleLeftX + paddleW;
        ballVelX = -ballVelX;

        float PaddleCenter = paddleLeftY + paddleH * 0.5f;
        float BallCenter = ballY + ballsize * 0.5f;
        float offset = (BallCenter - PaddleCenter) / (paddleH * 0.5f);
        const float MAX_Y_SPEED = 500.0f;
        ballVelY = offset * MAX_Y_SPEED;
    }

    bool overlapRightX = ballX + ballsize >= paddleRightX;
    bool overlapRightY = ballY + ballsize >= paddleRightY && ballY <= paddleRightY + paddleH;

    if (overlapRightX && overlapRightY && ballVelX > 0)
    {

        ballX = paddleRightX - ballsize;
        ballVelX = -ballVelX;

        float paddleCenter = paddleRightY + paddleH * 0.5f;
        float ballCenter = ballY + ballsize * 0.5f;
        float offset = (ballCenter - paddleCenter) / (paddleH * 0.5f);
        const float MAX_Y_SPEED = 500.0f;
        ballVelY = offset * MAX_Y_SPEED;
    }

    // score
    // tại sao khi đập vào tường nó chỉ tính khi là đập vào tường bên trái không phải khi đập lên trên cũng là nhỏ hơn 0 à ?
    if (ballX <= 0)
    {
        // cái ++ là đang làm cái gì ? nếu nó là cộng thì thì nó có biết tổng số lần đã chạm vào một bên là bao nhiêu không ?
        scoreRight++;
        std::cout << "score +1 left" << std::endl;
        // tại sao hàm resetBall lại để ở đây ? và nên gọi nó là function hay là method , tôi hay vướng chỗ gọi này ? khi nào gọi là method khi nào thì gọi là hàm ?
        resetBall(+1);
    }

    if (ballX >= 1000)
    {
        scoreLeft++;
        std::cout << "score +1 right" << std::endl;
        resetBall(-1);
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