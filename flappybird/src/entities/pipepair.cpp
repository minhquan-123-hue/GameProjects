#include <entities/pipepair.h>
#include <iostream>
#include <algorithm>



PipePair::PipePair():
PIPE_HEIGHT(700.0f),
is_passed(false),
MIN_GAP(170.0f),
RANGE_GAP(100.0f)
{}

void PipePair::init(float y)
{
    float PIPE_GAP = rand() % (int)(RANGE_GAP) + (int)(MIN_GAP);
    std::cout << "pipe gap: " << PIPE_GAP << std::endl;

    top_pipe.init(y,'t');
    bottom_pipe.init(y + PIPE_HEIGHT + PIPE_GAP,'b');
}

void PipePair::process_logic(float dt)
{
    top_pipe.process_logic(dt);
    bottom_pipe.process_logic(dt);
}

void PipePair::render(SDL_Renderer *renderer, SDL_Texture *pipe_texture)
{
    top_pipe.render(renderer,pipe_texture);
    bottom_pipe.render(renderer,pipe_texture);
}   