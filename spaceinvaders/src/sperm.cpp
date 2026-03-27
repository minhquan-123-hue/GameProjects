#include <algorithm>
#include <sperm.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Sperm::Sperm() : texture(nullptr)
{
}

bool Sperm::loadTexture(SDL_Renderer *renderer)
{
    texture = IMG_LoadTexture(renderer, "../assets/sperm.png");

    if (texture == nullptr)
    {
        std::cout << "không mở được ảnh trung tình" << std::endl;
        return false;
    }
    return true;
}

void Sperm::create(int x, int y)
{
    body.rect.w = 64;
    body.rect.h = 64;
    body.rect.x = x + (body.rect.w / 2);
    body.rect.y = y;
    body.speed = 8;

    sperms.emplace_back(body);
}

void Sperm::updateMovement()
{
    for (auto &body : sperms)
    {
        body.rect.y -= body.speed;
    }
}

void Sperm::updateCollision()
{
    auto smartPointer = std::remove_if(
        sperms.begin(),
        sperms.end(),
        [](auto &sperm)
        { return sperm.rect.y < 0; });

    sperms.erase(smartPointer, sperms.end());
}

void Sperm::render(SDL_Renderer *renderer)
{
    for (auto &sperm : sperms)
    {
        SDL_RenderCopy(renderer, texture, nullptr, &sperm.rect);
    }
}

void Sperm::clean()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}