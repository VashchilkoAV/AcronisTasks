#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define PNG_DEBUG 3
#include <png.h>

void abort_(const char * s, ...)
{
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}

int x, y;

int** weights;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

void read_png_file(char* file_name)
{
    char header[8];    // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    if (!fp)
        abort_("[read_png_file] File %s could not be opened for reading", file_name);
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
        abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);


    /* initialize stuff */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
        abort_("[read_png_file] png_create_read_struct failed");

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        abort_("[read_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[read_png_file] Error during init_io");

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);


    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[read_png_file] Error during read_image");

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (y=0; y<height; y++)
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

    png_read_image(png_ptr, row_pointers);

    fclose(fp);
}


void write_png_file(char* file_name)
{
    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp)
        abort_("[write_png_file] File %s could not be opened for writing", file_name);


    /* initialize stuff */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
        abort_("[write_png_file] png_create_write_struct failed");

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        abort_("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] Error during init_io");

    png_init_io(png_ptr, fp);


    /* write header */
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] Error during writing header");

    png_set_IHDR(png_ptr, info_ptr, width, height,
                 bit_depth, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);


    /* write bytes */
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] Error during writing bytes");

    png_write_image(png_ptr, row_pointers);


    /* end write */
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    /* cleanup heap allocation */
    for (y=0; y<height; y++)
        free(row_pointers[y]);
    free(row_pointers);

    fclose(fp);
}

int GetDist(png_byte* p, png_byte* ptr) {
    return (p[0]-ptr[0])*(p[0]-ptr[0])+(p[1]-ptr[1])*(p[1]-ptr[1])+(p[2]-ptr[2])*(p[2]-ptr[2]);
}

void process_file(void)
{
    if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
        abort_("[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
               "(lacks the alpha channel)");

    if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
        abort_("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)",
               PNG_COLOR_TYPE_RGBA, png_get_color_type(png_ptr, info_ptr));

    for (y=0; y<height; y++) {
        png_byte* row = row_pointers[y];
        for (x=0; x<width; x++) {
            png_byte* ptr = &(row[x*4]);
//            printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
//                   x, y, ptr[0], ptr[1], ptr[2], ptr[3]);

            int dists[8];
            if (x > 0 && y > 0) { //left-down
                png_byte * p = &row_pointers[y-1][4*(x-1)];
                dists[0] = GetDist(p, ptr);
            } else {
                dists[0] = -1;
            }
            if (x > 0) { //left-still
                png_byte * p = &row_pointers[y][4*(x-1)];
                dists[1] = GetDist(p, ptr);
            } else {
                dists[1] = -1;
            }
            if (x > 0 && y < height-1) { //left-up
                png_byte * p = &row_pointers[y+1][4*(x-1)];
                dists[2] = GetDist(p, ptr);
            } else {
                dists[2] = -1;
            }
            if (y < height-1) { //still-up
                png_byte * p = &row_pointers[y+1][4*(x)];
                dists[3] = GetDist(p, ptr);
            } else {
                dists[3] = -1;
            }
            if (x < width-1 && y < height-1) { //right-up
                png_byte * p = &row_pointers[y+1][4*(x+1)];
                dists[4] = GetDist(p, ptr);
            } else {
                dists[4] = -1;
            }
            if (x < width-1) { //right-still
                png_byte * p = &row_pointers[y][4*(x+1)];
                dists[5] = GetDist(p, ptr);
            } else {
                dists[5] = -1;
            }
            if (x < width-1 && y > 0) { //rigth-down
                png_byte * p = &row_pointers[y-1][4*(x+1)];
                dists[6] = GetDist(p, ptr);
            } else {
                dists[6] = -1;
            }
            if (y > 0) { //still-down
                png_byte * p = &row_pointers[y-1][4*(x)];
                dists[7] = GetDist(p, ptr);
            } else {
                dists[7] = -1;
            }

            int sum = 0, i = 0;
            for (i; i < 8; i++) {
                sum += (dists[i] == -1) ? 0 : dists[i];
            }
            if (y == 2) {

            }
            weights[y][x]= sum;

        }
    }
}



int main(int argc, char **argv) {
    read_png_file("fruit.png");
    weights = (int**) malloc(height*sizeof(int*));
    int i = 0, j = 0;
    for (i = 0; i < height; i++) {
        weights[i] = (int*)malloc(width*sizeof(int));
    }
    process_file();

    printf("%d %d\n", height, width);
    i = 0; j = 0;
    for (i = 0; i < height; i++) {
        if (i == 1);
        for (j = 0; j < width; j++) {
            printf("%d ", weights[i][j]);
        }
        printf("\n");
    }

    write_png_file("fruit1.png");
    for (i = 0; i < height; i++) {
        free(weights[i]);
    }
    free(weights);
    return 0;
}