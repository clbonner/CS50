/** caesar.c by Chris Bonner
 * This program uses the Caesar Cipher to encrypt messages entered by the user.
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int PrintCipher(string text, int k);

int main(int argc, string argv[])
{
    // perform checks on command line arguments
    if (argc > 2) return 1;
    if (argc == 1) 
    {
        printf("Usage: caesar [key]\n");
        return 1;
    }
    
    // convert argument to integer
    int k = atoi(argv[1]);
    
    string text = GetString();
    
    PrintCipher(text, k);
    return 0;
}

/**
 * This function prints out the encrypted text.
 **/
int PrintCipher(string text, int k)
{
    // get string length and minus 1 to account for array index
    int text_length = strlen(text) - 1;
    k = k - 1;

    // print rotated alphabet characters
    for (int i = 0; i <= text_length; i++)
    {
        if (isalpha(text[i]))
        {
            if (islower(text[i]))
            {
                int rot_text = text[i];
                for (int j = 0; j <= k; j++)
                {
                    if (rot_text == 122) rot_text = 96;
                    rot_text++;
                }
                printf("%c", rot_text);
            }
            else if (isupper(text[i]))
            {
                int rot_text = text[i];
                for (int j = 0; j <= k; j++)
                {
                    if (rot_text == 90) rot_text = 64;
                    rot_text++;
                }
                printf("%c", rot_text);
            }
        }
        else printf("%c", text[i]);
    }
    
    printf("\n");
    return 0;
}