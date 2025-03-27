#include <stdio.h>
#include <cuda.h>
#include <string.h>

__global__ void reverseWords(char *input, char *output, int wordLength) {
    int idx = threadIdx.x;
    int wordStart = idx * (wordLength + 1); // +1 accounts for spaces

    for (int i = 0; i < wordLength; i++) {
        output[wordStart + i] = input[wordStart + (wordLength - i - 1)];
    }

    // Copy space if it exists
    if (input[wordStart + wordLength] == ' ') {
        output[wordStart + wordLength] = ' ';
    }
}

int main() {
    const char input[] = "cuda fast test word";
    const int wordLength = 4;
    char output[sizeof(input)] = "";

    char *d_input, *d_output;
    cudaMalloc(&d_input, sizeof(input));
    cudaMalloc(&d_output, sizeof(output));

    cudaMemcpy(d_input, input, sizeof(input), cudaMemcpyHostToDevice);

    reverseWords<<<1, 4>>>(d_input, d_output, wordLength);
    cudaDeviceSynchronize();

    cudaMemcpy(output, d_output, sizeof(output), cudaMemcpyDeviceToHost);

    printf("Reversed Words: %s\n", output);

    cudaFree(d_input); 
    cudaFree(d_output);
    return 0;
}
