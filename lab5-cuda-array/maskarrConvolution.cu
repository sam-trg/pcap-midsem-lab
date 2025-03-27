#include <stdio.h>
#include <cuda.h>

#define MASK_WIDTH 3

__global__ void convolution1D(int *N, int *M, int *P, int width) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int radius = MASK_WIDTH / 2;

    if (idx < width) {
        int result = 0;
        for (int i = -radius; i <= radius; i++) {
            int neighbor_idx = idx + i;
            if (neighbor_idx >= 0 && neighbor_idx < width) {
                result += N[neighbor_idx] * M[radius + i];
            }
        }
        P[idx] = result;
    }
}

int main() {
    const int width = 10;
    int N[width] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int M[MASK_WIDTH] = {1, 0, -1};
    int P[width];

    int *d_N, *d_M, *d_P;
    cudaMalloc(&d_N, width * sizeof(int));
    cudaMalloc(&d_M, MASK_WIDTH * sizeof(int));
    cudaMalloc(&d_P, width * sizeof(int));

    cudaMemcpy(d_N, N, width * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, M, MASK_WIDTH * sizeof(int), cudaMemcpyHostToDevice);

    convolution1D<<<(width + 255) / 256, 256>>>(d_N, d_M, d_P, width);

    cudaMemcpy(P, d_P, width * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Resultant Array: ");
    for (int i = 0; i < width; i++)
        printf("%d ", P[i]);
    
    printf("\n");

    cudaFree(d_N); cudaFree(d_M); cudaFree(d_P);
    return 0;
}
