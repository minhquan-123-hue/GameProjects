// #include == import (same with ideals but not with mechanism), iostream == input output stream : library run & at compile time
#include <iostream>

// return_type function_name(type if have)
void greet(void)
{
    // create array of strings by using [] to declare number of words
    char greet[20] = "first time to c";
    // std::cout == standard character output , std::endl = standard endline , << put that into here , they are in compiler ??
    std::cout << "HI,WORLD!" << std::endl
              << greet << std::endl;
}

// entry point run entire code : mandate
int main(void)
{
    // call a function
    greet();
    // tell OS this program run successfully
    return 0;
}
