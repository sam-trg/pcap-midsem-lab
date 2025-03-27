#include <stdio.h>
#include <cuda.h>

__global__ void convertToOctal(int *input, int *output, int N) {
    int idx = threadIdx.x;
    if (idx < N) {
        int num = input[idx];
        int octal = 0, place = 1;
        while (num > 0) {
            octal += (num % 8) * place;
            num /= 8;
            place *= 10;
        }
        output[idx] = octal;
    }
}

int main() {
    const int N = 5;
    int input[N] = {10, 20, 30, 40, 50};
    int output[N];

    int *d_input, *d_output;
    cudaMalloc(&d_input, N * sizeof(int));
    cudaMalloc(&d_output, N * sizeof(int));

    cudaMemcpy(d_input, input, N * sizeof(int), cudaMemcpyHostToDevice);

    convertToOctal<<<1, N>>>(d_input, d_output, N);

    cudaMemcpy(output, d_output, N * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Octal values: ");
    for (int i = 0; i < N; i++)
        printf("%d ", output[i]);

    printf("\n");
    
    cudaFree(d_input); cudaFree(d_output);
    return 0;
}
