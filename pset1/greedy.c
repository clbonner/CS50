/**
 * greedy.c by Chris Bonner
 * The user is asked for the amount of change in dollars and the minimum amount
 * of coins that can be used is returned.
 **/

#include <stdio.h>
#include <math.h>
#include <cs50.h>

int MinimumCoins(int change);

int main(void)
{
    double fchange;
    
    // get amount of change
    printf("O hai! ");
    do
    {
        printf("How much change is owed?\n");
        fchange = GetFloat();
    }
    while (fchange < 0.00);
    
    // convert dollars to cents
    fchange = fchange * 100;
    int change = round(fchange);
    
    // display minimum number of coins possible
    printf("%d\n", MinimumCoins(change));
    
    return 0;
}

/**
 * Returns the minimum amount of coins required for the amount of change given.
 **/
int MinimumCoins(int change)
{
    int quarter = 25, dime = 10, nickel = 5, cent = 1, coins = 0;

    // count quarters
    while (change >= quarter)
    {
        coins++;
        change = change - quarter;
    }

    // count dimes
    while (change >= dime)
    {
        coins++;
        change = change - dime;
    }

    // count nickels
    while (change >= nickel)
    {
        coins++;
        change = change - nickel;
    }
 
    // count cents
    while (change >= cent)
    {
        coins++;
        change = change - cent;
    }
    
    return coins;
}