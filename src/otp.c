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

void otp_encrypt(char *clear_text, int *cipher_text, char *key, int length)
{
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    calculate_cipher_text_integers(clear_text, key, cipher_text, length);

    printf("\nOTP: ");
    for (int i = 0; i < length; i++)
    {
        printf("%c", alphabet[cipher_text[i]]);
    }

    printf("\nOTP Values: ");
    for (int i = 0; i < length; i++)
    {
        printf("%d ", cipher_text[i]);
    }
    printf("\n");
}

// When incorporating with the png, make it so that it accepts decimal arr instead of char
// This is because we want the calculations to be easier
void otp_decrypt(char *clear_text, char *cipher_text, char *key, int length)
{
    printf("OTP DECRYPT\n\n");

    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    for (int i = 0; i < length; i++)
    {
        int temp = (cipher_text[i] - 'a') - (key[i] - 'a');

        if (temp < 0)
        {
            temp = 26 + temp;
        }

        printf("%d ", temp);
    }
}