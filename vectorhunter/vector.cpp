#include "vector.h"
#include <iostream>

Hunter::Hunter()
{
}
float Hunter::square_root(int x, int y)
{
    int hypotenus; // cạnh huyền trước khi tính căn bậc hai

    hypotenus = (x * x + y * y);
    std::cout << "hypotenus: " << hypotenus << std::endl;

    return hypotenus;
}
Hunter::~Hunter() {}