#include <dick.h>
#include <iostream>
#include <SDL2/SDL_image.h>

Dick::Dick() : texture(nullptr)
{
}
Dick::~Dick() {}

bool Dick::loadTexture(SDL_Renderer *renderer)
{
    texture = IMG_LoadTexture(renderer, "../assets/dick.png"); // trả lại SDL_Texture hoặc NULL

    if (texture == nullptr)
    {
        std::cout << "không mở được ảnh buồi ngựa" << std::endl;
        return false;
    }
    return true;
}

void Dick::create()
{
    dick.rect.w = 100;
    dick.rect.h = 100;
    dick.rect.x = 100;
    dick.rect.y = 900;
    dick.speed = 15;
}

void Dick::updateMovement()
{
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_A])
    {
        dick.rect.x -= dick.speed;
    }
    if (state[SDL_SCANCODE_D])
    {
        dick.rect.x += dick.speed;
    }
}

void Dick::updateCollision(int leftWall, int rightWall)
{

    if (dick.rect.x <= leftWall)
    {
        dick.rect.x = leftWall;
    }
    if (dick.rect.x >= rightWall - dick.rect.w)
    {
        dick.rect.x = rightWall - dick.rect.w;
    }
}

void Dick::render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &dick.rect);
}
void Dick::clean()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}