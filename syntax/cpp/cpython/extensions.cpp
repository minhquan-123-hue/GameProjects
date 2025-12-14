#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

int main()
{
    std::cout << "filename: ";
    std::string filename;
    std::getline(std::cin, filename);
    std::cout << "[DEBUG] raw filename: '" << filename << "'\n\n";

    size_t start = filename.find_first_not_of(" \t\n\r");
    std::cout << "[DEBUG] position of start character: '" << start << "'\n";
    filename.erase(0, start);
    std::cout << "[DEBUG]filename whitespace&t&n&enter delete: '" << filename << "'\n\n";

    size_t end = filename.find_last_not_of(" \t\n\r");
    std::cout << "[DEBUG] filename position of end character: '" << end << "'\n";
    filename.erase(end + 1);
    std::cout << "[DEBUG] filename rm whitespace&t&n&r: '" << filename << "'\n\n";

    // lower
    std::transform(filename.begin(), filename.end(), filename.begin(), [](unsigned char character)
                   { return std::tolower(character); });
    std::cout << "[DEBUG] tolower: '" << filename << "'\n\n";

    size_t pos = filename.rfind(".");
    std::cout << "[DEBUG] pos of . : '" << pos << "'\n\n";

    std::string extension = "";
    std::cout << "[DEBUG] raw string extension: '" << extension << "'\n";
    if (pos != std::string::npos)
    {
        extension = filename.substr(pos + 1);
        std::cout << "[DEBUG] extension after add string: " << extension << "'\n\n";
    }

    if (extension == "pdf")
    {
        std::cout << "file pdf\n";
    }
    else
    {
        std::cout << "not pdf\n";
    }

    return 0;
}