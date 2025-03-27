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
    int rank, size, number, result;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int values[size];
        printf("Enter %d values: ", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &values[i]);
        }
        for (int i = 1; i < size; i++) {
            MPI_Send(&values[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        result = factorial(values[0]);
    } else {
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        result = factorial(number);
    }

    int total_sum = 0;
    MPI_Reduce(&result, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total sum of factorials: %d\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}
