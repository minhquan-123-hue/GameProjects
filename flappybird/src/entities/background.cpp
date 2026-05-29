#include <entities/background.h>
#include <iostream>

BackGround::BackGround():
speed(100)
{}

void BackGround::init(Window &w_size)
{
    rect.x = w_size.left;
    rect.y = w_size.top;
    rect.w = w_size.right * 2;
    rect.h = w_size.down;

}

void BackGround::process_logic(float dt)
{
    rect.x += -speed * dt;
    
    int RESET_POINT = -(rect.w / 2);

    if (rect.x <= RESET_POINT)
    {
        rect.x = 0;
    }
}

