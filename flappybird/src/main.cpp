#include <game.h>

int main(void)
{
    Game game;
    
    bool initResult = game.init();
    if (!initResult)
    {
        return 1; 
    }
    game.run();
    return 0;
}