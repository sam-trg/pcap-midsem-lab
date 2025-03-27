#include <stdio.h>
#include <math.h>
#include <cuda.h>

__global__ void computeSine(float *angles, float *sines, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N)
        sines[idx] = sinf(angles[idx]);
}

int main() {
    const int N = 10;
    float angles[N], sines[N];
    float *d_angles, *d_sines;

    for (int i = 0; i < N; i++) angles[i] = i * 0.1f;

    cudaMalloc((void**)&d_angles, N * sizeof(float));
    cudaMalloc((void**)&d_sines, N * sizeof(float));

    cudaMemcpy(d_angles, angles, N * sizeof(float), cudaMemcpyHostToDevice);

    computeSine<<<1, N>>>(d_angles, d_sines, N);

    cudaMemcpy(sines, d_sines, N * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Sine values: ");
    for (int i = 0; i < N; i++) {
        printf("%f ", sines[i]);
    }
    printf("\n");
    cudaFree(d_angles); cudaFree(d_sines);
    return 0;
}
