#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <vector>

class Sperm
{
public:
    Sperm();
    ~Sperm();

    bool loadTexture(SDL_Renderer *renderer);
    void create(int x, int y);

    void updateMovement();
    void updateCollision(int topWall);

    void render(SDL_Renderer *renderer);
    void clean();

    struct Body
    {
        SDL_Rect rect;
        float speed;
    };

    Body sperm;
    std::vector<Body> sperms;
    SDL_Texture *texture;
};