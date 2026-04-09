#include <dick.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Dick::Dick() : texture(nullptr),
               isAlive(false),
               respawnTimer(0),
               respawnDelay(1000)
{
}

bool Dick::loadTexture(SDL_Renderer *renderer)
{
    texture = IMG_LoadTexture(renderer, "../assets/dick.png");

    if (texture == nullptr)
    {
        std::cout << "không tải được ảnh dick" << std::endl;
        return false;
    }

    return true;
}

void Dick::create()
{
    body.rect.w = 120;
    body.rect.h = 120;
    body.rect.x = 100;
    body.rect.y = 900;
    body.speed = 15;
}

void Dick::updateMovement()
{
    if (!isAlive)
    {
        return;
    }
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_A])
    {
        body.rect.x -= body.speed;
    }
    if (state[SDL_SCANCODE_D])
    {
        body.rect.x += body.speed;
    }
}

void Dick::updateCollision(int leftWall, int rightWall)
{
    if (body.rect.x <= leftWall)
    {
        body.rect.x = leftWall;
    }
    if (body.rect.x >= rightWall - body.rect.w)
    {
        body.rect.x = rightWall - body.rect.w;
    }
}

void Dick::die()
{
    isAlive = false;
    respawnTimer = SDL_GetTicks();
}
void Dick::updateRespawn()
{
    if (!isAlive)
    {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - respawnTimer >= respawnDelay)
        {
            isAlive = true;
            body.rect.x = 100;
            body.rect.y = 900;
        }
    }
}

void Dick::render(SDL_Renderer *renderer)
{
    if (!isAlive)
    {
        return;
    }
    SDL_RenderCopy(renderer, texture, nullptr, &body.rect);
}

void Dick::clean()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}