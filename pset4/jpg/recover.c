/**
 * recover.c - Chris Bonner
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// macro for block size
#define BLOCK 512

// to keep count of recovered files
int filecount = 0;

// function prototypes
bool jpg_found(unsigned char* buffer);
void recover_file(FILE* inputfile, unsigned char* buffer);

int main(int argc, char* argv[])
{
    // buffer to store file blocks and end of file indicator
    unsigned char* buffer = malloc(BLOCK);
    int eof;

    // check if enough memory free
    if (buffer == NULL) 
        return 1;
    
    // open CF card file
    FILE* inputfile = fopen("card.raw","r");
    if (inputfile == NULL) 
        return 1;
    
    // read first block of file
    eof = fread(buffer, BLOCK, 1, inputfile);
    
    // read blocks until end of file
    while (eof != 0)
    {
        if (jpg_found(buffer) == true)
            recover_file(inputfile, buffer);
        else
            eof = fread(buffer, BLOCK, 1, inputfile);
    }
    
    // close input file and free memory
    fclose(inputfile);
    free(buffer);
}

/**
 * This functions determines if the starting bytes of the supplied block 
 * (in buffer) is a JPG file header.
 **/
bool jpg_found(unsigned char* buffer)
{
    // return true if it is a jpg header
    if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) && 
        (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
    {
        return true;
    }
    else
        return false;
}

/**
 * This function recovers blocks of data from the supplied file pointer
 * until another JPG header is found. Sequentionally numbersing the files
 * as it goes.
 **/
void recover_file(FILE* inputfile, unsigned char* buffer)
{
    char filename[20];
    
    // format output file name with correct digits
    sprintf(filename,"%03d.jpg", filecount);
    
    // open output file
    FILE* outputfile = fopen(filename,"w");
    
    // write first block to output file
    fwrite(buffer, BLOCK, 1, outputfile);
    
    // write blocks until a new jpg is found
    while (fread(buffer, BLOCK, 1, inputfile) != 0)
    {
        if (jpg_found(buffer) == true)
        {
            // close output file and increment file count
            fclose(outputfile);
            filecount++;
            return;
        }
        
        // write block to output file
        fwrite(buffer, BLOCK, 1, outputfile);
    }
    
    // close output file if end of file
    fclose(outputfile);
    return;
}