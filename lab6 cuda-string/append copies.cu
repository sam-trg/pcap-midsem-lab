#include <stdio.h>
#include <cuda.h>

__global__ void createStringT(char *Sin, char *T, int N) {
    int idx = threadIdx.x;
    for (int i = 0; i < N; i++) {
        T[idx * N + i] = Sin[idx];
    }
}

int main() {
    const char Sin[] = "Hai";
    const int N = 3;
    char T[10] = "";

    char *d_Sin, *d_T;
    cudaMalloc(&d_Sin, sizeof(Sin));
    cudaMalloc(&d_T, sizeof(T));

    cudaMemcpy(d_Sin, Sin, sizeof(Sin), cudaMemcpyHostToDevice);

    createStringT<<<1, 3>>>(d_Sin, d_T, N);

    cudaMemcpy(T, d_T, sizeof(T), cudaMemcpyDeviceToHost);

    printf("Output String T: %s\n", T);

    cudaFree(d_Sin);
    cudaFree(d_T);

    return 0;
}
