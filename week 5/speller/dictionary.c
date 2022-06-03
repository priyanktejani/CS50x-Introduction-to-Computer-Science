// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1700;

// Hash table
node *table[N];

unsigned int hash_value;
unsigned int word_count;

// Returns true if the word is in dictionary else false
bool check(const char *word)
{
    // Hash word to obtain a hash value
    hash_value = hash(word);

    // Access list at that index in the hash table
    node *cursor = table[hash_value];

    // Iterate over the list until the end (NULL address)
    while (cursor)
    {
        // Compare two words by taking one word from the list
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        // Move the cursor to next node
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
// Source: http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char words[LENGTH + 1];

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    // Read string from file until EOF
    while (fscanf(file, "%s", words) != EOF)
    {
        // Create a new node
        node *n = malloc(sizeof(node));
        if (!n)
        {
            return false;
        }

        // Copy word into the node
        strcpy(n->word, words);

        // Hash word to obtain a hash value
        hash_value = hash(words);

        // Access list at that index & set pointer to the previous node
        n->next = table[hash_value];

        // Update new node to the beginning of the list
        table[hash_value] = n;

        // Update the word count
        word_count++;
    }

    // Close dictionary file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (0 < word_count)
    {
        return word_count;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterate over the each bucket of hash table
    for (int i = 0; i < N; i++)
    {
        // Set Pointer to the first element of the link list
        node *cursor = table[i];

        // Iterate over the list until the end (NULL address)
        while (cursor)
        {
            // Create a temporary variable equal to cursor
            node *temp = cursor;

            // Move cursor to next node
            cursor = cursor->next;

            // Free current node memory
            free(temp);
        }

        // Check that the cursor of the last bucket of the hash table points to an NULL address
        if (i == N - 1 && !cursor)
        {
            return true;
        }
    }

    return false;
}
