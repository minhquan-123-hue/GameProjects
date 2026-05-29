#include <SDL2/SDL.h>

class Bird
{
    public:
    
    Bird();

    void init();
    void input(SDL_Event &event);
    void process_logic(float dt);

    SDL_Rect rect;

    float velY;

    float GRAVITY;
};
