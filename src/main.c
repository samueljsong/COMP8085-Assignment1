#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "png_reader.h"
#include "otp.h"
#include "file_reader.h"
#include "bit_utils.h"
#include "cli.h"

#define BUFFER_SIZE 256 //size of 256 Bytes

void create_steno_image ()
{
    printf("Creating steno image");
}

void encode(Config *config)
{
    printf("\nEncoding started...\n\n");
    char clear_text_buffer[BUFFER_SIZE];  

    process_file(clear_text_buffer);
    
    int   length              = strlen(clear_text_buffer);
    char *key                 = config->secret;
    char *clear_text          = malloc(length + 1);
    int  *cipher_text_decimal = malloc(length + 1);
    strcpy(clear_text, clear_text_buffer); // copying the message in txt file to clear_text

    otp_encrypt(clear_text, cipher_text_decimal, key, length);

    int *cipher_text_bits = malloc(length * 5 * sizeof(int));

    convert_to_binary(cipher_text_decimal, cipher_text_bits, length);

    // for (int i = 0; i < length * 5; i++)
    // {
    //     if (i != 0 && i % 5 == 0)
    //     {
    //         printf(" ");
    //     }

    //     printf("%d", cipher_text_bits[i]);
    // }

    printf("\nPNG Information:\n--------------------------\n");


    Image *image = read_png(config->image_file);

    alter_rgba_values(image, cipher_text_bits, length * 5);

    write_png("output.png", image);

    free(clear_text);
    free(cipher_text_bits);
    free(cipher_text_decimal);
    free(image);
}

void decode(Config *config)
{
    char cipher_text_buffer[BUFFER_SIZE];

    process_file(cipher_text_buffer);

    int   length      = strlen(cipher_text_buffer);
    char *key         = config->secret;
    char *clear_text  = malloc(length + 1);
    char *cipher_text = malloc(length + 1);
    strcpy(cipher_text, cipher_text_buffer);

    otp_decrypt(clear_text, cipher_text, key, length);

    free(clear_text);
    free(cipher_text);
}

int main (int argc, char *argv[]) 
{
    Config config;
    parse_arguments(argc, argv, &config);

    switch(config.mode)
    {
        case MODE_ENCRYPT:
            encode(&config);
            break;
        
        case MODE_DECRYPT:
            decode(&config);
            break;
        
        case MODE_HELP:
            print_usage();
            break;
        
        case MODE_NONE:
            break;
            
        default:
            printf("%s", config.error_message);
            break;
    }

    return 0;
}