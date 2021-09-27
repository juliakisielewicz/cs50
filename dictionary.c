// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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
const unsigned int N = LENGTH * 100;

// Hash table
node *table[N];

//Number of words in dictionary
int words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    unsigned int index = hash(word);

    node *current = table[index];

    while(current != NULL)
    {
        if(strcasecmp(word, current->word) == 0)
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
        sum += toupper(word[i]);
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    FILE *file;
    file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char word[LENGTH + 1];
    unsigned int index;

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        n->next = NULL;

        index = hash(n->word);

        if(table[index] != NULL)
        {
            n->next = table[index];
        }

        table[index] = n;

        words++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *current = table[i];
        node *tmp = table[i];

        while(current != NULL)
        {
            current = current->next;
            free(tmp);
            tmp = current;
        }

    }

    return true;
}
