#include <SDL2/SDL_image.h>
#include <vector>

class Pussy
{
public:
    Pussy();
    ~Pussy();

    bool loadTexture(SDL_Renderer *renderer);
    void create();

    void updateMovement();
    void updateCollision(int leftWall, int rightWall);

    void render(SDL_Renderer *renderer);
    void clean();

    struct Body
    {
        SDL_Rect rect;
        float speed;
    };

    int direction; // 1 = sang phải , -1 sang trái
    int dropDistance;

    Body pussy;
    std::vector<Body> pussies;
    SDL_Texture *texture;

    // cờ
    bool hitWall;
};