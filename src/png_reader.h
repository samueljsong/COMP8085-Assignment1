#ifndef PNG_READER_H
#define PNG_READER_H

#include <png.h>

typedef struct {
    int width;
    int height;
    int bit_depth;
    int color_type;
    int channels;

    png_bytep *rows;
} Image;

Image *read_png(const char *filename);
void free_image(Image *image);
void print_pixels(const Image *image);

#endif