#include <iostream>
#include <entities/bird.h>

Bird::Bird():
GRAVITY(1000.0f),
velY(0.0f)
{}

void Bird::init()
{
    rect.x = 500;
    rect.y = 500;
    rect.w = 80;
    rect.h = 80;

}

void Bird::input(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
        {
            velY = -350.0f;
        }
    }
}
void Bird::process_logic(float dt)
{
    velY +=  GRAVITY * dt; // acceleration accumlate overtime

    rect.y += velY * dt;
}

