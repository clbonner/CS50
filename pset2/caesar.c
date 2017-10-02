/** caesar.c by Chris Bonner
 * This program uses the Caesar Cipher to encrypt messages entered by the user.
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

void PrintCipher(string text, int k);

int main(int argc, string argv[])
{
    // perform checks on command line arguments
    if (argc > 2)
    {
        return 1;
    }
    if (argc == 1) 
    {
        printf("Usage: caesar [key]\n");
        return 1;
    }
    
    // convert argument to integer
    int k = atoi(argv[1]);
    
    // get text to cipher
    string text = GetString();
    
    PrintCipher(text, k);
    
    return 0;
}

/**
 * This function prints out the encrypted text.
 **/
void PrintCipher(string text, int k)
{
    // get string length and minus 1 to account for array index
    int text_length = strlen(text) - 1;

    // print rotated alphabet characters
    for (int i = 0; i <= text_length; i++)
    {
        if (isalpha(text[i]))
        {
            if (islower(text[i]))
            {
                // rotate lowercase letter
                int rot_text = ((text[i] - 97) + k) % 26 + 97;
                
                // print rotated letter
                printf("%c", rot_text);
            }
            else if (isupper(text[i]))
            {
                // rotate uppercase letter
                int rot_text = ((text[i] - 65) + k) % 26 + 65;
                
                // print rotated letter
                printf("%c", rot_text);
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