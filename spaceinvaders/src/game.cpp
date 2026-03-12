
#include <iostream>
#include <SDL2/SDL.h>
#include <game.h>

// tạo constructor
SpaceInvaders::SpaceInvaders() : renderer(nullptr),
                                 window(nullptr),

                                 isRunning(false)
{
}

void SpaceInvaders::init()
{

    int initResult = SDL_Init(SDL_INIT_VIDEO);

    if (initResult != 0)
    {
        std::cout << "không khởi tạo hệ thống video thành công: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow(
        "SpaceInvaders",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000,
        1000,
        0);

    // ! là đảo logic , nếu mà pointer thì sai không chạy thân code , nếu mà nullpointer thì false false = true chạy thân code
    if (!window)
    {
        std::cout << "không khởi tạo được cửa sổ: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_ACCELERATED_BACKEND)
}