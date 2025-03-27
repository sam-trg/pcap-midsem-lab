#include <stdio.h>
#include <cuda.h>
#include <string.h>

__global__ void countWord(char *text, char *word, int *count, int textLen, int wordLen) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx <= textLen - wordLen) {
        bool match = true;
        for (int i = 0; i < wordLen; i++) {
            if (text[idx + i] != word[i]) {
                match = false;
                break;
            }
        }
        if (match) {
            atomicAdd(count, 1);
        }
    }
}

int main() {
    const char text[] = "cuda is fast cuda is powerful cuda cuda";
    const char word[] = "cuda";
    int count = 0;

    char *d_text, *d_word;
    int *d_count;

    cudaMalloc(&d_text, sizeof(text));
    cudaMalloc(&d_word, sizeof(word));
    cudaMalloc(&d_count, sizeof(int));

    cudaMemcpy(d_text, text, sizeof(text), cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, word, sizeof(word), cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);

    countWord<<<1, strlen(text)>>>(d_text, d_word, d_count, strlen(text), strlen(word));

    cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    printf("Count of word '%s': %d\n", word, count);

    cudaFree(d_text); cudaFree(d_word); cudaFree(d_count);
    return 0;
}
