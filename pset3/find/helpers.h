/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

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