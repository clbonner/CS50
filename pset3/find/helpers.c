/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

// function prototypes

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);

/**
 * Performs a binary search on values[] looking for value. variables 
 * upper and lower define the portion of the array to search, n defines
 * the array size.
 */
bool b_search(int value, int values[], int lower, int upper, int n);

/**
 * Finds the mid point of an array from an upper and lower index 
 * array value.
 */
int mid_array(int lower, int upper);

// function definitions

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // return false if n is not positive
    if (n < 1)
    {
        return false;
    }
    
    // search the array
    if (b_search(value, values, n - n, n - 1, n))
    {
        // value found
        return true;
    }
    else
    {
        // value not found
        return false;
    }
}

/**
 * Performs a binary search on values[] looking for value. variables 
 * upper and lower define the portion of the array to search, n defines
 * the array size.
 */
bool b_search(int value, int values[], int lower, int upper, int n)
{
    // search if lower/upper are in array limits
    if (lower >= 0 && lower <= n - 1 
        && upper >= 0 && upper <= n - 1 
        && lower <= upper)
    {
        // get middle array index
        int middle = mid_array(lower, upper);
        
        // if not the middle value keep looking
        if (values[middle] == value)
        {
            // value found
            return true;
        }
        else if (values[middle] > value)
        {
            // search left half
            if (b_search(value, values, lower, middle - 1, n))
            {
                // value found
                return true;
            }
        }
        else if (values[middle] < value)
        {
            // search right half
            if (b_search(value, values, middle + 1, upper, n))
            {
                // value found
                return true;
            }
        }
    }

    // value not found
    return false;
}

/**
 * Finds the mid point of an array from an upper and lower index 
 * array value.
 */
int mid_array(int lower, int upper)
{
    int count = 0;
    
    // iterate array to get size
    for (int i = lower; i <= upper; i++)
    {
        count++;
    }
    
    // half arrray size to find middle
    int middle = count / 2;
    return lower + middle;
}

/**
 * Sorts array of n values using a bubble sort algorithm.
 */
void sort(int values[], int n)
{
    int swap_count;

    // sort values until the count is 0
    do
    {
        // set count to 0 on each loop iteration
        swap_count = 0;
        
        // iterate over all values and swap if necessary
        for (int i = 0; i < n - 1; i++)
        {
            if (values[i] > values[i + 1])
            {
                // use temporary varialble to swap values
                int swap_value = values[i];
                values[i] = values[i + 1];
                values[i + 1] = swap_value;
                
                // increase count to indicate sorting has occured
                swap_count++;
            }
        }
    }
    while (swap_count != 0);

    return;
}