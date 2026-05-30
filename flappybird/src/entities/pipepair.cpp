#include <entities/pipepair.h>
#include <iostream>
#include <algorithm>

PipePair::PipePair():
PIPE_GAP(250.0f),
PIPE_HEIGHT(500.0f)
{}

void PipePair::init(float y)
{
    top_pipe.init(y,'t');
    bottom_pipe.init(y + PIPE_GAP + PIPE_HEIGHT,'b');
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