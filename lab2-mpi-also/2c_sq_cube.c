#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int array[100], value;
    char buffer[1000];
    MPI_Status status;
    MPI_Buffer_attach(buffer, 1000);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter %d elements: ", size);
        for (int i = 0; i < size; i++)
            scanf("%d", &array[i]);

        for (int i = 1; i < size; i++)
            MPI_Bsend(&array[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        if (rank % 2 == 0)
            printf("Process %d squared value: %d\n", rank, value * value);
        else
            printf("Process %d cubed value: %d\n", rank, value * value * value);
    }

    MPI_Finalize();
    return 0;
}
