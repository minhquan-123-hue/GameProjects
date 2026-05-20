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

    bool image_Handler();
    bool connect_Path(SDL_Renderer *renderer);
    void create();


    private:

    SDL_Texture* background_Texture;
    
    struct Coor
    {
        SDL_Rect rect;
    };

    Coor coor;

    struct Movement
    {
        float speed;
    };

    Movement movement;
};