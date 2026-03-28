#include <SDL2/SDL_image.h>
#include <vector>

class Pussy
{
public:
    Pussy();
    ~Pussy();

    bool loadTexture(SDL_Renderer *renderer);
    void create();

    void render(SDL_Renderer *renderer);
    void clean();

    struct Body
    {
        SDL_Rect rect;
        float speed;
    };

    Body pussy;
    std::vector<Body> pussies;
    SDL_Texture *texture;
};