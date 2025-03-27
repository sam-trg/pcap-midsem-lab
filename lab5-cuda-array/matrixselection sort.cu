#include <stdio.h>
#include <cuda.h>

__global__ void selectionSort(int *matrix, int N) {
    int row = blockIdx.x;
    for (int i = 0; i < N - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < N; j++) {
            if (matrix[row * N + j] < matrix[row * N + minIdx])
                minIdx = j;
        }
        int temp = matrix[row * N + i];
        matrix[row * N + i] = matrix[row * N + minIdx];
        matrix[row * N + minIdx] = temp;
    }
}

int main() {
    const int N = 4;
    int matrix[N][N] = {{3, 2, 1, 4}, {6, 5, 4, 3}, {9, 8, 7, 6}, {12, 11, 10, 9}};
    int *d_matrix;

    cudaMalloc((void**)&d_matrix, N * N * sizeof(int));
    cudaMemcpy(d_matrix, matrix, N * N * sizeof(int), cudaMemcpyHostToDevice);

    selectionSort<<<N, 1>>>(d_matrix, N);

    cudaMemcpy(matrix, d_matrix, N * N * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }

    cudaFree(d_matrix);
    return 0;
}
