/* Encrypts the text with a key */
/* 
    Usage example:
        substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
        plaintext: Hello
        ciphertext: Jrssb
 */
/* Build: gcc ../../vendor/cs50.c substitution.c -o substitution */

#include "../../vendor/cs50.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Wrong arguments number");
        return 1;
    }
    string key = argv[1];
    int key_length = strlen(argv[1]);

    if (key_length != 26)
    {
        printf("key must contain 26 characters");
        return 1;
    }

    for (int i = 0; i < key_length; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Your input is not alphabetical.\n");
            return 1;
        }

        for (int j = 0; j < key_length; j++)
        {
            if (tolower(key[i]) == tolower(key[j]) && i != j)
            {
                printf("Your key must containing each letter exactly once.\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, text_length = strlen(plaintext); i < text_length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int key_index = (tolower(plaintext[i]) - 97);
            if (islower(plaintext[i]))
            {
                printf("%c", (char)tolower((int)key[key_index]));
            }
            else
            {
                printf("%c", (char)toupper((int)key[key_index]));
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}