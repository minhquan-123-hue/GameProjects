#include <SDL2/SDL.h>
#include <systems/sdlmanager.h>

class BackGround
{
    public:

    BackGround();

    void init(Window &win_z);
    void process_logic(float dt);
    
    SDL_Rect rect;

    float speed;
};