/**
 * mario.c by Chris Bonner
 * This program outputs a mario pyramid according to the height inputted
 * by the user.
 **/

#include <stdio.h>
#include <cs50.h>

void BuildTower(int height);

int main(void)
{
    int height;
    
    // get a number between 0 and 23
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while ((height < 0) || (height > 23));

    BuildTower(height);
    
    return 0;
}

/**
 * This function builds a tower, starting with two blocks and increasing
 * by 1 each time until the height of the tower is reached.
 **/
void BuildTower(int height)
{
    // set initial number of blocks and spaces
    int total_blocks = height + 1, spcs = total_blocks - 2, blocks = 2;
    
    // build the tower
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= spcs; j++)
        {
            // print spaces
            printf(" ");
        }
        for (int j = 1; j <= blocks; j++) 
        {
            // print blocks
            printf("#");
        }   
        printf("\n");
        
        // increment blocks and decrement spaces
        spcs = spcs - 1;
        blocks = blocks + 1;
    }

    return;
}