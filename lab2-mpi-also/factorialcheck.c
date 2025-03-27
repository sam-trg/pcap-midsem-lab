#include <stdio.h>
#include <mpi.h>

int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

int main(int argc, char* argv[]) {
    int rank, size, n, localSum = 0, totalSum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the value of N: ");
        scanf("%d", &n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 1; i <= rank + 1; i++)
        localSum += i;

    totalSum = factorial(localSum);

    MPI_Reduce(&totalSum, &totalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("Final Result: %d\n", totalSum);

    MPI_Finalize();
    return 0;
}
