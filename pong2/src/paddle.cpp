#include <paddle.h>
#include <iostream>

Paddle::Paddle() {}
Paddle::~Paddle()
{
    clean();
}

void Paddle::clean()
{
}

void Paddle::create(int x, int y)
{
    config.rect.x = x;
    config.rect.y = y;
    config.rect.w = 20;
    config.rect.h = 100;
    movement.speed = 10;
}

void Paddle::update(int topWin, int downWin)
{
    updateMovement();
    updateCollision(topWin, downWin);
}

void Paddle::updateMovement()
{

    // con trỏ sẽ trả về index => từ index sẽ biết là phím nào ấn
    const Uint8 *keyState = SDL_GetKeyboardState(nullptr);

    if (keyState[SDL_SCANCODE_W])
    {
        config.rect.y -= movement.speed;
    }

    if (keyState[SDL_SCANCODE_S])
    {
        config.rect.y += movement.speed;
    }
}

void Paddle::updateCollision(int topWin, int downWin)
{
    if (config.rect.y <= topWin)
    {
        config.rect.y = topWin;
    }

    if (config.rect.y >= downWin - config.rect.h)
    {
        config.rect.y = downWin - config.rect.h;
    }
}

void Paddle::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &config.rect);
}