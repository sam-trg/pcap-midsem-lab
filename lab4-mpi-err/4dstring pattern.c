#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank, size;
    char input[100], local_char, result[100], *gathered_data = NULL;
    int recv_counts[100], displs[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter a string of length %d: ", size);
        fflush(stdout);
        scanf("%s", input);
    }

    MPI_Scatter(input, 1, MPI_CHAR, &local_char, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    int len = rank + 1;
    for (int i = 0; i < len; i++) {
        result[i] = local_char;
    }
    result[len] = '\0';

    MPI_Gather(&len, 1, MPI_INT, recv_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        displs[0] = 0;
        for (int i = 1; i < size; i++) {
            displs[i] = displs[i - 1] + recv_counts[i - 1];
        }
        gathered_data = (char*)malloc(displs[size - 1] + recv_counts[size - 1] + 1);
    }

    MPI_Gatherv(result, len, MPI_CHAR, gathered_data, recv_counts, displs, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        gathered_data[displs[size - 1] + recv_counts[size - 1]] = '\0';
        printf("Output: %s\n", gathered_data);
        free(gathered_data);
    }

    MPI_Finalize();
    return 0;
}
