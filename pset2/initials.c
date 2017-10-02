/**
 * initials.c by Chris Bonner
 * This program prints out the initials of any name entered by the user.
 **/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

void Initials(string name, int name_length);

int main(void)
{
    // get the name and length
    string name = GetString();
    int name_length = strlen(name);    

    // print initials
    Initials(name,name_length);
    
    return 0;
}

/**
 * This function prints the initials of the name to the screen.
 **/
void Initials(string name, int name_length)
{
    // iterate over array
    for (int i = 0; i < name_length; i++)
    {
        // capitalise each letter following a space
        if (name[i] != ' ')
        {
            // print letter in uppercase
            printf("%c",toupper(name[i]));
            
            // find next space in text
            do
            {   
                i++;
            }
            while (name[i] != ' ' && i < name_length);
        }
    }
    
    printf("\n");
    
    return;
}