#include <entities/background.h>
#include <iostream>

BackGround::BackGround():
speed(100)
{}

void BackGround::init(Window &w_size)
{
    rect.x = w_size.left;
    std::cout << rect.x << std::endl;
    rect.y = w_size.top;
    std::cout << rect.y << std::endl;
    rect.w = w_size.right * 2;
    std::cout << rect.w << std::endl;
    rect.h = w_size.down;
    std::cout << rect.h << std::endl;

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

