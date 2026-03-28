#include <sperm.h>
#include <iostream>
#include <algorithm>

Sperm::Sperm() : texture(nullptr)
{
}
Sperm::~Sperm() {}

bool Sperm::loadTexture(SDL_Renderer *renderer)
{
    texture = IMG_LoadTexture(renderer, "../assets/sperm.png");

    if (texture == nullptr)
    {
        std::cout << "không mở được ảnh của trung tình" << std::endl;
        return false;
    }
    return true;
}

void Sperm::create(int x, int y)
{
    sperm.rect.w = 64;
    sperm.rect.h = 64;
    sperm.rect.x = x + (sperm.rect.w / 2);
    sperm.rect.y = y;
    sperm.speed = 8;

    sperms.emplace_back(sperm);
}

void Sperm::updateMovement()
{
    for (auto &sperm : sperms)
    {
        sperm.rect.y -= sperm.speed;
    }
}

void Sperm::updateCollision(int topWall)
{
    auto iterator = std::remove_if(
        sperms.begin(),
        sperms.end(),
        [&topWall](auto &sperm)
        { return sperm.rect.y < topWall; }); // sperm thì được tạo ở phần khai nên dùng &sperm nó sẽ biết vào sperm , và begin() , end() là từ đầu đên cuối của mảng động chứa nhiều sperm

    sperms.erase(iterator, sperms.end());
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