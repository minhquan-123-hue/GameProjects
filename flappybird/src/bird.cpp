#include <bird.h>
#include <iostream>

Bird::Bird(): bird_texture(nullptr),
GRAVITY(1500.0f),
velY(0.0f)
{}
Bird::~Bird()
{
    clean();
}

void Bird::clean()
{
    if (bird_texture)
    {
        SDL_DestroyTexture(nullptr);
    }

}

bool Bird::init(SDL_Renderer *renderer)
{
    bird_texture = IMG_LoadTexture(renderer , "../assets/bird.png");

    if (!bird_texture)
    {
        std::cerr << "không mở được ảnh con chim" << std::endl;
        return false;
    }

    rect.x = 500;
    rect.y = 500;
    rect.w = 80;
    rect.h = 80;

    return true;
}

void Bird::input(SDL_Event &event)
{
    if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && event.key.repeat == 0)
    {
        velY = -450;
    }
}
void Bird::update(float dt)
{
    velY = velY + GRAVITY * dt;

    std::cout << "velY: " << velY << std::endl;

    rect.y = rect.y + velY * dt;
}

void Bird::render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, bird_texture, nullptr, &rect);
}