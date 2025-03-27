#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int rank, size;
    char S1[100], S2[100], result[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter string S1: ");
        scanf("%s", S1);
        printf("Enter string S2: ");
        scanf("%s", S2);
    }

    int chunk_size = strlen(S1) / size;
    char part1[100], part2[100];

    MPI_Scatter(S1, chunk_size, MPI_CHAR, part1, chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(S2, chunk_size, MPI_CHAR, part2, chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk_size; i++) {
        result[i * 2] = part1[i];
        result[i * 2 + 1] = part2[i];
    }

    MPI_Gather(result, chunk_size * 2, MPI_CHAR, result, chunk_size * 2, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resultant String: %s\n", result);
    }

    MPI_Finalize();
    return 0;
}
