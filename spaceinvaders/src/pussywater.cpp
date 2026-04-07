#include <pussywater.h>
#include <SDL2/SDL_image.h>
#include <algorithm>

PussyWater::PussyWater() : texture(nullptr) {}
PussyWater::~PussyWater() {}

bool PussyWater::loadTexture(SDL_Renderer *renderer)
{

    texture = IMG_LoadTexture(renderer, "../assets/pussy_water.png");

    if (texture == nullptr)
    {
        return false;
    }
    return true;
}

void PussyWater::create(int x, int y)
{
    pussyWater.rect.w = 100;
    pussyWater.rect.h = 100;
    pussyWater.rect.x = x;
    pussyWater.rect.y = y;
    pussyWater.speed = 8;

    watersSystem.push_back(pussyWater);
}

void PussyWater::updateMovement()
{
    for (auto It = watersSystem.begin(); It != watersSystem.end(); ++It)
    {
        auto &pussyWater = It;
        pussyWater->rect.y += pussyWater->speed;
    }
}

void PussyWater::updateCollision(int bottomWall)
{
    auto It = std::remove_if(
        watersSystem.begin(),
        watersSystem.end(),
        [bottomWall](const Body &pussyWater)
        {
            return pussyWater.rect.y > bottomWall;
        });

    watersSystem.erase(It, watersSystem.end());
}

void PussyWater::render(SDL_Renderer *renderer)
{
    for (auto It = watersSystem.begin(); It != watersSystem.end();)
    {
        auto &pussyWater = It;
        SDL_RenderCopy(renderer, texture, nullptr, &pussyWater->rect);
    }
}

void PussyWater::clean()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}