#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include "png_reader.h"

static FILE        *open_png_file        (const char *filename);
static png_structp initialize_png_structs(FILE *fp, png_infop *info_ptr);
static png_bytep   *allocate_memory      (png_structp png_ptr, png_infop info_ptr, int height);

static void read_png_metadata(png_structp png_ptr, png_infop info_ptr, int *width, int *height, int *bit_depth, int *color_type);
static void process_pixels   (png_bytep *row_pointers, int width, int height);
static void free_memory      (png_bytep *row_pointers, int height);
static void cleanup          (FILE *fp, png_structp png_ptr, png_infop info_ptr);


Image *read_png(const char *filename)
{
    FILE *fp;
    png_infop info_ptr;
    png_structp png_ptr;

    Image *image = malloc(sizeof(Image));

    if (image == NULL)
    {
        return NULL;
    }

    fp = open_png_file(filename);
    png_ptr = initialize_png_structs(fp, &info_ptr);
    read_png_metadata(
        png_ptr, 
        info_ptr, 
        &image->width, 
        &image->height, 
        &image->bit_depth, 
        &image->color_type
    );

    image -> channels = png_get_channels(png_ptr, info_ptr);
    image -> rows     = allocate_memory(
        png_ptr,
        info_ptr,
        image->height
    );

    cleanup(fp, png_ptr, info_ptr);

    return image;
}

void free_image(Image *image)
{
    if (image == NULL)
    {
        return;
    }

    for (int y = 0; y < image -> height; y++)
    {
        free(image->rows[y]);
    }

    free(image->rows);
    free(image);
}

void print_pixels(const Image *image)
{
    if (image == NULL)
    {
        return;
    }

    for (int y = 0; y < image->height; y++)
    {
        for (int x = 0; x < image->width; x++)
        {
            png_bytep pixel = &image->rows[y][x * image->channels];
            printf("Pixel [%d, %d]: ", x, y);

            for (int c = 0; c < image->channels; c++)
            {
                printf("%d ", pixel[c]);
            }

            printf("\n");
        }
    }
}

void alter_rgba_values(const Image *image, int *cipher_text_binary, int cipher_text_binary_length)
{
    if (image == NULL)
    {
        return;
    }

    int cipher_text_counter = 0;

    for (int y = 0; y < image->height; y++)
    {
        for (int x = 0; x < image->width; x++)
        {
            png_bytep pixel = &image->rows[y][x * image->channels];

            for (int c = 0; c < image->channels; c++)
            {
                if (cipher_text_counter == cipher_text_binary_length)
                {
                    return;
                }

                int cipher_text_bit = cipher_text_binary[cipher_text_counter];

                if (cipher_text_bit == 1)
                {
                    pixel[c] = pixel[c] | cipher_text_bit; 
                }
                
                if (cipher_text_bit == 0)
                {
                    pixel[c] = pixel[c] & cipher_text_bit;
                }

                cipher_text_counter++;
            }
        }

    }
}

// png_structp controls the writing process
// png_infop describes what the image should look like.
int write_png(const char *filename, const Image *image)
{
    FILE *fp = fopen(filename, "wb");

    if (fp == NULL)
    {
        return 1;
    }

    // png_structp is a libpng defined pointer type 
    // -> main obj libpng will use to keep track of the png writing process
    png_structp png = png_create_write_struct(
        PNG_LIBPNG_VER_STRING,  // tells the libpng  which version your program was compiled against. from png.h
        NULL, // nulls are saying use default behaviour
        NULL, // you would provide custom handlers in the three NULLS
        NULL
    );

    if (png == NULL)
    {
        fclose(fp);
        return 1;
    }

    // creates another libpng structure keeping track of
    //width, height, bit depth, color type, interlacing, etc.
    png_infop info = png_create_info_struct(png);

    if (info == NULL)
    {
        png_destroy_write_struct(&png, NULL);
        fclose(fp);
        return 1;
    }

    // connects your writer to the actual file you are going to be writing out
    png_init_io(png, fp);

    // sets te image header
    png_set_IHDR(
        png,
        info,
        image->width,
        image->height,
        8,  // each color channel uses 8 bit -> 255
        PNG_COLOR_TYPE_RGBA,            // Tells libpng each pixel has RGBA values
        PNG_INTERLACE_NONE,             // Don't use interlacing
        PNG_COMPRESSION_TYPE_DEFAULT,   // normal png compression
        PNG_FILTER_TYPE_DEFAULT         // normal filter
    );

    png_write_info(png, info);
    png_write_image(png, image->rows);
    png_write_end(png, NULL);
    png_destroy_write_struct(&png, &info);

    fclose(fp);

    return 0;
}

static FILE *open_png_file(const char *filename)
{
    FILE *fp;

    fp = fopen(filename, "rb");

    if(!fp)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    return fp;
}

static png_structp initialize_png_structs(FILE *fp, png_infop *info_ptr)
{
    png_structp png_ptr;

    png_ptr= png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if(!png_ptr)
    {
        fclose(fp);
        perror("Failed to create png_struct");
        exit(EXIT_FAILURE);
    }

    *info_ptr = png_create_info_struct(png_ptr);

    if(!*info_ptr)
    {
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(fp);
        perror("Failed to create info_struct");
        exit(EXIT_FAILURE);
    }

    if(setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, info_ptr, NULL);
        fclose(fp);
        perror("Error during PNG read");
        exit(EXIT_FAILURE);
    }

    png_init_io(png_ptr, fp);

    return png_ptr;
}

static void read_png_metadata(png_structp png_ptr, png_infop info_ptr, int *width, int *height, int *bit_depth, int *color_type)
{
    png_read_info(png_ptr, info_ptr);
    *width      = png_get_image_width(png_ptr, info_ptr);
    *height     = png_get_image_height(png_ptr, info_ptr);
    *bit_depth  = png_get_bit_depth(png_ptr, info_ptr);
    *color_type = png_get_color_type(png_ptr, info_ptr);
    printf("Image Width: %d, Height: %d, Bit Depth: %d, Color Type: %d\n",  *width, *height, *bit_depth, *color_type);

    if(*color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(png_ptr);
    }

    if(*color_type == PNG_COLOR_TYPE_GRAY && *bit_depth < 8)
    {
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    }

    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(png_ptr);
    }

    if(*bit_depth == 16)
    {
        png_set_strip_16(png_ptr);
    }

    png_read_update_info(png_ptr, info_ptr);
}

static png_bytep *allocate_memory(png_structp png_ptr, png_infop info_ptr, int height)
{
    png_bytep *row_pointers;

    row_pointers= (png_bytep *)malloc(sizeof(png_bytep) * height);

    if(!row_pointers)
    {
        perror("Failed to allocate memory for rows");
        exit(EXIT_FAILURE);
    }

    for(int y = 0; y < height; y++)
    {
        row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png_ptr, info_ptr));

        if(!row_pointers[y])
        {
            perror("Failed to allocate memory for a row");
            exit(EXIT_FAILURE);
        }
    }

    png_read_image(png_ptr, row_pointers);

    return row_pointers;
}

static void process_pixels(png_bytep *row_pointers, int width, int height)
{
    printf("Pixel data (assuming RGBA):\n");

    for(int y = 0; y < height; y++)
    {
        png_bytep row = row_pointers[y];

        for(int x = 0; x < width; x++)
        {
            png_bytep px;

            px = &(row[x * 4]); // Assuming RGBA format
            printf("Pixel at (%d, %d): R=%d G=%d B=%d A=%d\n", x, y, px[0], px[1], px[2], px[3]);
        }
    }
}

static void free_memory(png_bytep *row_pointers, int height)
{
    for(int y = 0; y < height; y++)
    {
        free(row_pointers[y]);
    }

    free(row_pointers);
}

static void cleanup(FILE *fp, png_structp png_ptr, png_infop info_ptr)
{
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
}

