#include <SDL2/SDL.h>

class Paddle
{
public:
    Paddle();
    ~Paddle();

    void create(int x, int y);

    void update(int topWin, int downWin);
    void updateMovement();
    void updateCollision(int topWin, int downWin);

    void render(SDL_Renderer *renderer);

private:
    void clean();

    struct Movement
    {
        float speed;
    };

    Movement movement;

    struct Config
    {
        SDL_Rect rect;
    };

    Config config;
};