#include <pipes.h>
#include <random>
#include <algorithm>
#include <iostream>

Pipe::Pipe(): 
pipe_texture(nullptr),
velX(100),
spawn_timer(0),
y_random(0)
{}

Pipe::~Pipe()
{
    clean();
}

void Pipe::clean()
{
    if (pipe_texture)
    {
        SDL_DestroyTexture(pipe_texture);
    
    }

}

bool Pipe::init(SDL_Renderer* renderer)
{
    pipe_texture = IMG_LoadTexture(renderer, "../assets/pipe.png");

    if (!pipe_texture)
    {
        std::cout << "không load được ảnh của cột" << std::endl;
        return false;
    }
    return true;
}

void Pipe::create(float delta, int rightWin)
{
    spawn_timer += delta;

    std::cout << spawn_timer << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(500,800);
    y_random = dist(gen);

    if (spawn_timer >= 2.5f)
    {
        std::cout << spawn_timer << std::endl;
        coor.rect.x = rightWin;
        coor.rect.y = y_random;
        coor.rect.w = 200;
        coor.rect.h = 500;

        pipes.emplace_back(coor);
        spawn_timer = 0;
    }
}

void Pipe::update(float delta)
{
    for (auto &pipe : pipes)
    {
        pipe.rect.x += -velX * delta;
        std::cout << "pipes pos: " << pipe.rect.x << std::endl;
    }
}

void Pipe::render(SDL_Renderer *renderer)
{
    for (auto &pipe : pipes)
    {
        SDL_RenderCopy(renderer, pipe_texture, nullptr,&pipe.rect);
    }

}


