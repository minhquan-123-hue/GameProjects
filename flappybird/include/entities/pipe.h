#include <SDL2/SDL.h>

class Pipe
{
    public:

    Pipe();

    void init();

    void process_logic(float dt);

    SDL_Rect rect;

    float x_pos;
    float velX;

    bool is_out;
};