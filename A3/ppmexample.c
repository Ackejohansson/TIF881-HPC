#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <png.h>

#define WIDTH 100
#define HEIGHT 100
#define MAX_COLOR 255

// Function to generate a random color
void generateRandomColor(int *r, int *g, int *b) {
    *r = rand() % (MAX_COLOR + 1);
    *g = rand() % (MAX_COLOR + 1);
    *b = rand() % (MAX_COLOR + 1);
}

// Function to create a PNG image
void createPNGImage(const char *filename, int width, int height) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(fp);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, NULL);
        fclose(fp);
        return;
    }

    png_init_io(png, fp);
    png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    for (int y = 0; y < height; y++) {
        png_byte row[width * 3]; // 3 bytes per pixel (RGB)
        for (int x = 0; x < width; x++) {
            int r, g, b;
            generateRandomColor(&r, &g, &b);
            row[x * 3] = r; // Red
            row[x * 3 + 1] = g; // Green
            row[x * 3 + 2] = b; // Blue
        }
        png_write_row(png, row);
    }

    png_write_end(png, NULL);
    png_destroy_write_struct(&png, &info);
    fclose(fp);
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    // Create and save the random color PNG image
    createPNGImage("random_colors.png", WIDTH, HEIGHT);

    return 0;
}
