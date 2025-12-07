// #include == import (but mechanism is not the same)  , stdio.h = standard input output headers ( list of tools you can borrow ( copy & paste others code )) when you need to work with : type signal , write on screen or file I/O
#include <stdio.h>

// int main () {} is function & entry ponit force to use , will return number = 0 to inform the code is compliled.
int main()
{
    /*in python use type hint(optional) but in C use need declare type before create it*/
    // integer = so nguyen, float = so thap phan co phan so , double so thap phan chinh xac , char == string ?? is one soldier  , if you want a string create arrays of  nazi soldiers
    int x = 5;
    float y = 0.1f;
    double pi = 3.14f;
    char name[] = "quan";

    /* in C , printf you have to sepcify their format right , %d for decimal integer , %.2f for 2 number after . f stand for float , %.2lf  for double mean precise-double number : so thap phan chinh xac , and the last %c for char */
    printf("int: %d\n", x);
    printf("float: %.2f\n", y);
    printf("double: %.2lf\n", pi);
    printf("name: %s\n", name);

    return 0;
}