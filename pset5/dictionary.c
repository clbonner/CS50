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

// create hash table
node* dict[HASHSIZE];

// tally of word count
unsigned int word_count = 0;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // temp variables
    node* trav;
    char wordl[LENGTH];
    unsigned int key;
    
    // convert word to lower case
    for (int i = 0; word[i] != '\0'; i++)
        wordl[i] = tolower(word[i]);
    wordl[strlen(word)] = '\0';
    
    // get hash key for word
    key = hash(wordl);
    
    // check if hash key is empty
    if (dict[key] == NULL)
        return false;
        
    trav = dict[key];
    
    // traverse and check all nodes in chain
    while (trav->next != NULL)
    {
        if (strcmp(trav->word, wordl) == 0)
            return true;
        else
            trav = trav->next;
    }
    
    // check last node in chain
    if (strcmp(trav->word, wordl) == 0)
        return true;
    else
        return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // temp variables
    char word[LENGTH];
    unsigned int key, c, index;
   
    // open dictionary file and check for error
    FILE* dictFile = fopen(dictionary, "r");
    if (dictFile == NULL)
        return false;
    
    // set initial array index
    index = 0;
    
    // read characters from file
    while ((c = fgetc(dictFile)) != EOF)
    {
        // check for new word (line feed)
        if (c == 10)
        {
            // terminate string, increment word count
            word[index] = '\0';
            word_count++;
            
            // get hash key
            key = hash(word);
            
            // check if key is empty
            if (dict[key] == NULL)
            {
                // insert new node
                dict[key] = malloc(sizeof(node));
                strcpy(dict[key]->word, word);
                dict[key]->next = NULL;
            }
            else
            {
                // insert another node
                node* new_node = malloc(sizeof(node));
                strcpy(new_node->word, word);
                new_node->next = dict[key];
                dict[key] = new_node;
            }
            
            index = 0;
        }
        
        // append char to word
        else
        {
            word[index] = c;
            index++;
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
    node* chain;
    node* trav;
    
    // iterate over array nodes
    for (int i = 0; i < HASHSIZE; i++)
    {
        // traverse and free all nodes in chain if not empty
        if (dict[i] != NULL)
        {  
            trav = dict[i];
            
            while (trav->next != NULL)
            {
                chain = trav->next;
                free(trav);
                trav = chain;
            }
            
            free(trav);
        }
    }
    
    // all nodes free'd
    return true;
}

/**
 * Hashes a string and returns a non negative integer.
 * 
 * Based on the hash function in the book 'The C Programming Language'
 * Second Edition, by Brian W. Kernighan & Dennis M. Ritchie.
 */
unsigned int hash(const char* word)
{
    unsigned int hashval;
    
    // multiply the hashval by 31 and add each ascii value in turn
    for (hashval = 0; *word != '\0'; word++)
        hashval = *word + 31 * hashval;
    
    // return value modulus the hash table size
    return hashval % HASHSIZE;
}