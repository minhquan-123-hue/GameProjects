#include <Game.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cassert>

Game::Game() : running(false), window(nullptr), renderer(nullptr), paddleX(10.0f), paddleY(10.0f), paddleSpeed(10.0f), ballX(10.0f), ballY(10.0f), ballVelX(400.0f), ballVelY(400.0f), collision(false) {}

Game::~Game()
{
    cleanUp();
}

bool Game::init()
{

    std::cout << "program start ..." << std::endl;

    int initResult = SDL_Init(SDL_INIT_VIDEO);
    assert(initResult == 0 && "fail to build foundation");

    if (initResult != 0)
    {
        std::cerr << "fail to build foundation" << std::endl;
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
        std::cerr << "fail to lauch window" << std::endl;
        return false;
    }

    // call "nha thau"
    // ?? tại sao renderer là một pointer variable lại có thể gắn cho function , và khi nó đưa vào hàm SDL_RenderFillRect() nó lại không cần & trong khi nó lại một function ??
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

    std::cout << renderer << std::endl;
    // fail to bargain with "nha thau"
    if (!renderer)
    {
        std::cerr << "fail to launch renderer" << std::endl;
        return false;
    }

    // set running to true
    running = true;
    // return to int main() {} game.init()
    return true;
}

// create game loop: render(), while , update(), handleEvents , deltaTime , Uint32
void Game::run()
{

    // create time that right after SDL init
    Uint32 previousTime = SDL_GetTicks();

    // while loop
    while (running)
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - previousTime) / 1000.0f;

        // fix bugs , use delta not fixed logic
        previousTime = currentTime;

        render();
        update(deltaTime);
        handleEvents();
    }
}
// create render : paddle , ball
void Game::render()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect paddle;
    paddle.x = static_cast<int>(paddleX);
    paddle.y = static_cast<int>(paddleY);
    paddle.w = 30;
    paddle.h = 100;

    SDL_Rect ball;
    ball.x = static_cast<int>(ballX);
    ball.y = static_cast<int>(ballY);
    ball.w = 30;
    ball.h = 30;

    // draw ball, paddle , set color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);
    SDL_RenderFillRect(renderer, &ball);
    SDL_RenderPresent(renderer);
}

// create update: ball, update time frame

// ?? delta la moi frame ma may tinh cap nhat a ? khac gi so voi minh tu tinh thời gian cố định 1.0f / 60.0f ?
void Game::update(float delta)
{
    // move ball

    ballX += ballVelX * delta;
    ballY += ballVelY * delta;

    // top / bottom wall
    // ?? tại sao điểm ảnh của quả bóng , phải phần đuôi của nó chạm vào khoảnh cách nó mới quay lại chứ không phải phần đầu ?
    if (ballY <= 0 || ballY >= 1000 - 30)
    {
        ballVelY = -ballVelY;
    }
    // left / right wall
    if (ballX <= 0 || ballX >= 1000 - 30)
    {
        ballVelX = -ballVelX;
    }

    // ?? tại sao paddle lại cộng thêm 20 và các giải thích toàn bộ các phép tính ở đằng sau ?
    if (ballX <= paddleX + 20 && ballY + 20 >= paddleY && ballY <= paddleY + 100)
    {
        ballVelX = -ballVelX;
        ballX = -ballVelX;
        ballX = paddleX + 20;
    }
}

// handle keystate , quit
void Game::handleEvents()
{
    // ?? keystate ở đây có phải là pointer variable không , tại sao có thể gán pointer variable cho 1 function ?
    const Uint8 *keystate = SDL_GetKeyboardState(nullptr);

    // *(keystate + position_key)
    if (keystate[SDL_SCANCODE_W])
    {
        paddleY -= paddleSpeed * timeFrame;
    }
    if (keystate[SDL_SCANCODE_S])
    {
        paddleY += paddleSpeed * timeFrame;
    }

    if (paddleY > 1000)
    {
        paddleY = 900;
    }
    if (paddleY < 0)
    {
        paddleY = 0;
    }

    // check quit
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
    }
}
// create collision() ??

// cleanUp after going out of the scope
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