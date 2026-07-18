#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include <time.h>
static void grayscale(const unsigned char *rgb,
                      unsigned char *gray,
                      int width,
                      int height) {
    size_t num_pixels = (size_t)width * (size_t)height;

    for (size_t i = 0; i < num_pixels; i++) {
        size_t j = i * 3;

        float r = (float)rgb[j];
        float g = (float)rgb[j + 1];
        float b = (float)rgb[j + 2];

        float value = 0.299f * r + 0.587f * g + 0.114f * b;

        if (value < 0.0f) value = 0.0f;
        if (value > 255.0f) value = 255.0f;

        gray[i] = (unsigned char)(value + 0.5f);
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.ppm output.pgm\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    PPMImage img = {0};

    if (!read_ppm(input_file, &img)) {
        return 1;
    }

    size_t num_pixels = (size_t)img.width * (size_t)img.height;
    unsigned char *gray = (unsigned char *)malloc(num_pixels);
    if (!gray) {
        fprintf(stderr, "Error: could not allocate grayscale buffer\n");
        free_ppm(&img);
        return 1;
    }
    clock_t start = clock();
    grayscale(img.data, gray, img.width, img.height);
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Grayscale conversion took %.6f seconds\n", elapsed_time);
    if (!write_pgm(output_file, gray, img.width, img.height, img.maxval)) {
        free(gray);
        free_ppm(&img);
        return 1;
    }

    free(gray);
    free_ppm(&img);

    printf("Wrote grayscale image to %s\n", output_file);
    return 0;
}