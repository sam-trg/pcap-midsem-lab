#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    const int x = 2; // Change 'x' as needed

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Process %d: pow(%d, %d) = %.0f\n", rank, x, rank, pow(x, rank));

    MPI_Finalize();
    return 0;
}

