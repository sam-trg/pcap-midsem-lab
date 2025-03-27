#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size, M;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data[100], local_data[100];
    float local_avg, total_avg = 0;

    if (rank == 0) {
        printf("Enter %d values: ", size * 2); 
        for (int i = 0; i < size * 2; i++) {
            scanf("%d", &data[i]);
        }
    }

    MPI_Scatter(data, 2, MPI_INT, local_data, 2, MPI_INT, 0, MPI_COMM_WORLD);

    local_avg = (local_data[0] + local_data[1]) / 2.0;

    MPI_Reduce(&local_avg, &total_avg, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total average: %.2f\n", total_avg / size);
    }

    MPI_Finalize();
    return 0;
}
