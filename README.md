# GPU Image Processing

A performance-oriented image processing project comparing CPU implementations written in C with GPU implementations using CUDA Python (Numba).

## Features

- PPM image reader
- CPU grayscale conversion (C)
- GPU grayscale conversion (CUDA Python / Numba) *(coming soon)*
- Performance benchmarking
- Side-by-side CPU vs GPU comparison

## Project Structure

```
image-processing/
├── cpu/
├── gpu/
├── images/
└── README.md
```

## Building the CPU Version

```bash
gcc cpu/main.c cpu/ppm.c -o grayscale
```

Run:

```bash
./grayscale images/cat.ppm images/output.pgm
```

## Performance Evaluation

> Placeholder benchmark results. Replace these with measurements collected on your own hardware before publishing.

| Image Size | CPU (ms) | GPU (ms) | Speedup |
|------------|---------:|---------:|---------:|
| 256×256 | 0.18 | 0.05 | 3.6× |
| 512×512 | 0.72 | 0.09 | 8.0× |
| 1024×1024 | 2.72 | 0.22 | 12.4× |
| 2048×2048 | 10.48 | 0.66 | 15.9× |
| 4096×4096 | 42.80 | 2.15 | 19.9× |

## Future Work

- GPU grayscale conversion
- Gaussian blur
- Sobel edge detection
- Shared-memory CUDA optimization
- Performance visualization