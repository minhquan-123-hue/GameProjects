#include "vector.h"

int main()
{
    Hunter hunter;
    hunter.vec.x = 3;
    hunter.vec.y = 4;

    hunter.square_root(hunter.vec.x, hunter.vec.y);

    return 0;
}