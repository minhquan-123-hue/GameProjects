#include <game.h>
#include <iostream>

Pong::Pong() : renderer(nullptr),
               window(nullptr),

               isRunning(false),

               leftWin(0),
               rightWin(1000),
               topWin(0),
               downWin(1000), 

               scoreL(0),
               scoreR(0),

               currentState(State::MENU)
{
}

Pong::~Pong()
{
    clean();
}

void Pong::clean()
{
    if (window)
    {
        SDL_DestroyWindow(window);
    }

    if (renderer)
    {
        SDL_DestroyRenderer(renderer); // đây là vùng heap [RAM + VRAM]
    }

    SDL_Quit();
}

bool Pong::init()
{
    bool hasVideo = initVideoSys(); // 3 hàm này chưa viết định nghĩa
    bool hasWin = createWin();
    bool hasRen = createRen();

    createResource();

    if (!hasVideo || !hasWin || !hasRen)
    {
        std::cerr << "không khởi tạo tài nguyên thành công: " << SDL_GetError() << std::endl;
        return false;
    }

    isRunning = true;
    return true;
}

void Pong::run()
{
    Uint32 previousTime = SDL_GetTicks();
    while (isRunning)
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - previousTime) / 1000.0f; // đổi ms -> s = / 1000
        previousTime = currentTime;

        handleInputs();
        updateSim(deltaTime);
        renderFrame();
    }
}

void Pong::handleInputs()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN && currentState == State::MENU)
            {
                currentState = State::PLAYING;
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_R && currentState == State::PLAYER1_WIN)
            {
                currentState = State::MENU;
                resetScore();
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_R && currentState == State::PLAYER2_WIN)
            {
                currentState = State::MENU;
                resetScore();
            }
        }
    }
}

void Pong::updateSim(float deltaTime)
{
    if (currentState == State::PLAYING)
    {
        updateScore();

        paddle1.updateCollision(topWin, downWin);
        paddle1.updateMovement(1, deltaTime);

        paddle2.updateCollision(topWin, downWin);
        paddle2.updateMovement(2, deltaTime);

        ball.updateCollision(topWin, downWin, paddle1, paddle2);
        ball.updateMovement(deltaTime);
    }
    
}

void Pong::renderFrame()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer); // làm sạch màn hình

    paddle1.render(renderer);
    paddle2.render(renderer);

    ball.render(renderer);

    renderScore();
    
    SDL_RenderPresent(renderer); // hiển thị
}

bool Pong::initVideoSys()
{
    int initResult = SDL_Init(SDL_INIT_VIDEO);

    if (initResult != 0)
    {
        std::cerr << "hệ thống video không khởi tạo được: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool Pong::createWin()
{
    window = SDL_CreateWindow(
        "Pong",
        0,
        0,
        1000,
        1000,
        SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cerr << "không tạo được cửa sổ: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool Pong::createRen()
{
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        std::cerr << "không kết được với backend (bộ não phía sau xử lý logic): " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Pong::createResource()
{
    paddle1.create(leftWin + 20, topWin + 20);
    paddle2.create(rightWin - 40, topWin + 20);
    ball.create();
}

void Pong::updateScore()
{
    if (ball.coor.rect.x < leftWin)
    {
        scoreR += 1;
        std::cout << "+1 paddle right" << std::endl;
        ball.resetPos(1);
    }

    if (ball.coor.rect.x + ball.coor.rect.h > rightWin)
    {
        scoreL += 1;
        std::cout << "+1 paddle left" << std::endl;
        ball.resetPos(-1);
    }

    if (scoreR == 10)
    {
        std::cout << "paddle right win" << std::endl;
        currentState = State::PLAYER2_WIN;
        
    }
    if (scoreL == 10)
    {
        std::cout << "paddle left win" << std::endl;
        currentState = State::PLAYER1_WIN;
    }
}

void Pong::renderScore()
{
    for (int i = 0; i < scoreL;i++)
    {
        rectScoreL.x = 20 + i * 20;
        rectScoreL.y = 20;
        rectScoreL.w = 15;
        rectScoreL.h = 15;


        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderFillRect(renderer, &rectScoreL);
    }

    for (int i = 0; i < scoreR;i++)
    {
        rectScoreR.x = 600 + i * 20;
        rectScoreR.y = 20;
        rectScoreR.w = 15;
        rectScoreR.h = 15;

        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderFillRect(renderer, &rectScoreR);
    }
}

void Pong::resetScore()
{
    scoreL = 0;
    scoreR = 0;

    ball.coor.rect.x = 500;
    ball.coor.rect.y = 500;
}