#include <dick.h>
#include <iostream>
#include <SDL2/SDL_image.h>

Dick::Dick() : normalTexture(nullptr),
               hitTexture(nullptr),
               isAlive(true),
               respawnTimer(0),
               respawnDelay(1000) // 1 second
{
}
Dick::~Dick()
{
    clean();
}

void Dick::clean()
{
    if (normalTexture)
    {
        SDL_DestroyTexture(normalTexture);
    }

    if (hitTexture)
    {
        SDL_DestroyTexture(hitTexture);
    }
}

bool Dick::loadTexture(SDL_Renderer *renderer)
{
    normalTexture = IMG_LoadTexture(renderer, "../assets/dick.png");
    hitTexture = IMG_LoadTexture(renderer, "../assets/dick_die.png");

    if (!normalTexture || !hitTexture)
    {
        std::cout << "không mở được ảnh buồi ngựa" << std::endl;
        return false;
    }

    state = DickState::NORMAL;
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

    SDL_Texture *currentTexture;

    if (state == DickState::NORMAL)
    {
        currentTexture = normalTexture;
    }
    else if (state == DickState::HIT)
    {
        currentTexture = hitTexture;
    }
    SDL_RenderCopy(renderer, currentTexture, nullptr, &dick.rect);
}

void Dick::die()
{
    isAlive = false;
    respawnTimer = SDL_GetTicks();
    setHit();
}

void Dick::updateRespawn()
{
    if (!isAlive)
    {
        Uint32 newTime = SDL_GetTicks();
        std::cout << "newTime khong chinh xac: " << newTime << std::endl;
        if (newTime - respawnTimer >= respawnDelay)
        {
            setNormal();

            dick.rect.x = 0;
            dick.rect.y = 900;

            isAlive = true;
        }
    }
}

void Dick::setHit()
{
    state = DickState::HIT;
}

void Dick::setNormal()
{
    state = DickState::NORMAL;
}