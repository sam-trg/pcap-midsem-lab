#include <stdio.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    char str[] = "HELLO";

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank < 5) {
        if (isupper(str[rank])) {
            str[rank] = tolower(str[rank]);
        } else {
            str[rank] = toupper(str[rank]);
        }
        printf("Process %d toggled character to '%c'\n", rank, str[rank]);
    }

    MPI_Finalize();
    return 0;
}
