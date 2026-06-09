#pragma once
#include <entities/pipe.h>
#include <SDL2/SDL.h>

class PipePair
{
    public:

    PipePair();

    void init(float y);

    void process_logic(float dt);

    void render(SDL_Renderer *renderer , SDL_Texture *pipe_texture);

    Pipe top_pipe;
    Pipe bottom_pipe;

    float MIN_GAP;
    float RANGE_GAP;

    int PIPE_HEIGHT;
    

    bool is_passed;
};
