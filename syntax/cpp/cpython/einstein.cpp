#include <iostream>
#include <cctype>
#include <string>

int energy(int mass)
{

    int c = 300;
    mass = mass * c * c;
    return mass;
}

int main()
{
    int mass = 5;
    std::cout << energy(mass) << " this is mass of that matter" << std::endl;
    return 0;
}