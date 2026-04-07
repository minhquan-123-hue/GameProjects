#pragma once // các file khác mà include thì chỉ được incluce 1 lần
#include <SDL2/SDL.h>
#include <vector>
#include <pussywater.h>

class Pussy
{
public:
    Pussy();

    bool loadTexture(SDL_Renderer *renderer);
    void create();

    void shootRandom(PussyWater &pussyWater);
    void updateMovement();                             // cập nhật vị trí: xuống - sang
    void updateCollision(int leftWall, int rightWall); // kiểm tra va với tường trái phải

    void render(SDL_Renderer *renderer);
    void clean();

    struct Body
    {
        SDL_Rect rect;
        float speed;
    };

    int direction;    // hướng của cả đội quân
    int dropDistance; // độ rơi theo trục Y

    Body body;
    SDL_Texture *texture;
    std::vector<Body> pussies;

    // cờ
    bool hitWall;
};