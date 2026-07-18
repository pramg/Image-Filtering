#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static int read_token(FILE *fp, char *buf, size_t bufsize) {
    int c;

    do {
        c = fgetc(fp);
        if (c == '#') {
            while (c != '\n' && c != EOF) {
                c = fgetc(fp);
            }
        }
    } while (c != EOF && isspace(c));

    if (c == EOF) {
        return 0;
    }

    size_t i = 0;
    while (c != EOF && !isspace(c) && c != '#') {
        if (i + 1 < bufsize) {
            buf[i++] = (char)c;
        }
        c = fgetc(fp);
    }
    buf[i] = '\0';

    if (c == '#') {
        while (c != '\n' && c != EOF) {
            c = fgetc(fp);
        }
    } else if (c != EOF) {
        ungetc(c, fp);
    }

    return 1;
}

int read_ppm(const char *filename, PPMImage *img) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Error: could not open %s\n", filename);
        return 0;
    }

    char token[64];

    if (!read_token(fp, token, sizeof(token)) || strcmp(token, "P6") != 0) {
        fprintf(stderr, "Error: %s is not a P6 PPM file\n", filename);
        fclose(fp);
        return 0;
    }

    if (!read_token(fp, token, sizeof(token))) {
        fprintf(stderr, "Error: could not read width\n");
        fclose(fp);
        return 0;
    }
    img->width = atoi(token);

    if (!read_token(fp, token, sizeof(token))) {
        fprintf(stderr, "Error: could not read height\n");
        fclose(fp);
        return 0;
    }
    img->height = atoi(token);

    if (!read_token(fp, token, sizeof(token))) {
        fprintf(stderr, "Error: could not read maxval\n");
        fclose(fp);
        return 0;
    }
    img->maxval = atoi(token);

    if (img->width <= 0 || img->height <= 0 || img->maxval != 255) {
        fprintf(stderr, "Error: unsupported PPM dimensions or maxval\n");
        fclose(fp);
        return 0;
    }

    int c = fgetc(fp);
    if (c != EOF && !isspace(c)) {
        ungetc(c, fp);
    }

    size_t num_bytes = (size_t)img->width * (size_t)img->height * 3;
    img->data = (unsigned char *)malloc(num_bytes);
    if (!img->data) {
        fprintf(stderr, "Error: could not allocate memory for image data\n");
        fclose(fp);
        return 0;
    }

    size_t read_count = fread(img->data, 1, num_bytes, fp);
    fclose(fp);

    if (read_count != num_bytes) {
        fprintf(stderr, "Error: could not read full image data\n");
        free(img->data);
        img->data = NULL;
        return 0;
    }

    return 1;
}

int write_pgm(const char *filename,
              const unsigned char *data,
              int width,
              int height,
              int maxval) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "Error: could not open %s for writing\n", filename);
        return 0;
    }

    fprintf(fp, "P5\n%d %d\n%d\n", width, height, maxval);

    size_t num_bytes = (size_t)width * (size_t)height;
    size_t written = fwrite(data, 1, num_bytes, fp);
    fclose(fp);

    if (written != num_bytes) {
        fprintf(stderr, "Error: could not write full output image\n");
        return 0;
    }

    return 1;
}

void free_ppm(PPMImage *img) {
    if (img && img->data) {
        free(img->data);
        img->data = NULL;
    }
}