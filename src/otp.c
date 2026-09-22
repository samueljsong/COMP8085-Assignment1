#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "otp.h"

void calculateCipherTextIntegers(char *textArray, char *keyArray, int* cipherTextArray, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        cipherTextArray[i] = abs(((textArray[i] - 'a') + (keyArray[i] - 'a')) % 26);
    }
}

void getKeyTextFromUserInput(char **keyText, size_t *bufferSize, int length)
{
    printf("Please enter a key of length %d\n", length);
    ssize_t inputLength = getline(keyText, bufferSize, stdin);  //basically does malloc and realloc if needed.

    if (inputLength > 0 && (*keyText)[inputLength - 1] == '\n')
    {
        inputLength--;
    }

    if (inputLength != length)
    {
        printf("Key is not %d characters long", length);
    }

    printf("Your key: %s", *keyText);
}

int getClearTextFromUserInput(char **clearText, size_t *bufferSize)
{
    printf("Please enter a word you wish to convert to a Ciphertext\n");
    ssize_t inputLength = getline(clearText, bufferSize, stdin);

    if (inputLength > 0 && (*clearText)[inputLength - 1] == '\n')
    {
        inputLength--;
    }

    printf("Your text: %s", *clearText);

    return inputLength;
}

void printIntegerValues(char *arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i] - 'a');
    }

    printf("\n");
}

void convertToLowerCase(char *arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        arr[i] = tolower(arr[i]);
    }
}

void otp_encrypt(
    const unsigned char *clear_text, 
    const unsigned char *key, 
    unsigned char *cipher_text, 
    int length
)
{

//     char   alphabet[]          = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
//     char   *keyText            = NULL; //Creates pointer but has no space because getline will do that for us (not an array)
//     char   *clearText          = NULL; 
//     size_t keyBufferSize       = 0;    //Going to tell getline() how much memory is currently available at that address
//     size_t clearTextBufferSize = 0;    //value 0 is basically telling getline() to allocate for us
    
//     int length = getClearTextFromUserInput(&clearText, &keyBufferSize);
//     convertToLowerCase(clearText, length);
//     printf("ClearText Integer Values: ");
//     printIntegerValues(clearText, length);
//     printf("\n");

//     getKeyTextFromUserInput(&keyText, &clearTextBufferSize, length);
//     convertToLowerCase(keyText, length);
//     printf("KeyText Integer Values: ");
//     printIntegerValues(keyText, length);

//     int ciphertextArray[length];

//     calculateCipherTextIntegers(clearText, keyText, ciphertextArray, length);

//     printf("\nOTP: ");
//     for (int i = 0; i < length; i++)
//     {
//         printf("%c", alphabet[ciphertextArray[i]]);
//     }

//     printf("\nOTP Values: ");
//     for (int i = 0; i < length; i++)
//     {
//         printf("%d ", ciphertextArray[i]);
//     }
//     printf("\n");

//     free(clearText); //dynamically allocated data remains allocated until we explicitly release it.
//     free(keyText);
}

void decrypt(
    const unsigned char *clear_text, 
    const unsigned char *key, 
    unsigned char *cipher_text, 
    int length
)
{
    
}