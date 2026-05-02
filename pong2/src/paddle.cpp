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
    coor.rect.x = x;
    coor.rect.y = y;
    coor.rect.w = 20;
    coor.rect.h = 100;
    movement.speed = 1500;
}

void Paddle::updateMovement(int player, float deltaTime)
{

    // con trỏ sẽ trả về index => từ index sẽ biết là phím nào ấn
    const Uint8 *keyState = SDL_GetKeyboardState(nullptr);

    if (player == 1)
    {
        if (keyState[SDL_SCANCODE_W])
        {
            coor.rect.y -= movement.speed * deltaTime;
        }

        if (keyState[SDL_SCANCODE_S])
        {
            coor.rect.y += movement.speed * deltaTime;
        }
    }

    if (player == 2)
    {
        if (keyState[SDL_SCANCODE_UP])
        {
            coor.rect.y -= movement.speed * deltaTime;
        }

        if (keyState[SDL_SCANCODE_DOWN])
        {
            coor.rect.y += movement.speed * deltaTime;
        }
    }
}

void Paddle::updateCollision(int topWin, int downWin)
{
    if (coor.rect.y <= topWin)
    {
        coor.rect.y = topWin;
    }

    if (coor.rect.y >= downWin - coor.rect.h)
    {
        coor.rect.y = downWin - coor.rect.h;
    }
}

void Paddle::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &coor.rect);
}