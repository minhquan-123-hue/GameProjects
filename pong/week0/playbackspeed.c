#include <stdio.h>

int main(void)
{

    char text[200];

    // Prompt user
    printf("Input: ");
    fgets(text, sizeof(text), stdin);

    printf("Output: ");

    // Loop through each character
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            printf("...");
        }
        else
        {
            putchar(text[i]);
        }
    }

    return 0;
}