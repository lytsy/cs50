/* Encrypts the text with the Caesar algorithm */
/* Build: gcc ../../vendor/cs50.c caesar.c -o caesar */
/* 
    Usage example:
        caesar 13
        plaintext: hello
        ciphertext: uryyb
*/
#include <stdio.h>
#include "../../vendor/cs50.h"
#include <string.h>
#include <stdlib.h>

void print_cipher_character(int letter_code, int key, int max_letter_code);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Wrong arguments number");
        return 1;
    }
    for (int i = 0, length = strlen(argv[1]); i < length; i++)
    {
        int letter_code = argv[1][i];
        if (letter_code < 48 || letter_code > 57)
        {
            printf("Usage: ./caesar key");
            return 1;
        }
    }
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        int letter_code = (int)plaintext[i];
        if ((letter_code >= 65 && letter_code <= 90))
        {
            print_cipher_character(letter_code, key, 90);
        }
        else if ((letter_code >= 97 && letter_code <= 122))
        {
            print_cipher_character(letter_code, key, 122);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    return 0;
}

void print_cipher_character(int letter_code, int key, int max_letter_code)
{
    int cipher_index = letter_code + key % 26;
    if (cipher_index > max_letter_code)
    {
        cipher_index -= 26;
    }
    printf("%c", (char)cipher_index);
}