/** vigenere.c by Chris Bonner
 * This program uses the Vigenere Cipher to encrypt messages entered by the 
 * user.
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

// function prototypes
void PrintCipher(string text, string k);
void PrintUsage();

int main(int argc, string argv[])
{
    // perform checks on command line arguments
    if (argc == 2)
    {
        int key_length = strlen(argv[1]) - 1;
        string k = argv[1];
            
        // check key is alphabetic
        for (int i = 0; i <= key_length; i++)
        {
            if (isalpha(k[i]))
            {
                // do nothing if alphabetic
            }
            else 
            {
                // return usage if not alphabetic
                PrintUsage();
                return 1;
            }
        }
    }
    else 
    {
        // return usage if no argument supplied
        PrintUsage();
        return 1;
    }
    
    // get text to encrypt
    string text = GetString();
    
    PrintCipher(text, argv[1]);
    return 0;
}

/**
 * This function prints out the encrypted text.
 **/
void PrintCipher(string text, string k)
{
    // get string length and minus 1 to account for array index
    int text_length = strlen(text) - 1, k_length = strlen(k) - 1;
    
    // convert key to lower case
    for (int i = 0; i <= k_length; i++)
    {
        k[i] = tolower(k[i]);
    }
    
    // print ciphered characters
    for (int i = 0, k_index = 0; i <= text_length; i++)
    {
        if (isalpha(text[i]))
        {
            if (islower(text[i]))
            {
                // rotate lowercase character using key
                int rot_text = ((text[i] - 97) + (k[k_index] - 97)) % 26 + 97;
                
                // print character
                printf("%c", rot_text);
                
                // reset key index if end reached else increment
                if (k_index == k_length)
                {
                    k_index = 0;
                }
                else
                {
                    k_index++;
                }
            }
            else if (isupper(text[i]))
            {
                // rotate uppercase character using key
                int rot_text = ((text[i] - 65) + (k[k_index] - 97)) % 26 + 65;
                
                // print character
                printf("%c", rot_text);
                
                // reset key index if end reached else increment
                if (k_index == k_length) 
                { 
                    k_index = 0;
                }
                else
                {
                    k_index++;
                }
            }
        }
        else
        {
            // print non-alphabetic character
            printf("%c", text[i]);
        }
    }
    
    printf("\n");
    
    return;
}

/**
 * This function prints the programs usage.
 **/
void PrintUsage()
{
    printf("Usage: vigenere [alphabetic key string]\n");
    return;
}