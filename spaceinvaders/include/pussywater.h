#pragma once // chỉ được include tao 1 lần trong file khác
#include <SDL2/SDL_image.h>
#include <vector>

class PussyWater
{
public:
    PussyWater();
    ~PussyWater();

    bool loadTexture(SDL_Renderer *renderer);

    void create(int x, int y); // tao dan
    void updateMovement();
    void updateCollision(int bottomWall);
    void render(SDL_Renderer *renderer);
    void clean();

    struct Body
    {
        SDL_Rect rect;
        int speed;
    };

    std::vector<Body> waters;

private:
    SDL_Texture *texture;
};
