// include
#include <Game.h>

int main()
{
    // call object(alive);
    Game game;
    if (!game.init())
    {
        return 1;
    }
    game.run();
    return 0;
}
