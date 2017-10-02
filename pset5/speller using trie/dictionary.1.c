/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// global pointer to dictionary
trie *dict;

// global tally of word count
unsigned int word_count = 0;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // set trav pointer to root of trie
    trie* trav = dict;
    
    // temporary variables
    int c, index;
    
    // iterate over length of word
    for (int i = 0; i < strlen(word); i++)
    {
        c = word[i];
        
        // get array index
        if (c == '\'')
            index = 0;
        else
        {    
            // convert letter to lower case if needed
            c = tolower(c);
            index = c - 96;
        }
        
        // check path is not NULL
        if (trav->path[index] != NULL)
            trav = trav->path[index];
        else
            return false;
    }
    
    // is it a word?
    if (trav->is_word == true)
        return true;
    else
        return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // temporary variables
    int c, index;
    
    // open dictionary file and return false if error encountered
    FILE* dictFile = fopen(dictionary, "r");
    if (dictFile == NULL)
        return false;
    
    // malloc dictionary root and start traversing from root
    dict = malloc(sizeof(trie));
    trie* trav = dict;

    // read characters from file
    while ((c = fgetc(dictFile)) != EOF)
    {
        // check for new word (line feed)
        if (c != 10)
        {
            // check for apostrophies or letters
            if (c == '\'')
                index = 0;
            else
                index = c - 96;
            
            // traverse to next node
            if (trav->path[index] == NULL)
            {
                // create new node
                trie* new_node = malloc(sizeof(trie));
                trav->path[index] = new_node;
                trav = new_node;
            }
            else
                trav = trav->path[index];
        }
        // it must be a new word
        else
        {
            // set word to true and go to trie root 
            trav->is_word = true;
            trav = dict;
            
            // increment the word count
            word_count++;
        }
    }
    
    fclose(dictFile);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    free_memory(dict);
    return true;
}

/**
 * Frees memory from trie data structures
 */
void free_memory(trie* trav)
{
    // iterate over array nodes
    for (int i = 0; i < 27; i++)
    {
        // find allocated array nodes
        if (trav->path[i] != NULL)
            free_memory(trav->path[i]);
    }
    
    // free current node
    free(trav);
    return;
}