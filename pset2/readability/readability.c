/* Assesses the difficulty of reading the text */
/* Build: gcc ../../vendor/cs50.c readability.c -o readability */
/* 
    Usage example: 
        input: Simple text.
        output: Before Grade 1
*/

#include <stdio.h>
#include "../../vendor/cs50.h"
#include <string.h>
#include <math.h>

int main(void)
{
    string s = get_string("Text: ");
    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0, length = strlen(s); i < length; i++)
    {
        int letter_code = (int)s[i];
        if ((letter_code >= 97 && letter_code <= 122) || (letter_code >= 65 && letter_code <= 90))
        {
            letters++;
        }
        else if (letter_code == 32)
        {
            words++;
        }
        else if (letter_code == 33 || letter_code == 46 || letter_code == 63)
        {
            sentences++;
        }
    }
    if (letters > 0)
    {
        words++;
    }

    float L = (letters * 100) / words;
    float S = (sentences * 100) / words;

    int grade = round(0.0588 * L - 0.296 * S - 15.8);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}