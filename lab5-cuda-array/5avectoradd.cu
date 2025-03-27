#include <stdio.h>
#include <cuda.h>

__global__ void vectorAdd(int *a, int *b, int *c, int N) {
    int idx = threadIdx.x;  // Each thread handles one element
    if (idx < N)
        c[idx] = a[idx] + b[idx];
}

int main() {
    const int N = 10;
    int a[N], b[N], c[N];
    int *d_a, *d_b, *d_c;

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i * 2;
    }

    cudaMalloc((void**)&d_a, N * sizeof(int));
    cudaMalloc((void**)&d_b, N * sizeof(int));
    cudaMalloc((void**)&d_c, N * sizeof(int));

    cudaMemcpy(d_a, a, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N * sizeof(int), cudaMemcpyHostToDevice);

    vectorAdd<<<1, N>>>(d_a, d_b, d_c, N);

    cudaMemcpy(c, d_c, N * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Result: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", c[i]);
    }

    printf("\n");

    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
    return 0;
}
