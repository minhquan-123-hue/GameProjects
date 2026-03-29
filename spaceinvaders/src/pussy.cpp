#include <pussy.h>
#include <iostream>

Pussy::Pussy() : texture(nullptr),
                 hitWall(false),
                 direction(1),
                 dropDistance(2)
{
}

Pussy::~Pussy() {}

bool Pussy::loadTexture(SDL_Renderer *renderer)
{
    texture = IMG_LoadTexture(renderer, "../assets/pussy.png");

    if (texture == nullptr)
    {
        std::cout << "không mở được ảnh cái lồn" << std::endl;
        return false;
    }
    return true;
}

void Pussy::create()
{
    int totalCols = 10;
    int totalRows = 5;
    int spaceX = 64 + 16;
    int spaceY = 64 + 16;
    int startX = 100; // tạo khoảng cách ban đầu so với tường
    int startY = 100; // cũng giống trên

    for (int pussyRow = 0; pussyRow < totalRows; pussyRow++)
    {
        for (int pussyCol = 0; pussyCol < totalCols; pussyCol++)
        {
            pussy.rect.w = 64;
            pussy.rect.h = 64;
            pussy.speed = 2;

            pussy.rect.x = startX + pussyCol * spaceX;
            pussy.rect.y = startY + pussyRow * spaceY;

            pussies.emplace_back(pussy);
        }
    }
}

void Pussy::updateCollision(int leftWall, int rightWall)
{
    // kiểm tra xem có con nào va chạm tường không
    for (auto &pussy : pussies)
    {
        if (pussy.rect.x <= leftWall || pussy.rect.x >= rightWall - pussy.rect.w)
        {
            hitWall = true;
            break;
        }
    }
}
void Pussy::updateMovement()
{

    // nếu chạm tường -> đổi hướng + đi xuống
    if (hitWall == true)
    {
        direction *= -1;

        for (auto &pussy : pussies)
        {
            pussy.rect.y += dropDistance;
        }
        hitWall = false;
    }

    for (auto &pussy : pussies)
    {
        pussy.rect.x += direction * pussy.speed;
    }
}

void Pussy::render(SDL_Renderer *renderer)
{
    for (auto &pussy : pussies)
    {
        SDL_RenderCopy(renderer, texture, nullptr, &pussy.rect);
    }
}

void Pussy::clean()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}
