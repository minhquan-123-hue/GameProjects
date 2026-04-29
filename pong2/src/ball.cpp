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
    coor.rect.x += (movement.speed * movement.velX) * deltaTime;
    coor.rect.y += (movement.speed * movement.velY) * deltaTime;
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
        movement.velX *= -1;

        // tính tâm của bóng
        float ballCenter = coor.rect.x + (coor.rect.w / 2);

        // tính tâm của vợt
        float paddle1Center = paddle1.coor.rect.x + (paddle1.coor.rect.w / 2);
        float realoffset = ballCenter - paddle1Center;
        float maxoffset = (coor.rect.w / 2 + paddle1.coor.rect.w / 2);

        float normalizeOffset = realoffset / maxoffset;
        if (normalizeOffset > 1.0f)
            normalizeOffset = 1.0f;
        if (normalizeOffset < -1.0f)
            normalizeOffset = -1.0f;

        // tốc độ cố định
        const float fixedSpeed = 800.0f;
        movement.speed = fixedSpeed;
        movement.velY = normalizeOffset;
    }

    // kiểm tra vợt phải và bóng
    bool overlapRX = coor.rect.x <= paddle2.coor.rect.x + paddle2.coor.rect.w && coor.rect.x + coor.rect.w >= paddle2.coor.rect.x;
    bool overlapRY = coor.rect.y <= paddle2.coor.rect.y + paddle2.coor.rect.h && coor.rect.y + coor.rect.h >= paddle2.coor.rect.y;

    if (overlapRX && overlapRY && movement.velX > 0)
    {
        coor.rect.x = paddle2.coor.rect.x - coor.rect.w;
        movement.velX *= -1;

        // tính tâm của bóng
        float ballCenter = coor.rect.x + (coor.rect.w / 2); // = 15

        // tính tâm của vợt
        float paddle2Center = paddle2.coor.rect.x + (paddle2.coor.rect.w / 2); // = 50
        float realoffset = ballCenter - paddle2Center;
        float maxoffset = (coor.rect.w / 2) + (paddle2.coor.rect.w / 2);

        float normalizeOffset = realoffset / maxoffset;
        if (normalizeOffset > 1.0f)
            normalizeOffset = 1.0f;
        if (normalizeOffset < -1.0f)
            normalizeOffset = -1.0f;

        // tốc độ cố định
        const float fixedSpeed = 800.0f;
        movement.speed = fixedSpeed;
        movement.velY = normalizeOffset;
    }
}

void Ball::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &coor.rect);
}