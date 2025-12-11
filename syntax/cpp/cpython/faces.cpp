// input output stream : to use tool like std::cout , std::cin
#include <iostream>
// string : an array use for declare a string or ::npos
#include <string>
// c character utilities : to use function : std::getline , std:: namescape (to say this is tools built-in)
#include <cctype>

// return_type function_name(type para) {}
std::string emotions(std::string input)
{
    // character output
    std::cout << "Input: ";
    // character input , read input , put into string input
    std::getline(std::cin, input);

    // size_type : for indice , index , sizes
    size_t position = 0;
    // find("text_want_tofind", start_position) => return position of the text if match else return npos
    while ((position = input.find(":)", position)) != std::string::npos)
    {
        // string.replace(position,number_of_character_replaced_forward,"text_replace")
        input.replace(position, 2, "happy");
        // jump over new text inserted
        position += 5;
    }

    position = 0;
    while ((position = input.find(":(", position)) != std::string::npos)
    {
        input.replace(position, 2, "sad");
        position += 3;
    }

    return input;
}

int main()
{
    std::string text;
    std::cout << emotions(text) << std::endl;
    return 0;
}