#include <entities/pipe.h>
#include <iostream>

Pipe::Pipe():
velX(100.0f),
is_out(false),
x_pos(1000.0f),
orientation()
{}

void Pipe::init(float y, char direction)
{
    rect.x = 1000;
    rect.y = y;
    rect.w = 200;
    rect.h = 500;

    orientation = direction;
}

void Pipe::process_logic(float dt)
{
    x_pos += -velX * dt;
 
    if (x_pos <= -float(rect.w))
    {
        is_out = true;
    }

    rect.x = x_pos;
}

void Pipe::render(SDL_Renderer *renderer , SDL_Texture *pipe_texture)
{
    if (orientation == 't')
    {
        SDL_RenderCopyEx(
        renderer,
        pipe_texture,
        nullptr,
        &rect,
        0.0,
        nullptr,
        SDL_FLIP_VERTICAL
        );
    }
    else
    {
        SDL_RenderCopy(renderer, pipe_texture, nullptr,&rect);
    }
    
}