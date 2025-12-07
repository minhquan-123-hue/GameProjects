#include <stdio.h>

void convert(const char *input);

int main(void)
{

    char text[300];

    printf("Input: ");
    fgets(text, sizeof(text), stdin);

    printf("Output: ");
    convert(text);

    return 0;
}

void convert(const char *input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        // Check for ":)"
        if (input[i] == ':' && input[i + 1] == ')')
        {
            printf("happy");
            i++; // skip the ")" so it isn't printed again
        }
        // Check for ":("
        else if (input[i] == ':' && input[i + 1] == '(')
        {
            printf("sad");
            i++; // skip the "("
        }
        else
        {
            putchar(input[i]);
        }
    }
}