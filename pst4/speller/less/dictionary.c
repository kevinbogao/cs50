// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }

        // Hash word for index
        int index = hash(word);

        // Insert word to begining of bucket
        strcpy(n->word, word);
        n->next = hashtable[index];
        hashtable[index] = n;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Declare counter
    int word_count = 0;

    // Loop through each bucket in the array
    for (int i = 0; i < N; i++)
    {
        for (node *ptr = hashtable[i]; ptr != NULL; ptr = ptr->next)
        {
            word_count++;
        }
    }

    // Return count
    return word_count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Lowercase the word
    char word_lo[LENGTH + 1];
    for (int i = 0, len = strlen(word_lo); i < len; i++)
    {
        word_lo[i] = tolower(word[i]);
    }

    // Hash word for index
    int index = hash(word_lo);

    // Check through the specific linked list
    node *ptr = hashtable[index];
    while (ptr != NULL)
    {
        // Compare two strings
        if (strcmp(word_lo, ptr->word) == 0)
        {
            return true;
            break;
        }
        ptr = ptr->next;
    }

    // Indicate failure
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = hashtable[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }

    // Indicate success
    return true;
}
