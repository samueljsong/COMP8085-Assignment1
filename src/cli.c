#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "cli.h"

static struct option long_options[] =
{
    {"encode", no_argument, NULL, 'e'},
    {"decode", no_argument, NULL, 'd'},
    {"help",   no_argument, NULL, 'h'},
    {NULL,     0,           NULL,  0 }
};

void print_usage()
{
    printf("Usage: [OPTIONS][paths...]\n\n");
    printf("Options:\n");
    printf("    -e, --encode <image_file> <cleartext_file> <secret>     Encode a message into a PNG\n");
    printf("    -d, --decode <image_file> <secret>                      Decode an encrypted message from a PNG\n");
    printf("    -h, --help                                              Display usage of the program\n");
}

int validate_file(char *file_path)
{
    FILE *file = fopen(file_path, "r");

    if (file == NULL)
    {
        return 0;
    }

    fclose(file);
    return 1;
}

int validate_png(char *file_path)
{
    if (file_path == NULL)
    {
        return 0;
    }

    char *dot = strrchr(file_path, '.');

    if (dot != NULL && strcmp(dot, ".png") == 0)
    {
        return 1;
    }

    return 0;
}

void parse_arguments(int argc, char *argv[], Config *config)
{
    int option;
    config->mode = MODE_NONE;

    while ((option = getopt_long(argc, argv, "edh", long_options, NULL)) != -1)
    {
        switch (option)
        {
            case 'e':

                if (config->mode != MODE_NONE)
                {
                    config->mode = MODE_NONE;
                    return;
                }

                if (argc - optind != 3)
                {
                    config->mode = MODE_ERROR;
                    config->error_message = "ERROR: encode requires <image_file> <cleartext_file> <secret>\n";
                    return;
                }

                if (!validate_file(argv[optind]))
                {
                    config->mode = MODE_ERROR;
                    config->error_message = "ERROR [FILE NOT FOUND]: Pleaase make sure the file path to the image is correct.";
                    return;
                }

                if (!validate_png(argv[optind]))
                {
                    config->mode = MODE_ERROR;
                    config->error_message = "ERROR [WRONG FILE]: Please ensure the image file is a png file.";
                    return;
                }

                if (!validate_file(argv[optind + 1]))
                {
                    config->mode = MODE_ERROR;
                    config->error_message = "ERROR [FILE NOT FOUND]: Please make sure the file path to the clear text is correct.";
                    return;
                }

                config->mode           = MODE_ENCRYPT;
                config->image_file     = argv[optind];
                config->cleartext_file = argv[optind + 1];
                config->secret         = argv[optind + 2];
                break;
            
            case 'd':
                if (config->mode != MODE_NONE)
                {
                    config->mode = MODE_NONE;
                    return;
                }
                config->mode = MODE_DECRYPT;
                break;
            
            case 'h':
                config->mode = MODE_HELP;
                print_usage();
                break;
            
            default:
                config->mode = MODE_ERROR;
                config->error_message = "ERROR: Something went wrong...";
                break;
        }
    }
}