#include <iostream>
#include <algorithm>
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

    return true;
}

void Pipe::update(float dt, int down_win)
{
    clear();
    spawn(dt,down_win);
    movement(dt);
}

void Pipe::render(SDL_Renderer *renderer)
{
    for (auto &pipe : pipes)
    {
        SDL_RenderCopy(renderer, texture, nullptr, &pipe);
    }
}

void Pipe::spawn(float dt, int down_win)
{
    spawn_timer += dt;

    if (spawn_timer >= 2.5f)
    {
        rect.y = rand() % (down_win / 2) + down_win / 2;
        rect.w = 200;
        rect.h = 700;

        pipes.emplace_back(rect);
        spawn_timer = 0;
    }
}

void Pipe::movement(float dt)
{
    for (auto &pipe : pipes)
    {
        pipe.x += -speed * dt;
    }
}

void Pipe::clear()
{
    auto it_middle = std::remove_if(
        pipes.begin(),
        pipes.end(),
        [](auto &pipe){return pipe.x < -pipe.w;}
    ); // alighn dynamic arrays [matched values from the middle to the left]

    pipes.erase(it_middle , pipes.end()); // delete that SDL_Rect have x out of the screen

}