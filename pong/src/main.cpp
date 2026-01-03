// include
#include <Pong.h>

int main()
{
    // call object(alive);
    Pong pong;
    if (!pong.init())
    {
        return 1;
    }
    pong.run();
    return 0;
}
