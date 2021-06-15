/* Determines the type of payment card by number */
/* Usage example: input: 4003600000000014 output:VISA */
/* Build: gcc ../../vendor/cs50.c credit.c -o credit */

#include <stdio.h>
#include "../../vendor/cs50.h"
#include <math.h>

int main(void)
{
    long long number;
    do
    {
        number = get_long_long("Number: ");
    } while (number <= 999999999999 || number >= 10000000000000000);
    int digit;
    int last_summ_digit;
    int first_digit;
    int second_digit;
    int count = 0;
    int summ = 0;
    long long n = number;
    while (n >= 0)
    {
        //get digits from end of card number
        if (n > 10)
        {
            digit = n % 10;
            n = floor(n / 10);
        }
        else
        {
            digit = n;
            n = -1;
        }
        //count summ of digits
        if (count % 2 == 0)
        {
            summ += digit;
        }
        else
        {
            digit *= 2;
            if (digit < 10)
            {
                summ += digit;
            }
            else
            {
                summ = summ + floor(digit / 10) + (digit % 10);
            }
        }
        count++;
        last_summ_digit = summ % 10;
    }

    first_digit = number / (pow(10, (count - 1)));
    second_digit = number / (pow(10, (count - 2))) - first_digit * 10;

    if (last_summ_digit == 0 && count == 15 && first_digit == 3 &&
        (second_digit == 4 || second_digit == 7))
    {
        printf("AMEX\n");
    }
    else if (last_summ_digit == 0 && count == 16 && first_digit == 5 && (second_digit >= 1 && second_digit <= 5))
    {
        printf("MASTERCARD\n");
    }
    else if (last_summ_digit == 0 && (count == 13 || count == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    
}