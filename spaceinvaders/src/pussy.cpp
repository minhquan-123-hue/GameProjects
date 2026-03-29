#include <pussy.h>
#include <iostream>
#include <SDL2/SDL_image.h>

Pussy::Pussy() : texture(nullptr),
                 hitWall(false),
                 direction(1),
                 dropDistance(2)
{
}

bool Pussy::loadTexture(SDL_Renderer *renderer)
{
    texture = IMG_LoadTexture(renderer, "../assets/pussy.png");

    if (texture == nullptr)
    {
        std::cout << "không mở được ảnh pussy" << std::endl;
        return false;
    }
    return true;
}

void Pussy::create()
{
    int startX = 100;
    int startY = 100;
    int spaceX = 64 + 16;
    int spaceY = 64 + 16;
    int totalCols = 10;
    int totalRows = 5;

    for (int pussyRow = 0; pussyRow < totalRows; pussyRow++)
    {
        for (int pussyCol = 0; pussyCol < totalCols; pussyCol++)
        {
            body.rect.w = 64;
            body.rect.h = 64;
            body.speed = 2;
            body.rect.x = startX + pussyCol * spaceX;
            body.rect.y = startY + pussyRow * spaceY;

            pussies.emplace_back(body);
        }
    }
}

void Pussy::updateMovement()
{
    if (hitWall == true)
    {
        direction *= -1;

        for (auto &pussy : pussies)
        {
            body.rect.y += dropDistance;
        }
        hitWall = false;
    }

    for (auto &pussy : pussies)
    {
        body.rect.x += body.speed * direction;
    }
}

void Pussy::updateCollision(int leftWall, int rightWall)
{
    for (auto &pussy : pussies)
    {
        if (body.rect.x <= leftWall || body.rect.x >= rightWall)
        {
            hitWall = true;
            break;
        }
    }
}
void Pussy::render(SDL_Renderer *renderer)
{
    for (auto &body : pussies)
    {
        SDL_RenderCopy(renderer, texture, nullptr, &body.rect);
    }
}

void Pussy::clean()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}