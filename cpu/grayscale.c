#include <stdio.h>
#include <stdint.h>

void grayscale(const uint8_t *input,
               uint8_t *output,
               int width,
               int height)
{
    int num_pixels = width * height;

    for (int i = 0; i < num_pixels; i++)
    {
        int rgb_index = i * 3;

        uint8_t r = input[rgb_index];
        uint8_t g = input[rgb_index + 1];
        uint8_t b = input[rgb_index + 2];

        float gray = 0.299f * r +
                     0.587f * g +
                     0.114f * b;

        output[i] = (uint8_t)gray;
    }
}

int main()
{
    // Example: 2×2 image
    uint8_t image[] = {
        255, 0, 0,      // Red
        0, 255, 0,      // Green
        0, 0, 255,      // Blue
        255, 255, 255   // White
    };

    uint8_t gray[4];

    grayscale(image, gray, 2, 2);

    printf("Grayscale values:\n");

    for (int i = 0; i < 4; i++)
    {
        printf("%d ", gray[i]);
    }

    printf("\n");

    return 0;
}
