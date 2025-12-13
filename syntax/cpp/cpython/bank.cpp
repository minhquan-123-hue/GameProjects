#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

int main()
{

    std::cout << "Greeting: ";
    std::string greeting;
    std::getline(std::cin, greeting);

    std::cout << "[DEBUG] rawstring: '" << greeting << "'\n";
    assert(!greeting.empty());

    while (!greeting.empty() && std::isspace(greeting.front()))
    {
        greeting.erase(greeting.begin());
        std::cout << "[DEBUG] function greeting.erase(): " << greeting << "'\n";
    }
    assert(greeting.size() > 0);

    for (char &character : greeting)
    {
        character = std::tolower(static_cast<unsigned char>(character));
        std::cout << "[DEBUG] character after lower = std::tolower(): " << character << "'\n";
    }

    if (greeting.rfind("hello", 0) == 0)
    {
        std::cout << "[DEBUG] greeting.rfind(): '" << greeting.rfind("hello", 0) << "'\n";
        std::cout << "$0\n";
    }
    else if (greeting.rfind("h", 0) == 0)
    {
        std::cout << "[DEBUG] greeting.rfind(): '" << greeting.rfind("h", 0) << "'\n";
        std::cout << "$20\n";
    }
    else
    {
        std::cout << "$100\n";
    }

    return 0;
}