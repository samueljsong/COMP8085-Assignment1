#include <stdio.h>

int process_file(char *clear_text_buffer, char *file_path, size_t buffer_size)
{
    FILE *file;
    file = fopen(file_path, "rb");

    // Checking to see if the file exists
    if (file == NULL)
    {
        printf("File empty");
        return 1;
    }

    if (buffer_size == 0)
    {
        fclose(file);
        return 1;
    }

    // Read at most buffer_size - 1 bytes
    size_t bytes_read = fread(clear_text_buffer, 1, buffer_size - 1, file);

    if (ferror(file))
    {
        fprintf(stderr, "ERROR: reading file\n");
        fclose(file);
        return 1;
    }

    // Check whether more data remains
    if (fgetc(file) != EOF)
    {
        fprintf(stderr, "ERROR: Clear text exceeds maximum message length\n");
        fclose(file);
        return 1;
    }

    clear_text_buffer[bytes_read] = '\0';

    printf("File Contains: %s\n", clear_text_buffer);

    fclose(file);
    return 0;
}