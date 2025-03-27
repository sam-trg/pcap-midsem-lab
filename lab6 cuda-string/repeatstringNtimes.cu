#include <stdio.h>
#include <cuda.h>

__global__ void repeatString(char *Sin, char *Sout, int len, int N) {
    int idx = threadIdx.x;
    for (int i = 0; i < N; i++) {
        Sout[idx * N + i] = Sin[idx];
    }
}

int main() {
    const char Sin[] = "Hello";
    const int N = 3;
    char Sout[16] = "";

    char *d_Sin, *d_Sout;
    cudaMalloc(&d_Sin, sizeof(Sin));
    cudaMalloc(&d_Sout, sizeof(Sout));

    cudaMemcpy(d_Sin, Sin, sizeof(Sin), cudaMemcpyHostToDevice);

    repeatString<<<1, 5>>>(d_Sin, d_Sout, 5, N);

    cudaMemcpy(Sout, d_Sout, sizeof(Sout), cudaMemcpyDeviceToHost);

    printf("Repeated String Sout: %s\n", Sout);

    cudaFree(d_Sin);
    cudaFree(d_Sout);

    return 0;
}
