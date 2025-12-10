// playback.cpp

#include <iostream>
#include <string>
#include <cctype>

int main()
{
    std::string text;
    std::getline(std::cin, text);

    for (size_t i = 0; i < text.size(); ++i)
    {
        std::cout << i << std::endl;
        std::cout << text.size() << std::endl;
        if (text[i] = ' ')
        {
            std::cout << text[i] << std::endl;
            text.replace(0, 1, "...");
            std::cout << text.replace(0, 1, "...") << std::endl;
            i += 2;
            std::cout << i << std::endl;
        }
    }
    std::cout << text << std::endl;
    return 0;
}