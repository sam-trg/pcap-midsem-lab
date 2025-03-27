#include <stdio.h>
#include <cuda.h>

__global__ void oddEvenSort(int *arr, int N) {
    int idx = threadIdx.x;
    for (int i = 0; i < N; i++) {
        if ((i % 2 == 0 && idx % 2 == 0) || (i % 2 != 0 && idx % 2 != 0)) {
            if (idx < N - 1 && arr[idx] > arr[idx + 1]) {
                int temp = arr[idx];
                arr[idx] = arr[idx + 1];
                arr[idx + 1] = temp;
            }
        }
        __syncthreads();
    }
}

int main() {
    const int N = 10;
    int arr[N] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int *d_arr;

    cudaMalloc(&d_arr, N * sizeof(int));
    cudaMemcpy(d_arr, arr, N * sizeof(int), cudaMemcpyHostToDevice);

    oddEvenSort<<<1, N>>>(d_arr, N);

    cudaMemcpy(arr, d_arr, N * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted Array: ");
    for (int i = 0; i < N; i++)
        printf("%d ", arr[i]);

    printf("\n");
    
    cudaFree(d_arr);
    return 0;
}
