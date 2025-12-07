
#include <stdio.h>
#include <ctype.h>

int main()
{

    char text[200];

    // read a line of input( up to 199 characters )
    fgets(text, sizeof(text), stdin);

    // Convert each character to lowercase
    for (int i = 0; text[i] != '\0'; i++)
    {
        text[i] = tolower(text[i]);
    }

    // Output result
    printf("%s", text);

    return 0;
}