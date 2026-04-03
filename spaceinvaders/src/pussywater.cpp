#include <pussywater.h>
#include <algorithm>
#include <iostream>

PussyWater::PussyWater() : texture(nullptr) {}

PussyWater::~PussyWater()
{
}

bool PussyWater::loadTexture(SDL_Renderer *renderer)
{
    texture = IMG_LoadTexture(renderer, "../assets/pussy_water.png");

    if (!texture)
    {
        std::cout << "khong load duoc pussy_water\n";
        return false;
    }
    return true;
}

void PussyWater::shoot(int x, int y)
{
    Body pussywater;

    pussywater.rect.w = 64;
    pussywater.rect.h = 64;
    pussywater.rect.x = x;
    pussywater.rect.y = y;

    pussywater.speed = 5;
    waters.push_back(pussywater);
}

void PussyWater::update(int bottomWall)
{
    for (auto &pussywater : waters)
    {
        pussywater.rect.y += pussywater.speed;
    }

    // xoa neu ra khoi man hinh
    auto smartIt = std::remove_if(
        waters.begin(),
        waters.end(),
        [bottomWall](const Body &pussywater)
        {
            return pussywater.rect.y > bottomWall;
        });

    waters.erase(smartIt, waters.end());
}

void PussyWater::render(SDL_Renderer *renderer)
{
    for (auto &pussywater : waters)
    {
        SDL_RenderCopy(renderer, texture, nullptr, &pussywater.rect);
    }
}

void PussyWater::clean()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}