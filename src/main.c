#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#include "png_reader.h"
#include "otp.h"
#include "file_reader.h"
#include "bit_utils.h"
#include "cli.h"

void encode(Config *config)
{
    printf("\nEncoding started...\n");

    printf("\nPNG Information:\n--------------------------\n");

    Image *image = read_png(config->image_file);

    // Calculate maximum characters based on 8 bits per character
    uint64_t max_characters = image->max_message_length / 8;

    printf("Maximum characters encodable: %" PRIu64 "\n\n", max_characters);

    // Allocate memory based on maximum characters
    char *clear_text_buffer = malloc((size_t)max_characters + 1);

    if(process_file(clear_text_buffer, config->cleartext_file, max_characters + 1) == 1)
    {
        return;
    }

    char *key;

    if (config->is_secret_text_file)
    {
        key = malloc((size_t)max_characters + 1);
        if(process_file(key, config->secret, max_characters + 1) == 1)
        {
            return;
        }
    }
    else
    {
        key = config->secret;
    }
    
    int   length      = strlen(clear_text_buffer);
    char *clear_text  = malloc(length + 1);
    char *cipher_text = malloc(length + 1);

    strcpy(clear_text, clear_text_buffer); // copying the message in txt file to clear_text

    otp_encrypt(clear_text, cipher_text, key, length);

    alter_rgba_values(image, cipher_text, length);

    write_png("./docs/output.png", image);

    if (config->is_secret_text_file)
    {
        free(key);
    }
    free(clear_text);
    free(cipher_text);
    free(image);
}

void decode(Config *config)
{
    printf("\nDecoding started...\n");

    printf("\nPNG Information:\n--------------------------\n");

    Image *image = read_png(config->image_file);

    uint64_t max_characters = image->max_message_length / 8;
    uint32_t message_bits = get_message_length(image);

    // Validate the message length
    if (message_bits % 8 != 0 ||
        (uint64_t)message_bits > image->max_message_length)
    {
        fprintf(stderr, "ERROR: Invalid message length\n");
        free_image(image);
        return;
    }

    size_t length = message_bits / 8;

    char *key;

    if (config->is_secret_text_file)
    {
        key = malloc((size_t)max_characters + 1);
        if(process_file(key, config->secret, max_characters + 1) == 1)
        {
            return;
        }
    }
    else
    {
        key = config->secret;
    }

    char *cipher_text = malloc(length + 1);
    char *clear_text = malloc(length + 1);

    if (extract_cipher_text(image, cipher_text, length) != 0)
    {
        printf("ERROR ON EXTRACTING\n");

        if (config->is_secret_text_file)
            free(key);

        free(cipher_text);
        free(clear_text);
        free_image(image);
        return;
    }


    if (length != strlen(key))
    {
        printf("\nERROR [WRONG KEY PROVIDED]: The key is not the same length as the cipher text\n");
        return;
    }

    otp_decrypt(cipher_text, clear_text, key, length);

    if (config->is_secret_text_file)
    {
        free(key);
    }

    free(cipher_text);
    free_image(image);
    free(clear_text);
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