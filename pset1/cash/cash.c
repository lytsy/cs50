/* App determine the minimum number of coins required to issue change */
/* Build command: gcc ../../vendor/cs50.c cash.c -o cash */

#include <stdio.h>
#include "../../vendor/cs50.h"
#include <math.h>

int main(void)
{
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    } while (dollars < 0);

    int cents = round(dollars * 100);
    int coins = 0;

    while (cents > 0)
    {
        if (cents >= 25)
        {
            cents -= 25;
        }
        else if (cents >= 10)
        {
            cents -= 10;
        }
        else if (cents >= 5)
        {
            cents -= 5;
        }
        else
        {
            cents -= 1;
        }
        coins++;
    }
    printf("%i\n", coins);
}