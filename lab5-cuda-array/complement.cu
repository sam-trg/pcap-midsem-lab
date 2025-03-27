#include <stdio.h>
#include <cuda.h>

__global__ void onesComplement(int *input, int *output, int N) {
    int idx = threadIdx.x;
    if (idx < N)
        output[idx] = ~input[idx];
}

int main() {
    const int N = 5;
    int input[N] = {0b1010, 0b1100, 0b0011, 0b0101, 0b1001};
    int output[N];

    int *d_input, *d_output;
    cudaMalloc(&d_input, N * sizeof(int));
    cudaMalloc(&d_output, N * sizeof(int));

    cudaMemcpy(d_input, input, N * sizeof(int), cudaMemcpyHostToDevice);

    onesComplement<<<1, N>>>(d_input, d_output, N);

    cudaMemcpy(output, d_output, N * sizeof(int), cudaMemcpyDeviceToHost);

    printf("One's Complement: ");
    for (int i = 0; i < N; i++)
        printf("%d ", output[i]);

    cudaFree(d_input); cudaFree(d_output);
    return 0;
}
