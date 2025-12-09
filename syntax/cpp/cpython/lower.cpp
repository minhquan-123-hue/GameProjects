// #include : look at this site , read the instructions
// iostream : input output stream
// string : array of characters
// cctype : c character utitlities
#include <iostream>
#include <string>
#include <cctype>

// return_type name_fuction(type var)
// std::string : declare string var
void lower(std::string text)
{
    // function from std:: => std::getline(std::cin , text): take all input then put into text
    std::getline(std::cin, text);

    // for (type &:reference directly name_var : = in var_name)
    for (char &c : text)
    {

        // function from std:: => std::tolower(static_cast<type>(var_name): built-in language contruct )
        c = std::tolower(static_cast<unsigned char>(c));
    };

    // print on the screen , << : put into here , cout : character output , endl = endline
    std::cout << text << std::endl;
}

int main()
{
    // create string text
    std::string text;
    // print on the screen
    std::cout << "lowercase character: ";
    // run the function(parameter)
    lower(text);
    // tell OS program run successfully
    return 0;
}