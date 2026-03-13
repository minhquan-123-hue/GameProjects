#include <iostream>
#include <game.h>

int main()
{

    SpaceInvaders game;
    game.init();
    if (!game.init())
    {
        std::cout << "không thể nạp code của thư viên SDL2 hoặc hệ thống phần cứng không tương thích" << std::endl;
        return 1;
    }
    game.run();
    return 0;
}