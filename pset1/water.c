/**
 * water.c by Chris Bonner
 * This program displays how many bottles of water you have used depending
 * on the amount of time you spent in the shower in minutes.
 **/
 
#include <stdio.h>
#include <cs50.h>

int BottlesUsed(int minutes);

int main(void)
{
    int minutes;
    
    // get positive number from user
    do
    {
        printf("minutes:");
        minutes = GetInt();
    } 
    while(minutes < 1);
    
    printf("bottles:%d\n", BottlesUsed(minutes));
    
    return 0;
}

/**
 * This functions returns the number of bottles used.
 **/
int BottlesUsed(int minutes)
{
    // calculate bottles used
    int bottles = (192 * minutes) / 16;

    return bottles;
}