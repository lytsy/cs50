// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 127127;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *n = table[index];
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return ((tolower(word[0])) << 3) + tolower(word[1]);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    node *new_node;
    unsigned int index;
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }
    while (fscanf(inptr, "%s", word) != EOF)
    {
        new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node->word, word);
        index = hash(word);
        new_node->next = table[index];
        table[index] = new_node;
    }
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int size = 0;
    node *n;
    for (int i = 0; i < N; i++)
    {
        n = table[i];
        while (n != NULL)
        {
            size++;
            n = n->next;
        }
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *n;
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        n = table[i];
        while (n != NULL)
        {
            tmp = n;
            free(tmp);
            n = n->next;
        }
    }
    return true;
}
