#pragma once

#include <SDL2/SDL.h>

#include <systems/sound_manager.h>

class Ball
{
public:
    Ball();
    ~Ball();

    void setTexture(SDL_Texture* texture);
    void setSourceRect(const SDL_Rect& src);

    void setPosition(float x, float y);
    void setVelocity(float vx, float vy);

    void setWorldBounds(int left, int right, int top, int bottom);
    void setSoundManager(SoundManager* soundManager);
    void bounceVertical();

    void update(float dt);
    void render(SDL_Renderer* renderer);

    float getX() const;
    float getY() const;

    int getWidth() const;
    int getHeight() const;

private:
    SDL_Texture* texture;
    SoundManager* soundMgr;

    SDL_Rect sourceRect;

    float x;
    float y;

    float vx;
    float vy;

    int width;
    int height;

    int leftBound;
    int rightBound;
    int topBound;
    int bottomBound;
};