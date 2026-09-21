#include <stdio.h>
#include <stdlib.h>
#include <png.h>

static FILE *open_png_file(const char *filename);
static png_structp initialize_png_structs(FILE *fp, png_infop *info_ptr);
static void read_png_metadata(png_structp png_ptr, png_infop info_ptr, int *width, int *height, int *bit_depth, int *color_type);
static png_bytep *allocate_memory(png_structp png_ptr, png_infop info_ptr, int height);
static void process_pixels(png_bytep *row_pointers, int width, int height);
static void free_memory(png_bytep *row_pointers, int height);
static void cleanup(FILE *fp, png_structp png_ptr, png_infop info_ptr);


int main(int argc, char *argv[])
{
    int width;
    int height;
    int bit_depth;
    int color_type;
    const char *filename;
    FILE *fp;
    png_infop info_ptr;
    png_structp png_ptr;
    png_bytep *row_pointers;

    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    filename = argv[1];
    fp = open_png_file(filename);
    png_ptr = initialize_png_structs(fp, &info_ptr);
    read_png_metadata(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type);
    row_pointers = allocate_memory(png_ptr, info_ptr, height);
    process_pixels(row_pointers, width, height);
    free_memory(row_pointers, height);
    cleanup(fp, png_ptr, info_ptr);

    return EXIT_SUCCESS;
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

