#include <iostream>
#include <string>
#include <cctype>

std::string faces(std::string text)
{
    std::cout << "Input";
    std::getline(std::cin, text);

    size_t pos = 0;
    while ((pos = text.find(":)", pos)) != std::string::npos)
    {
        text.replace(pos, 2, "happy");
        std::cout << pos << "in loop 1" << std::endl;
        pos += 5;
        std::cout << pos << "after +5" << std::endl;
    }

    pos = 0;
    while ((pos = text.find(":(", pos)) != std::string::npos)
    {
        std::cout << pos << "in loop 2" << std::endl;
        text.replace(pos, 2, "sad");
        pos += 3;
        std::cout << pos << "after +3" << std::endl;
    }
    return text;
}

int main()
{
    std::string text;
    std::string input = faces(text);
    std::cout << input << std::endl;
    return 0;
}
