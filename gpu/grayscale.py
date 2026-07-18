import time
import numpy as np
from PIL import Image
from numba import njit


@njit
def grayscale_cpu(rgb):
    height, width, _ = rgb.shape

    gray = np.empty((height, width), dtype=np.uint8)

    for y in range(height):
        for x in range(width):
            r = rgb[y, x, 0]
            g = rgb[y, x, 1]
            b = rgb[y, x, 2]

            gray[y, x] = (
                0.299 * r +
                0.587 * g +
                0.114 * b
            )

    return gray


def benchmark(rgb, iterations=100):
    grayscale_cpu(rgb)  # JIT compilation

    start = time.perf_counter()

    for _ in range(iterations):
        gray = grayscale_cpu(rgb)

    end = time.perf_counter()

    avg_ms = (end - start) * 1000 / iterations

    print(f"Average CPU time: {avg_ms:.3f} ms")

    return gray


def main():
    image = Image.open("../images/cat.ppm").convert("RGB")

    rgb = np.array(image, dtype=np.uint8)

    gray = benchmark(rgb)

    Image.fromarray(gray).save("../images/output_python.pgm")


if __name__ == "__main__":
    main()