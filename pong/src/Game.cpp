#include <Game.h>
#include <iostream>
#include <cassert>
#include <SDL2/SDL.h>

Game::Game() : running(false), window(nullptr), renderer(nullptr) {}

Game::~Game()
{
    cleanUp();
}

bool Game::init()
{

    std::cout << "Program starting ... " << std::endl;

    int initresult = SDL_Init(SDL_INIT_VIDEO);

    if (initresult != 0)
    {
        std::cout << "can't init SDL_INIT_VIDEO" << std::endl;
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
        std::cout << "fail to create window" << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cout << "can't create renderer" << std::endl;
        return false;
    }

    running = true;
    return true;
}

void Game::run()
{
    Uint32 previoustime = SDL_GetTicks();
    std::cout << "previoustime: " << previoustime << std::endl;
    previoustime = previoustime / 1000;
    while (running)
    {

        Uint32 currenttime = SDL_GetTicks();
        float deltatime = currenttime - previoustime;
        deltatime = deltatime / 1000.0f;
        std::cout << deltatime << std::endl;
        previoustime = currenttime;

        handleEvents();
        update(deltatime);
        render();
    }
}

void Game::update(float dt)
{
    (void)dt;
}

void Game::render()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect paddle;
    paddle.x = 30;
    paddle.y = 50;
    paddle.h = 100;
    paddle.w = 45;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);
    SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
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
