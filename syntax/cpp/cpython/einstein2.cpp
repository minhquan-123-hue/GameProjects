#include <string>
#include <cctype>
#include <iostream>
#include <limits>

using i64 = long long;
const i64 c = 300;

i64 energy(i64 mass)
{
    return mass * c * c;
}

int main()
{
    std::cout << "Mass: ";
    i64 mass{};
    if (!(std::cin >> mass))
    {
        std::cerr << "Invalid Number\n";
        return 1;
    }

    i64 result = energy(mass);
    std::cout << energy(mass) << std::endl;
    return 0;
}