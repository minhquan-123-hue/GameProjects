#include <iostream>
#include <Game.h>

int main(int argc, char *argv[])
{

    Game game; // contruct object
    if (!game.init())
    {
        std::cout << "not init" << std::endl;
        return 1;
    }
    game.run();
    return 0;
}