#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int a = 10, b = 5; // Sample values

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Addition: %d + %d = %d\n", a, b, a + b);
    } else if (rank == 1) {
        printf("Subtraction: %d - %d = %d\n", a, b, a - b);
    } else if (rank == 2) {
        printf("Multiplication: %d * %d = %d\n", a, b, a * b);
    } else if (rank == 3) {
        if (b != 0)
            printf("Division: %d / %d = %.2f\n", a, b, (float)a / b);
        else
            printf("Division by zero is undefined.\n");
    }

    MPI_Finalize();
    return 0;
}
