#include <iostream>
#include <string>
#include <cctype>

void great(std::string name)
{

    std::getline(std::cin, name);

    std::cout << "hello " << name << std::endl;
}

int main()
{
    std::string name;
    great(name);
    return 0;
}