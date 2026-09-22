#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "png_reader.h"

#define BUFFER_SIZE 256 //size of 256 Bytes

void create_steno_image ()
{
    printf("Creating steno image");
}

int main (int argc, char *argv[]) {


    if (strcmp(argv[1], "-e") == 0)
    {
        printf("encoding started\n");

        FILE *fptr;

        fptr = fopen("docs/message.txt", "r");

        // Checking to see if the file exists
        if (fptr == NULL)
        {
            printf("File empty");
            return 1;
        }

        char message[BUFFER_SIZE];

        while (fgets(message, sizeof(message), fptr) != NULL)
        {
            printf("%s", message);
        }

        int length = strlen(message);

        printf("\n\nLength of the word is: %d", length);

        fclose(fptr);
        // see if i can open the message.txt file and read it.

    }
    else if (strcmp(argv[1], "-d") == 0){
        printf("Decoding started");
    }
    else{
        Image *image = read_png("docs/image.png");
    
        if (image == NULL)
        {
            printf("ERROR");
            return EXIT_FAILURE;
        }
    
        printf("Width: %d\n", image->width);
        printf("Height: %d\n", image->height);
        printf("Bit depth: %d\n", image->bit_depth);
        printf("Color type: %d\n", image->color_type);
        printf("Channels: %d\n", image->channels);
    
        print_pixels(image);
        free_image(image);
    }

    return 0;
}