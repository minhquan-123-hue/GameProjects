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

void PussyWater::create(int x, int y)
{
    Body pussywater;

    pussywater.rect.w = 64;
    pussywater.rect.h = 64;
    pussywater.rect.x = x;
    pussywater.rect.y = y; // bước này là khi pussy trao cho nó x y của object trong mảng động thật sự

    pussywater.speed = 5;
    waters.push_back(pussywater);
}

void PussyWater::updateMovement()
{
    for (auto pusWaterIt = waters.begin(); pusWaterIt != waters.end(); ++pusWaterIt)
    {
        auto &pussywater = pusWaterIt;
        pussywater->rect.y += pussywater->speed;
    }
}
void PussyWater::updateCollision(int bottomWall)
{

    // xoa neu ra khoi man hinh
    auto smartIt = std::remove_if(
        waters.begin(),
        waters.end(),
        [bottomWall](const Body &pussywater)
        {
            return pussywater.rect.y > bottomWall;
        });

    waters.erase(smartIt, waters.end()); // vị trí con trỏ thông minh trước phần tử khớp điều kiện > bottomWall bên phải rồi xóa từ đó đên hết
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