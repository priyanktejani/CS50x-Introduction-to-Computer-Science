#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function prototype
bool usage(int argc, string arg);

int main(int argc, string argv[])
{
    // Ensure proper usage
    if (!usage(argc, argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert string to int
    int key = atoi(argv[1]);

    // Prompts user for a Plaintext
    string text = get_string("plaintext: ");

    // Iterate over the length of the string
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            // Shift plaintext character by key, Preserving case
            if (isupper(text[i]))
            {
                text[i] = ((text[i] - 'A') + key) % 26 + 'A';
            }
            else
            {
                text[i] = ((text[i] - 'a') + key) % 26 + 'a';
            }
        }
    }

    // Print Enciphered text
    printf("ciphertext: %s\n", text);
}

// Function for check proper usage
bool usage(int argc, string arg)
{
    // Ensure only two argument
    if (argc != 2)
    {
        return false;
    }

    // Return true if the string is numeric else false
    for (int i = 0; i < strlen(arg); i++)
    {
        if (!isdigit(arg[i]))
        {
            return false;
        }
    }
    return true;
}
