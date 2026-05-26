#include <iostream>
#include <pipe.h>


Pipe::Pipe():
texture(nullptr),
speed(100)
{}

Pipe::~Pipe()
{
    clean();
}

void Pipe::clean()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }

}

bool Pipe::init(SDL_Renderer *renderer, int right_win)
{
    texture = IMG_LoadTexture(renderer, "../assets/pipe.png");

    if (!texture)
    {
        std::cerr << "không tạo được texture cho Pipe" << std::endl;
        return false;
    }

    rect.x = right_win;
    rect.y = rand() % 500 + 500;
    rect.w = 200;
    rect.h = 500;

    return true;
}

void Pipe::update(float dt)
{
    rect.x += -speed * dt;
   
}

void Pipe::render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

