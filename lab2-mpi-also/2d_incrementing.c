#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size, value;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter a value: ");
        scanf("%d", &value);
        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
        printf("Final value after incrementing: %d\n", value);
    } else {
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        value++;
        int nextRank = (rank == size - 1) ? 0 : rank + 1;
        MPI_Send(&value, 1, MPI_INT, nextRank, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
