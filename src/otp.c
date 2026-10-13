#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "otp.h"

void calculate_cipher_text_integers(char *textArray, char *keyArray, int* cipherTextArray, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        cipherTextArray[i] = abs(((textArray[i] - 'a') + (keyArray[i] - 'a')) % 26);
    }
}

void print_integer_values(char *arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i] - 'a');
    }

    printf("\n");
}

void convert_to_lowercase(char *arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        arr[i] = tolower(arr[i]);
    }
}

void otp_encrypt(char *clear_text, char *cipher_text, char *key, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        cipher_text[i] = clear_text[i] ^ key[i];
    }

    printf("\nOTP Values (Decimal): ");
    for (size_t i = 0; i < length; i++)
    {
        printf("%u ", (unsigned char)cipher_text[i]);
    }

    printf("\n");
}

void otp_decrypt(char *cipher_text, char *clear_text, char *key, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        clear_text[i] = cipher_text[i] ^ key[i];
    }

    printf("\nDecoded Values (Decimal): ");
    for (size_t i = 0; i < length; i++)
    {
        printf("%u ", (unsigned char)clear_text[i]);
    }

    printf("\nDecoded Message: ");
    for (size_t i = 0; i < length; i++)
    {
        printf("%c", clear_text[i]);
    }

    printf("\n");
}