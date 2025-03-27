#include <stdio.h>
#include <mpi.h>

int factorial(int n) {
    int fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main(int argc, char* argv[]) {
    int rank, size, local_factorial, total_sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each rank computes its own factorial
    local_factorial = factorial(rank + 1);

    // Calculate cumulative sum using MPI_Scan
    MPI_Scan(&local_factorial, &total_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if (rank == size - 1) {
        printf("Sum of factorials = %d\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}
