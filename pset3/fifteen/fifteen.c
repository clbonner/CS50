/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 2
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void move_up(int i, int j, int tile);
void move_down(int i, int j, int tile);
void move_left(int i, int j, int tile);
void move_right(int i, int j, int tile);


int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // initialise the number of tiles
    int tile = d * d - 1;
    switch (d)
    {
        // initialise array for odd numbered board
        case 2: 
        case 4: 
        case 6: 
        case 8:
            // iterate over rows and columns
            for (int i = 0; i < d; i++)
            {
                for (int j = 0; j < d; j++, tile--)
                {
                    if (tile == 2)
                    {
                        // swap 2 for 1
                        board[i][j] = 1;
                    }
                    else if (tile == 1)
                    {
                        // swap 1 for 2
                        board[i][j] = 2;
                    }
                    else
                    {
                        // add tile number to array
                        board[i][j] = tile;
                    }
                }
            }
            break;
        
        // initialise array for even numbered board
        case 3:
        case 5:
        case 7:
        case 9:
            // iterate over rows and columns
            for (int i = 0; i < d; i++)
            {
                for (int j = 0; j < d; j++, tile--)
                {
                    // add tile to array
                    board[i][j] = tile;
                }
            }
            break;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // iterate over array rows and columns
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == 0)
            {
                // print an underscore in place of blank space
                printf(" _ ");
            }
            else if (board[i][j] >= 10)
            {
                // print less space around double digit numbers
                printf("%d ", board[i][j]);
            }
            else
            {
                // print more space around single digit numbers
                printf(" %d ", board[i][j]);
            }
        }
        
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // do linear search of array to find tile
    // iterate over array rows and columns
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                // tile in lower right corner
                if (i == d - 1 && j == d - 1)
                {
                    // find blank space
                    if (board[i - 1][j] == 0)
                    {
                        move_up(i, j, tile);
                    }
                    else if (board[i][j - 1] == 0)
                    {
                        move_left(i, j, tile);
                    }
                }
                
                // tile borders right edge
                else if (i != 0 && i != d - 1 && j == d - 1)
                {
                    // find blank space
                    if (board[i + 1][j] == 0)
                    {
                        move_down(i, j, tile);
                    }
                    else if (board[i][j - 1] == 0)
                    {
                        move_left(i, j, tile);
                    }
                    else if (board[i - 1][j] == 0)
                    {
                        move_up(i, j, tile);
                    }
                }
                
                // tile is in top right corner
                else if (i == 0 && j == d - 1)
                {
                    // find blank space
                    if (board[i + 1][j] == 0)
                    {
                        move_down(i, j, tile);
                    }
                    else if (board[i][j - 1] == 0)
                    {
                        move_left(i, j, tile);
                    }
                }
                
                // tile borders top row
                else if (i == 0 && j != 0 && j != d - 1)
                {
                    // find blank space
                    if (board[i + 1][j] == 0)
                    {
                        move_down(i, j, tile);
                    }
                    else if (board[i][j + 1] == 0)
                    {
                        move_right(i, j, tile);
                    }
                    else if (board[i][j - 1] == 0)
                    {
                        move_left(i, j, tile);
                    }
                }
                
                // tile is in top left corner
                else if (i == 0 && j == 0)
                {
                    // find blank space
                    if (board[i][j + 1] == 0)
                    {
                        move_right(i, j, tile);
                    }
                    else if (board[i + 1][j] == 0)
                    {
                        move_down(i, j, tile);
                    }
                }
                
                // tile borders left edge
                else if (i != 0 && i != d - 1 && j == 0)
                {
                    // find blank space
                    if (board[i + 1][j] == 0)
                    {
                        move_down(i, j, tile);
                    }
                    else if (board[i - 1][j] == 0)
                    {
                        move_up(i, j, tile);
                    }
                    else if (board[i][j + 1] == 0)
                    {
                        move_right(i, j, tile);
                    }
                }
                
                // tile is in lower left corner
                else if (i == d - 1 && j == 0)
                {
                    // find blank space
                    if (board[i - 1][j] == 0)
                    {
                        move_up(i, j, tile);
                    }
                    else if (board[i][j + 1] == 0)
                    {
                        move_right(i, j, tile);
                    }
                }
                
                // tile borders bottom edge
                else if (i == d - 1 && j != 0 && j != d - 1)
                {
                    // find blank space
                    if (board[i - 1][j] == 0)
                    {
                        move_up(i, j, tile);
                    }
                    else if (board[i][j + 1] == 0)
                    {
                        move_right(i, j, tile);
                    }
                    else if (board[i][j - 1] == 0)
                    {
                        move_left(i, j, tile);
                    }
                }
                
                // tile does not border any edges
                else
                {
                    // find blank space
                    if (board[i + 1][j] == 0)
                    {
                        move_down(i, j, tile);
                    }
                    else if (board[i - 1][j] == 0)
                    {
                        move_up(i, j, tile);
                    }
                    else if (board[i][j + 1] == 0)
                    {
                        move_right(i, j, tile);
                    }
                    else if (board[i][j - 1] == 0)
                    {
                        move_left(i, j, tile);
                    }
                }
                
                // tile moved
                return true;
            }
        }
    }
    
    // tile not found
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // set count to 0 
    int swap_count = 0;
    
    // iterate over rows and columns in array
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] != 0)
            {
                if (j == d - 2 && i == d - 1 && swap_count == 0)
                {
                    // array is sorted
                    return true;
                }
                else if ( j == d - 1)
                {
                    // compare with tile on next row
                    if (board[i][j] > board[i + 1][0])
                    {
                        swap_count++;
                        return false;
                    }
                }
                // compare with tile next in row
                else if (board[i][j] > board[i][j + 1])
                {
                    swap_count++;
                    return false;
                }
            }
            else
            {
                // array not sorted
                return false;
            }
        }
    }
    
    return false;
}

/**
 * Moves the tile up in to the blank space.
 */
void move_up(int i, int j, int tile)
{
    board[i - 1][j] = tile;
    board[i][j] = 0;
    return;
}

/**
 * Moves the tile down in to the blank space.
 */
void move_down(int i, int j, int tile)
{
    // move tile down
    board[i + 1][j] = tile;
    board[i][j] = 0;
    return;
}

/**
 * Moves the tile left in to the blank space.
 */
void move_left(int i, int j, int tile)
{
    // move tile left
    board[i][j - 1] = tile;
    board[i][j] = 0;
    return;
}

/**
 * Moves the tile right in to the blank space.
 */
void move_right(int i, int j, int tile)
{
    // move tile right
    board[i][j + 1] = tile;
    board[i][j] = 0;
    return;
}
