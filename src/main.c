#include <stdio.h>

#include "cli.h"
#include "main_functions.h"

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