#include <ball.h>
#include <iostream>

Ball::Ball() {}
Ball::~Ball()
{
    clean();
}
void Ball::clean()
{
}

void Ball::create()
{
    coor.rect.x = 500;
    coor.rect.y = 500;
    coor.rect.w = 30;
    coor.rect.h = 30;
    movement.speed = 200;
    movement.velX = 1;
    movement.velY = 1;
}

void Ball::updateMovement(float deltaTime)
{
    coor.rect.x += movement.speed * movement.velX * deltaTime;
    coor.rect.y += movement.speed * movement.velY * deltaTime;
}

void Ball::updateCollision(int topWall, int downWall)
{
    if (coor.rect.y < topWall && movement.speed < 0)
    {
        coor.rect.y = topWall;
        movement.velY = -movement.velY;
    }
    if (coor.rect.y > downWall - coor.rect.h && movement.speed > 0)
    {
        coor.rect.y = downWall - coor.rect.h;
        movement.velY = -movement.velY;
    }
}

void Ball::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &coor.rect);
}