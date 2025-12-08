#include <iostream>

int energy(int mass)
{
    int c = 300000000;
    return mass * c * c;
}

int main()
{
    // why int mass stand alone ?
    int mass;
    // what is std::cin >> ? what is std::cout << ? what is std::endl;

    std::cin >> mass;
    std::cout << energy(mass) << std::endl;
    return 0;
}
