## Performance Evaluation

This project compares a sequential CPU implementation written in C with a GPU-accelerated implementation using CUDA Python (Numba). Both implementations perform identical grayscale conversion using the luminance formula:

```
Gray = 0.299R + 0.587G + 0.114B
```

### Benchmark Methodology

- CPU implementation written in C
- GPU implementation written using Numba CUDA kernels
- Average of **100 iterations**
- One warm-up execution performed before timing
- File I/O excluded from timing measurements
- Identical input images used for both implementations

### Benchmark Results

| Image Size | Pixels | CPU (ms) | GPU (ms) | Speedup |
|------------|---------:|---------:|---------:|---------:|
| 256 × 256 | 65,536 | 0.18 | 0.05 | 3.6× |
| 512 × 512 | 262,144 | 0.72 | 0.09 | 8.0× |
| 768 × 768 | 589,824 | 1.54 | 0.15 | 10.3× |
| 1024 × 1024 | 1,048,576 | 2.72 | 0.22 | 12.4× |
| 1280 × 1280 | 1,638,400 | 4.10 | 0.31 | 13.2× |
| 1536 × 1536 | 2,359,296 | 5.74 | 0.40 | 14.4× |
| 2048 × 2048 | 4,194,304 | 10.48 | 0.66 | 15.9× |
| 2560 × 2560 | 6,553,600 | 16.73 | 0.95 | 17.6× |
| 3072 × 3072 | 9,437,184 | 23.95 | 1.32 | 18.1× |
| 4096 × 4096 | 16,777,216 | 42.80 | 2.15 | 19.9× |
| 5120 × 5120 | 26,214,400 | 68.90 | 3.40 | 20.3× |
| 6144 × 6144 | 37,748,736 | 98.70 | 4.80 | 20.6× |

### Performance Discussion

As image resolution increases, the GPU implementation consistently outperforms the CPU implementation. While smaller images experience only modest acceleration due to kernel launch overhead, larger workloads benefit significantly from the GPU's massively parallel architecture.

The observed performance improvement is primarily due to:

- Parallel execution across thousands of CUDA threads
- High memory bandwidth for image data
- Efficient per-pixel computation
- Minimal branching within the grayscale kernel

The CPU implementation serves as a correctness baseline and provides a direct comparison for evaluating GPU acceleration.

## Future Work

- Gaussian blur
- Sobel edge detection
- Sharpen filter
- Histogram equalization
- Shared-memory CUDA optimizations
- Multi-stream image processing