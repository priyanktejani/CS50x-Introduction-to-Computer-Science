#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Function prototype
int word_count(string st);

int main(void)
{
    int letter = 0;
    int word = 0;
    int sentence = 0;

    // Prompt user for text
    string text = get_string("Text: ");

    // Count sentences & letters
    for (int i = 0, j = 0; i < strlen(text); i++, j++)
    {
        // Increment letter if a character is alphabetical
        if (isalpha(text[i]))
        {
            letter++;
        }
        
        // Increment sentence if the text ends with '.', '!', '?'
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence++;
        }
    }

    // Count words
    word = word_count(text);

    // Calculate (US) grade level index using Coleman-Liau formula
    float l = (float) letter / word * 100;
    float s = (float) sentence / word * 100;
    int grade = round(0.0588 * l - 0.296 * s - 15.8);

    // Print reading level
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Returns number of words in text
int word_count(string text)
{
    int word = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] != ' ')
        {
            while (text[i + 1] != ' ' && i < strlen(text))
            {
                i++;
            }
            word++;
        }
    }
    return word;
}
