/* Draws a pyramids of a given height */
/* Build: gcc ../../vendor/cs50.c mario.c -o mario */

#include <stdio.h>
#include "../../vendor/cs50.h"

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    int line_length = (height * 2) + 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= line_length; j++)
        {
            if ((j >= (height - i - 1) && j < height) || (j <= (height + 2 + i) && (j >= (height + 2))))
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        if (i != height - 1)
        {
            printf("\n");
        }
    }
}