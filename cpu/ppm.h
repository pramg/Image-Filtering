#ifndef PPM_H
#define PPM_H

typedef struct {
    int width;
    int height;
    int maxval;
    unsigned char *data;  // RGB data: width * height * 3 bytes
} PPMImage;

int read_ppm(const char *filename, PPMImage *img);
int write_pgm(const char *filename,
              const unsigned char *data,
              int width,
              int height,
              int maxval);
void free_ppm(PPMImage *img);

#endif