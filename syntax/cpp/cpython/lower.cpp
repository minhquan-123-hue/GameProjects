#include <iostream>
#include <string>
#include <cctype>

void lower(std::string text)
{
    std::cout << "Enter UPPER_CASE: " << std::endl;
    std::getline(std::cin, text); // text = characters

    for (char &character : text)
    {
        character = std::tolower(static_cast<unsigned char>(character));
        character = static_cast<unsigned char>(character);
        character = std::tolower(character);
    }

    std::cout << "this is lower_case: " << text << std::endl;
}

int main()
{
    std::string characters;

    lower(characters);

    return 0;
}