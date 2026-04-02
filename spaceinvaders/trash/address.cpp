#include <iostream>

int main()
{
    struct Vector
    {
        int x;
        int y;
    };

    Vector coordinate;
    Vector *pointer = &coordinate;

    pointer->x = 100;

    std::cout << coordinate.x << std::endl; // in ra 100
}