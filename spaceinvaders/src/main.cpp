#include <iostream>
#include <game.h>

int main()
{

    SpaceInvaders game;
    bool initResult = game.initSystem();
    if (!initResult)
    {
        std::cout << "không thể nạp code của thư viên SDL2 hoặc hệ thống phần cứng không tương thích" << std::endl;
        return 1;
    }
    game.runProgram();
    return 0;
}