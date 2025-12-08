// #include == ! import (same idea bring function others had written to use ) , <stdio.h> : to work with input(keyboard) , output(screen) , File
#include <stdio.h>

// int main () {} is function & return 0;
// what is void ? what does it do ? how to use it ? does it call "parameter" of function int main ?
int main(void)
{
    // what is {10,20,30,40,50} ? why it is an array but use this {} symbol ? i thought this [] is its symbol ? numbers[5] is create an array ?
    int numbers[5] = {10, 20, 30, 40, 50};

    // why you need to create an int i = 0 , why we need to use ; after int i=0 and i < 0 ? what is i++ ? how to use it (for (parameter))?
    for (int i = 0; i < 5; i++)
    {
        // how to use printf() ? parameter ?
        printf("%d\n", numbers[i]);
    }
    printf("\n");

    return 0;
}