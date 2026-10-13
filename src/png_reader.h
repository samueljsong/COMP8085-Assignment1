#ifndef PNG_READER_H
#define PNG_READER_H

#include <png.h>

typedef struct {
    int width;
    int height;
    int bit_depth;
    int color_type;
    int channels;
    uint64_t max_message_length;

    png_bytep *rows;
} Image;

Image *read_png(const char *filename);
void free_image(Image *image);
void print_pixels(const Image *image);
void alter_rgba_values(Image *image, char *cipher_text, size_t length);
int write_png(const char *filename, const Image *image);
uint32_t get_message_length(const Image *image);
int extract_cipher_text(Image *image, char *cipher_text, size_t length);

#endif