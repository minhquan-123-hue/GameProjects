// #include = import (but different mechanism) tho co dung cu(class/module) vs tho lay dung cu(no class/module) , stdio.h = module/classes but it's just a list of tools ,not a giant function you can already use
#include <stdio.h>

// int main() = function & return 0; {} = block , ; = end of line
int main()
{
    // int = so nguyen (type)
    int integer = 10;
    // float = so thap phan khong chia het
    float integer_dot = 10.5f;
    // double = so thap phan chinh xac (chia het co phay)
    double pi = 3.14f;
    // single character use ''
    char sing_nazi = 'N';
    // array of characters use ""
    char nazi[] = "Nazi";

    // format specification %d = i'm about to print decimal , %.4f = i'm about to print float with quantity of decimal i will tell you , %.6lf = i'm about to pring double-precision demicimal number , %c = character (1 nazi_Soldier) , %s = whole army
    printf("int: %d\n", integer);
    printf("float: %.4f\n", integer_dot);
    printf("pi: %.6lf\n", pi);
    printf("single_nazi: %c\n", sing_nazi);
    printf("army_nazi: %s\n", nazi);

    // program run successfully
    return 0;
}