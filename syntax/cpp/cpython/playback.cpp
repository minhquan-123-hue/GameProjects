// playback.cpp

#include <iostream>
#include <string>
#include <cctype>

int main()
{
    std::string text;
    std::getline(std::cin, text);
    std::cout << text << " before modifying " << std::endl;
    std::cout << text.size() << " number of characters before modifying " << std::endl;
    for (size_t i = 0; i < text.size(); ++i)
    {
        if (text[i] = 'w')
        {
            std::cout << i << " characters had eaten and it position " << std::endl;
            text.replace(0, 1, "...");
            i += 2;
        }
    }
    std::cout << text << std::endl;
    return 0;
}