#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt user for height until it's an integer and between 1 to 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);


    for (int i = height; i > 0; i--)
    {
        // Print spaces
        for (int spaces = 0; spaces < i - 1; spaces++)
        {
            printf(" ");
        }

        // Print hashes
        for (int hashes = i; hashes <= height; hashes++)
        {
            printf("#");
        }

        // print two space
        printf("  ");

        // Print hashes
        for (int hashes = i; hashes <= height; hashes++)
        {
            printf("#");
        }

        // Print new line
        printf("\n");
    }
}
