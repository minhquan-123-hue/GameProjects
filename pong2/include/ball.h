#include <SDL2/SDL.h>

class Ball
{
public:
    Ball();  // contructor
    ~Ball(); // destructor

    void create();

    void updateMovement(float deltaTime);
    void updateCollision(int topWall, int downWall);

    void render(SDL_Renderer *renderer);

    void clean();

private:
    struct Coor
    {
        SDL_Rect rect;
        float x;
        float y;
    };

    Coor coor;

    struct Movement
    {
        float velX;
        float velY;
        float speed;
    };

    Movement movement;
};