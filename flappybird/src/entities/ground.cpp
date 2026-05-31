#include <iostream>
#include <entities/ground.h>

Ground::Ground():
speed(150)
{}

void Ground::init(Window &w_size)
{
    rect.x = w_size.left;
    std::cout << rect.x << std::endl;
    rect.y = 900;
    std::cout << rect.y << std::endl;
    rect.w = w_size.right * 2;
    std::cout << rect.w << std::endl;
    rect.h = 100;
    std::cout << rect.h << std::endl;
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