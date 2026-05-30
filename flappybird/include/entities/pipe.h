#include <SDL2/SDL.h>


class Pipe
{
    public:

    Pipe();

    void init(float y, char orientation);

    void process_logic(float dt);

    void render(SDL_Renderer *renderer , SDL_Texture *pipetexture);

    SDL_Rect rect;

    float x_pos;

    float velX;
    
    bool is_out;

    char orientation;
};