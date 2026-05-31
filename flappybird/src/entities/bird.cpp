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

void Bird::render(SDL_Renderer *renderer , SDL_Texture *bird_texture)
{
    SDL_RenderCopy(renderer, bird_texture, nullptr, &rect);
}

bool Bird::collide(Pipe &pipe)
{
    bool overlapX = rect.x - 10 <= pipe.rect.x + pipe.rect.w && rect.x + rect.w - 10 >= pipe.rect.x;
    bool overlapY = rect.y - 10 <= pipe.rect.y + pipe.rect.h && rect.y + rect.h - 10 >= pipe.rect.y;

    if (overlapX && overlapY)
    {
        std::cout << "đã va chạm" << std::endl;
        return true;
    }

    return false;
}