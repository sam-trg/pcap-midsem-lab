#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char* argv[]) {
    int rank, size, M;
    int data[100], local_data[100], result[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter value of M: ");
        scanf("%d", &M);

        printf("Enter %d elements: ", size * M);
        for (int i = 0; i < size * M; i++) {
            scanf("%d", &data[i]);
        }
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(data, M, MPI_INT, local_data, M, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < M; i++) {
        result[i] = pow(local_data[i], rank + 2);
    }

    MPI_Gather(result, M, MPI_INT, result, M, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resultant Array: ");
        for (int i = 0; i < size * M; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
