#include "entities/ball.h"

Ball::Ball()
    : texture(nullptr),
      soundMgr(nullptr),
      sourceRect{0, 0, 8, 8},
      x(0.0f),
      y(0.0f),
      vx(0.0f),
      vy(0.0f),
      width(8),
      height(8),
      leftBound(0),
      rightBound(800),
      topBound(0),
      bottomBound(600)
{
}

Ball::~Ball()
{
}

void Ball::setTexture(SDL_Texture* texture)
{
    this->texture = texture;
}

void Ball::setSourceRect(const SDL_Rect& src)
{
    sourceRect = src;

    width = src.w;
    height = src.h;
}

void Ball::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Ball::setVelocity(float vx, float vy)
{
    this->vx = vx;
    this->vy = vy;
}

void Ball::setWorldBounds(int left, int right, int top, int bottom)
{
    leftBound = left;
    rightBound = right;
    topBound = top;
    bottomBound = bottom;
}

void Ball::setSoundManager(SoundManager* soundManager)
{
    soundMgr = soundManager;
}

void Ball::bounceVertical()
{
    vy = -vy;
}

void Ball::update(float dt)
{
    x += vx * dt;
    y += vy * dt;

    if (x <= leftBound)
    {
        x = leftBound;
        vx = -vx;
        if (soundMgr)
            soundMgr->playSound("brick-hit-2");
    }

    if (x + width >= rightBound)
    {
        x = rightBound - width;
        vx = -vx;
        if (soundMgr)
            soundMgr->playSound("brick-hit-2");
    }

    if (y <= topBound)
    {
        y = topBound;
        vy = -vy;
        if (soundMgr)
            soundMgr->playSound("brick-hit-2");
    }

    if (y + height >= bottomBound)
    {
        y = bottomBound - height;
        vy = -vy;
        if (soundMgr)
            soundMgr->playSound("brick-hit-2");
    }
}

void Ball::render(SDL_Renderer* renderer)
{
    if (renderer == nullptr || texture == nullptr)
    {
        return;
    }

    SDL_Rect destination =
    {
        static_cast<int>(x),
        static_cast<int>(y),
        width,
        height
    };

    SDL_RenderCopy(
        renderer,
        texture,
        &sourceRect,
        &destination);
}

float Ball::getX() const
{
    return x;
}

float Ball::getY() const
{
    return y;
}

int Ball::getWidth() const
{
    return width;
}

int Ball::getHeight() const
{
    return height;
}