/* The application restores jpg images from a copy of the card */
/* Usage: recover card.raw */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: recover file\n");
        return 1;
    }

    char *infile = argv[1];
    char outfile[8];
    FILE *outptr;
    FILE *inptr;
    BYTE buffer[512];
    int files = 0;
    int is_outfile_exist = 0;

    inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    while (fread(buffer, sizeof(BYTE), 512, inptr))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (is_outfile_exist)
            {
                fclose(outptr);
            }
            sprintf(outfile, "%03i.jpg", files);
            outptr = fopen(outfile, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", outfile);
                return 1;
            }
            is_outfile_exist = 1;
            files++;
        }
        if (is_outfile_exist)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, outptr);
        }
    }
    if (files > 0)
    {
        fclose(outptr);
    }
    fclose(inptr);
    return 0;
}