#include <SDL2/SDL.h>
#include <systems/sdlmanager.h>

class Ground
{
    public:

    Ground();

    void init(Window &w_size);
    void process_logic(float delta);

    SDL_Rect rect;

    float speed;

};