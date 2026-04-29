#pragma once
#include <SDL2/SDL.h>

class Paddle
{
public:
    Paddle();
    ~Paddle();

    void create(int x, int y);

    void updateMovement(int player, float deltaTime);
    void updateCollision(int topWin, int downWin);

    void render(SDL_Renderer *renderer);

    void clean();

    struct Movement
    {
        float speed;
    };

    Movement movement;

    struct Coor
    {
        SDL_Rect rect;
    };

    Coor coor;
};