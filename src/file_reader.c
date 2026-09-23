#include <stdio.h>

void process_file(char *clear_text_buffer)
{
    FILE *file;
    file = fopen("docs/message.txt", "r");

    // Checking to see if the file exists
    if (file == NULL)
    {
        printf("File empty");
        fclose(file);
        return;
    }

    while (fgets(clear_text_buffer, sizeof(clear_text_buffer), file) != NULL)
    {
        printf("%s", clear_text_buffer);
    }

    fclose(file);
}