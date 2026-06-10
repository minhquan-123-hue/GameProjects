#include <iostream>
#include <entities/ground.h>

Ground::Ground():
speed(150)
{}

void Ground::init(Window &w_size)
{
    rect.x = w_size.left;
    rect.y = 900;
    rect.w = w_size.right * 2;
    rect.h = 100;
}

void Ground::process_logic(float delta)
{
    rect.x += -speed * delta;

    int RESET_POINT = -(rect.w / 2);

    if (rect.x <= RESET_POINT)
    {
        rect.x = 0;
    }
}

void Ground::render(SDL_Renderer *renderer , SDL_Texture *ground_texture)
{
    SDL_RenderCopy(renderer, ground_texture, nullptr, &rect);
}