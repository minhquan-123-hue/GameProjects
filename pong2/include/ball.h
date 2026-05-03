#pragma once
#include <SDL2/SDL.h>
#include <paddle.h>
#include <sound.h>

class Ball
{
public:
    Ball();  // contructor
    ~Ball(); // destructor

    void create();

    void updateMovement(float deltaTime);
    void updateCollision(int topWall, int downWall, Paddle &paddle1, Paddle &paddle2, Sound &sound);
    void resetPos(int direction);

    void render(SDL_Renderer *renderer);

    void clean();

    struct Coor
    {
        SDL_Rect rect;
        float x;
        float y;
    };

    Coor coor;

    struct Vector
    {
        float velX;
        float velY;
    };

    Vector movement;

};