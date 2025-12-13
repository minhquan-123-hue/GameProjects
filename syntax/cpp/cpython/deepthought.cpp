#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::cout << "What is the purporse in life? ";
    std::string text;
    std::getline(std::cin, text);

    while (!text.empty() && std::isspace(text.front()))
        text.erase(text.begin());

    while (!text.empty() && std::isspace(text.back()))
        text.pop_back();

    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char character)
                   { return tolower(character); });

    if (text == "42" || text == "forty two" || text == "forty-two")
    {
        std::cout << "yes" << std::endl;
    }
    else
    {
        std::cout << "no" << std::endl;
    }

    return 0;
}