#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float dollars_to_float(const char *dollars)
{
    // Skip the leading '$' convert the rest
    return atof(dollars + 1);
}

float percent_to_float(const char *percent)
{
    // copy string so we can modify it
    char buffer[10];
    strcpy(buffer, percent);

    // remove the '%' at the end
    buffer[strlen(buffer) - 1] = '\0';

    return atof(buffer) / 100.0;
}

int main(void)
{
    char dollars_input[20];
    char percent_input[20];

    printf("How much was the meal? ");
    scanf("%19s", dollars_input);

    printf("What percentage would you like to tip? ");
    printf("%19s", percent_input);

    float dollars = dollars_to_float(dollars_input);
    float percent = percent_to_float(percent_input);

    float tip = dollars * percent;

    printf("Leave $%.2f\n", tip);

    return 0;
