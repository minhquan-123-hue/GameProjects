#include <pussy.h>
#include <iostream>

Pussy::Pussy() : texture(nullptr),
                 hitWall(false),
                 direction(1),
                 dropDistance(10)
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

void Pussy::updateMovement()
{

    // nếu chạm tường -> đổi hướng + đi xuống
    if (hitWall == true)
    {
        direction *= -1; // direction để ngoài biến thành viên của pussy

        for (auto &pussy : pussies)
        {
            pussy.rect.y += dropDistance; // không để drop trong biến thành viên của pussy
        }
        hitWall = false;
    }

    for (auto &pussy : pussies)
    {
        pussy.rect.x += direction * pussy.speed; // di chuyển cả đội quân
    }
}

void Pussy::updateCollision(int leftWall, int rightWall)
{
    hitWall = false; // chatGPT bảo là để cờ ở đây cho đỡ bị giật (reset mỗi frame)

    // kiểm tra xem có con nào va chạm tường không
    for (auto &pussy : pussies)
    {
        if (pussy.rect.x <= leftWall || pussy.rect.x >= rightWall - pussy.rect.w) // va tường trải phải
        // theo điều kiện OR: nghĩa 1 trong 2 đúng thì chạy body
        {
            hitWall = true; // đã va chạm tường
            break;          // không cần kiểm tra toàn 1 bộ sau khi phát hiện 1 em pussy nào đó đã va chạm
        }
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
