#include <stdbool.h>
#ifndef CLI_H
#define CLI_H

typedef enum
{
    MODE_NONE,
    MODE_ENCRYPT,
    MODE_DECRYPT,
    MODE_HELP,
    MODE_ERROR
}CliMode;

typedef struct 
{
    CliMode mode;
    char    *image_file;
    char    *cleartext_file;
    char    *secret;
    bool    is_secret_text_file;
    char    *error_message;
}Config;

void parse_arguments(int argc, char *argv[], Config *config);
void print_usage();

#endif