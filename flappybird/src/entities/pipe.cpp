#include <entities/pipe.h>
#include <iostream>

Pipe::Pipe():
velX(100.0f),
is_out(false),
x_pos(1000.0f)
{}

void Pipe::init()
{
    rect.x = 1000;
    rect.y = rand() % 500 + 420;
    rect.w = 200;
    rect.h = 500;
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
