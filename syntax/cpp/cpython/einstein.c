#include <stdio.h>

int energy(int mass)
{
    int c = 300000000;
    return mass * c * c;
}

int main(void)
{
    int mass;
    scanf("%d", &mass);
    printf("%d\n", energy(mass));

    return 0;
}