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
    movement.velX = 300;
    movement.velY = 300;
}

void Ball::updateMovement(float deltaTime)
{
    coor.rect.x += movement.velX * deltaTime;
    coor.rect.y += movement.velY * deltaTime;
}

void Ball::updateCollision(int topWall, int downWall, Paddle &paddle1, Paddle &paddle2)
{
    if (coor.rect.y <= topWall && movement.velY < 0)
    {
        coor.rect.y = topWall;
        movement.velY = -movement.velY;
    }
    if (coor.rect.y >= downWall - coor.rect.h && movement.velY > 0)
    {
        coor.rect.y = downWall - coor.rect.h;
        movement.velY = -movement.velY;
    }

    // kiểm tra vợt trái và bóng
    bool overlapLX = coor.rect.x <= paddle1.coor.rect.x + paddle1.coor.rect.w && coor.rect.x + coor.rect.w >= paddle1.coor.rect.x;
    bool overlapLY = coor.rect.y <= paddle1.coor.rect.y + paddle1.coor.rect.h && coor.rect.y + coor.rect.h >= paddle1.coor.rect.y;

    if (overlapLX && overlapLY && movement.velX < 0)
    {
        coor.rect.x = paddle1.coor.rect.x + paddle1.coor.rect.w;
        movement.velX = -movement.velX;

        float ballCenter = coor.rect.y + coor.rect.h * 0.5f;
        float paddle1Center = paddle1.coor.rect.y + paddle1.coor.rect.h * 0.5f;
        float offset = (ballCenter - paddle1Center) / (paddle1.coor.rect.h * 0.5f);
        const float fixedSpeed = 1000.0f;
        movement.velY = fixedSpeed * offset;
    }

    // kiểm tra vợt phải và bóng
    bool overlapRX = coor.rect.x <= paddle2.coor.rect.x + paddle2.coor.rect.w && coor.rect.x + coor.rect.w >= paddle2.coor.rect.x;
    bool overlapRY = coor.rect.y <= paddle2.coor.rect.y + paddle2.coor.rect.h && coor.rect.y + coor.rect.h >= paddle2.coor.rect.y;

    if (overlapRX && overlapRY && movement.velX > 0)
    {
        coor.rect.x = paddle2.coor.rect.x - coor.rect.w;
        movement.velX = -movement.velX;

        float ballCenter = coor.rect.y + coor.rect.h * 0.5f;
        float paddle2Center = paddle2.coor.rect.y + paddle2.coor.rect.h * 0.5f;
        float offset = (ballCenter - paddle2Center) / (paddle2.coor.rect.h * 0.5f);
        const float fixedSpeed = 1000.0f;
        movement.velY = fixedSpeed * offset;
    }
}

void Ball::resetPos(int direction)
{

    coor.rect.x = 500;
    coor.rect.y = 500;
    
    movement.velY = 0.0f;
    movement.velX *= direction;
}

void Ball::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &coor.rect);
}