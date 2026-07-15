#pragma once

#include <SDL2/SDL.h>

class Paddle
{
public:
    Paddle();
    ~Paddle();

    void setTexture(SDL_Texture* texture);
    void setSourceRect(const SDL_Rect& src);

    void setWorldBounds(int left, int right, int top, int bottom);
    void setPosition(float x, float y);
    void setSpeed(float speed);

    void update(float dt);
    void render(SDL_Renderer* renderer);

    float getX() const;
    float getY() const;
    int getWidth() const;
    int getHeight() const;

private:
    SDL_Texture* texture;

    SDL_Rect sourceRect;

    float x;
    float y;
    float speed;

    int leftBound;
    int rightBound;
    int topBound;
    int bottomBound;

    int width;
    int height;
};