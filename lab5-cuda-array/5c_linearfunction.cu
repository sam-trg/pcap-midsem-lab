#include <stdio.h>
#include <cuda.h>

__global__ void linearAlgebra(float *x, float *y, float alpha, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N)
        y[idx] = alpha * x[idx] + y[idx];
}

int main() {
    const int N = 10;
    float x[N], y[N];
    float alpha = 2.0f;

    for (int i = 0; i < N; i++) {
        x[i] = i * 1.0f;
        y[i] = i * 0.5f;
    }

    float *d_x, *d_y;
    cudaMalloc((void**)&d_x, N * sizeof(float));
    cudaMalloc((void**)&d_y, N * sizeof(float));

    cudaMemcpy(d_x, x, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, N * sizeof(float), cudaMemcpyHostToDevice);

    linearAlgebra<<<1, N>>>(d_x, d_y, alpha, N);

    cudaMemcpy(y, d_y, N * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Resultant y values: ");
    for (int i = 0; i < N; i++) {
        printf("%f ", y[i]);
    }
    printf("\n");
    cudaFree(d_x); cudaFree(d_y);
    return 0;
}
