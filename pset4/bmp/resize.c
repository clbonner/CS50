/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a bitmap by a given number of times (n).
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember arument/filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // check scale factor is within bounds
    if (n < 1 || n > 100)
    {
        printf("Scale factor must be between 0 and 100.\n");
        return 5;
    }
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_out;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fseek(inptr, 0, SEEK_SET);
    fread(&bf_out, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_out;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    fseek(inptr, sizeof(BITMAPFILEHEADER), SEEK_SET);
    fread(&bi_out, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // increase height and width in BITMAPINFOHEADER
    bi_out.biWidth = bi.biWidth * n;
    bi_out.biHeight = -(abs(bi.biHeight) * n);
    
    // determine padding for scanlines
    int padding_in =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_out =  (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // increase file size in BITMAPFILEHEADER
    bf_out.bfSize = ((bi_out.biWidth * abs(bi_out.biHeight)) * 3)
                    + (padding_out * abs(bi_out.biHeight)) + 54;
                    
    // increase size of biSizeImage
    bi_out.biSizeImage = bf_out.bfSize - 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    // array for storing scanlines
    RGBTRIPLE scanline[bi.biWidth];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // copy triple to scanline
            scanline[j] = triple;
            
            // write RGB triple to outfile n number of times
            for (int k = 0; k < n; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        
        // add padding to scanline
        for (int l = 0; l < padding_out; l++)
        {
            fputc(0x00, outptr);
        }
        
        // write vertical scanline
        for (int j = 0; j < n - 1; j++)
        {
            // arrary incrementor
            int counter = 0;
            
            // write scanline from array n times
            for (int k = 0; k < bi.biWidth; k++, counter++)
            {
                for (int l = 0; l < n; l++)
                {
                    fwrite(&scanline[counter], sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // add padding
            for (int l = 0; l < padding_out; l++)
            {
                fputc(0x00, outptr);
            }
        }
        
        // skip over padding, if any
        fseek(inptr, padding_in, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}