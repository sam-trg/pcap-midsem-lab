#include <stdio.h>
#include <mpi.h>
#include <stdbool.h>

int isPrime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0) {
            printf("Please run the program with 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    int start = (rank == 0) ? 1 : 51;
    int end = (rank == 0) ? 50 : 100;

    printf("Process %d primes: ", rank);
    for (int i = start; i <= end; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
