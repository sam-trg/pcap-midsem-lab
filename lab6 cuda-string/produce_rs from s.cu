#include <stdio.h>
#include <cuda.h>

__global__ void generateRS(char *S, char *RS, int len) {
    int idx = threadIdx.x;
    RS[2 * idx] = S[idx];
    RS[2 * idx + 1] = S[idx];
}

int main() {
    const char S[] = "PCAP";
    char RS[9] = "";

    char *d_S, *d_RS;
    cudaMalloc(&d_S, sizeof(S));
    cudaMalloc(&d_RS, sizeof(RS));

    cudaMemcpy(d_S, S, sizeof(S), cudaMemcpyHostToDevice);

    generateRS<<<1, 4>>>(d_S, d_RS, 4);

    cudaMemcpy(RS, d_RS, sizeof(RS), cudaMemcpyDeviceToHost);

    printf("Output String RS: %s\n", RS);

    cudaFree(d_S);
    cudaFree(d_RS);

    return 0;
}
