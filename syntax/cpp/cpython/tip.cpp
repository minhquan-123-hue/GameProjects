#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>   // stod() , fixed
#include <algorithm> // remove() , erase

double dollar_to_float(const std::string &dollar)
{

    std::string copy_dollar = dollar; // make an copy

    copy_dollar.erase(std::remove(copy_dollar.begin(), copy_dollar.end(), '$'), copy_dollar.end());

    return std::stod(copy_dollar);
}

double percentage_to_float(const std::string &percentage)
{

    std::string copy_percentage = percentage; // make an copy

    copy_percentage.erase(std::remove(copy_percentage.begin(), copy_percentage.end(), '%'), copy_percentage.end());

    return std::stod(copy_percentage);
}

int main()
{
    std::string dollar;
    std::getline(std::cin, dollar);

    std::string percentage;
    std::getline(std::cin, percentage);

    double tip = (dollar_to_float(dollar) / 100) * percentage_to_float(percentage);

    std::cout << "This is the money you tip: $" << std::fixed << std::setprecision(15) << tip << std::endl;
}
