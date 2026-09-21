#include <stdio.h>
#include <stdlib.h>
#include <png.h>

typedef struct {

    int rows;
    int cols;

    int **rmap;
    int **gmap;
    int **bmap;

} Image;


int main() {

	//Initialize Struct
	Image* img = malloc(sizeof(Image));

	//Initialize pointers for PNG contents prior to writing them to the struct
	png_byte color_type;
    png_bytep * row_pointers;

	//Initialize integers
	int i,j;

    FILE *fp = fopen("image.png", "rb");

    if (!fp) return 1;

    // Initialize structures
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);

	color_type = png_get_color_type(png_ptr, info_ptr);

	printf("Colortype: %d",color_type);

	if(color_type != PNG_COLOR_TYPE_RGB){
        fprintf(stderr, "[read_png_file] Only RGB PNGs are supported");
    }

   //png_read_update_info(png_ptr, info_ptr);

    if (!png_ptr || !info_ptr) {
			printf("Closing file prematurely...");
        fclose(fp);
        return 1;
    }

    // Set up error handling required by libpng
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return 1;
    }

	


    png_init_io(png_ptr, fp);
	png_read_info(png_ptr, info_ptr);

    //png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);


    //Read in the rows
    img->cols = png_get_image_width(png_ptr, info_ptr);
    img->rows = png_get_image_height(png_ptr, info_ptr);

	//Store the pointers to each row
	row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * img->rows);
    for (i = 0; i < img->rows; i += 1){
        row_pointers[i] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));
    } 

	png_read_image(png_ptr, row_pointers);

    printf("Rows: %d, Cols: %d\n", img->rows, img->cols);

    //Read in the maps for red, green and blue
    img->rmap = malloc(img->rows * sizeof(int *));
    for (i = 0; i < img->rows; i += 1)
        (img->rmap)[i] =  malloc(img->cols * sizeof(int));

    img->gmap = malloc(img->rows * sizeof(int *));
    for (i = 0; i < img->rows; i += 1)
        (img->gmap)[i] = malloc(img->cols * sizeof(int));

    img->bmap = malloc(img->rows * sizeof(int *));
    for (i = 0; i < img->rows; i += 1)
        (img->bmap)[i] = malloc(img->cols * sizeof(int));


	//printf("Size or row pointers: %lu",sizeof(row_pointers));
	
		//Populate themaps
		for (i = 0; i < img->rows; i += 1) {
			png_byte* row = row_pointers[i];
			for (j = 0; j < img->cols; j += 1) {
				png_byte* ptr = &(row[j * 3]);

				img->rmap[i][j] = ptr[0];
				img->gmap[i][j] = ptr[1];
				img->bmap[i][j] = ptr[2];
			}
		}	


    //Iterate through the pixels
    for(i = 0; i < img->rows; i += 1){
        for(j = 0; j < img->cols ; j += 1){
			printf("Pixel [%d,%d]:",i,j);
            printf("r:%d", img->rmap[i][j]);
            printf("g:%d", img->gmap[i][j]);
            printf("b:%d", img->bmap[i][j]);
			printf("\n");
        }
    }

    // Clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
    return 0;
}
