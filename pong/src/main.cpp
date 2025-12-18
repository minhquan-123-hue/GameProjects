#include <iostream>
#include <Game.h>

int main(int argc, char *argv[])
{
    Game game; // create constructor
    if (!game.init())
    {
        return 1;
    }
    game.run();
    return 0;
}