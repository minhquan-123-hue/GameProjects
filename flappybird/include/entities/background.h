#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Background
{
    public:
    Background();
    ~Background();

    void clean();

    bool init(SDL_Renderer *renderer);
    void update(float dt);
    void render(SDL_Renderer *renderer);

    bool create_Texture(SDL_Renderer *renderer);


    private:

    SDL_Texture* background_texture;
    
    struct Coor
    {
        SDL_Rect rect;
    };

    Coor coor;

    float speed;
    int RESET_POINT;
};