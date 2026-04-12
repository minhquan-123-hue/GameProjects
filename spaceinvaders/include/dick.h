#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Dick
{
public:
    Dick();
    ~Dick();

    bool loadTexture(SDL_Renderer *renderer);
    void create();

    void updateMovement();
    void updateCollision(int leftWall, int rightWall);
    void updateRespawn();
    void render(SDL_Renderer *renderer);
    void clean();

    // hàm đặc biệt
    void die();

    struct Body
    {
        SDL_Rect rect;
        float speed;
    };

    Body body;

    // cờ mới:
    bool isAlive;
    Uint32 respawnTimer; // biến lưu thời gian chết tại thời điểm frame nhất định
    Uint32 respawnDelay; // thời gian hồi sinh phải sau 1 giây

private:
    SDL_Texture *texture;
};