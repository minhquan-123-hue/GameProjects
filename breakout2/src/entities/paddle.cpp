#include "entities/paddle.h"

#include <SDL2/SDL.h>
#include <algorithm>

Paddle::Paddle()
    : texture(nullptr),
      sourceRect{0, 0, 64, 16},
      x(0.0f),
      y(0.0f),
      speed(0.0f),
      leftBound(0),
      rightBound(800),
      topBound(0),
      bottomBound(600),
      width(64),
      height(16)
{
}

Paddle::~Paddle()
{
}

void Paddle::setTexture(SDL_Texture* texture)
{
    this->texture = texture;
}

void Paddle::setSourceRect(const SDL_Rect& src)
{
    sourceRect = src;
    width = src.w;
    height = src.h;
}

void Paddle::setWorldBounds(int left, int right, int top, int bottom)
{
    leftBound = left;
    rightBound = right;
    topBound = top;
    bottomBound = bottom;
}

void Paddle::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Paddle::setSpeed(float speed)
{
    this->speed = speed;
}

void Paddle::update(float dt)
{
    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    if (keys[SDL_SCANCODE_LEFT])
    {
        x -= speed * dt;
    }

    if (keys[SDL_SCANCODE_RIGHT])
    {
        x += speed * dt;
    }

    x = std::clamp(
        x,
        static_cast<float>(leftBound),
        static_cast<float>(rightBound - width));
}

void Paddle::render(SDL_Renderer* renderer)
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

float Paddle::getX() const
{
    return x;
}

float Paddle::getY() const
{
    return y;
}

int Paddle::getWidth() const
{
    return width;
}

int Paddle::getHeight() const
{
    return height;
}