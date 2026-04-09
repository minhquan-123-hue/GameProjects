#include <dick.h>
#include <iostream>
#include <SDL2/SDL_image.h>

Dick::Dick() : texture(nullptr),
               isAlive(true),
               respawnTimer(0),
               respawnDelay(1000) // 1 second
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
    if (!isAlive)
        return;

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
    if (!isAlive)
        return;
    SDL_RenderCopy(renderer, texture, nullptr, &dick.rect);
}
void Dick::clean()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

void Dick::die()
{
    isAlive = false;
    respawnTimer = SDL_GetTicks(); // lấy thời gian hiện tại
    std::cout << "respawnTimer: " << respawnTimer << std::endl;
}

void Dick::updateRespawn()
{
    if (!isAlive)
    {
        Uint32 newTime = SDL_GetTicks();
        std::cout << "newTime khong chinh xac: " << newTime << std::endl;
        if (newTime - respawnTimer >= respawnDelay)
        {
            std::cout << "newTime: " << newTime << std::endl;
            // hồi sinh bên trái
            dick.rect.x = 0;
            dick.rect.y = 900;

            isAlive = true;
        }
    }
}