// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames and get resize factor
    int factor = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // make sure n is a positive integer less than or equal to 100
    if (factor < 1 || factor > 100)
    {
        fprintf(stderr, "The first argument must be a positive integer less than or equal to 100\n");
        return 2;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // infile's property
    int biWidthIn = bi.biWidth;
    int biHeightIn = bi.biHeight;

    // infile's property
    bi.biWidth *= factor;
    bi.biHeight *= factor;

    // determine infile's padding for scanlines
    int paddingIn = (4 - (biWidthIn * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine infile's padding for scanlines
    int paddingOut = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // outfile's BITMAPINFOHEADER
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + paddingOut) * abs(bi.biHeight);

    // outfile's BITMAPFILEHEADER
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(biHeightIn); i < biHeight; i++)
    {
        // iterate over factor times for horizontal resize
        for (int j = 0; j < factor; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < biWidthIn; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile factor times
                for (int l = 0; l < factor; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // add outfile's padding, if any
            for (int m = 0; m < paddingOut; m++)
            {
                fputc(0x00, outptr);
            }

            // move the corsor back to begining of scanline
            if (j < factor - 1)
            {
                fseek(inptr, -biWidthIn * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }

        // skip over infile's padding, if any
        fseek(inptr, paddingIn, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
