#include <game.h>
#include <iostream>

int main()
{
    Game game;

    int result = game.init();

    if (!result)
    {
        std::cerr << "can't init resource" << std::endl;
        return 1;
    }

    game.run();

    return 0;
}