#include <stdio.h>
#include <string.h>

int main(void)
{
    // 1.Arrays
    int numbers[5] = {10, 20, 30, 40, 50};

    // 2. Multidimensional array (a small 2x3 grid)
    int grid[2][3] = {
        {1, 2, 3},
        {4, 5, 6}};

    // 3. Conditions
    int x = 25;
    if (x > 20)
    {
        printf("X is greater than 20\n");
    }
    else
    {
        printf("x is 20 or less\n");
    }

    // 4. Strings
    char name[20] = "Quân";
    printf("Hello, %s!\n", name);

    // Print array elements
    printf("Numbers array:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d", numbers[i]);
    }
    printf("\n");

    // Print grid elements
    printf("2D Grid: \n");
    for (int row = 0; row < 2; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            printf("%d", grid[row][col]);
        }
        printf("\n");
    }

    return 0;
}