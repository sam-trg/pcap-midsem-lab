#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size, N;
    int data[100], local_data[100], result[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter size N (divisible by number of processes): ");
        scanf("%d", &N);

        printf("Enter %d elements: ", N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &data[i]);
        }
    }

    int chunk_size = N / size;

    MPI_Scatter(data, chunk_size, MPI_INT, local_data, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    int local_even = 0, local_odd = 0;
    for (int i = 0; i < chunk_size; i++) {
        if (local_data[i] % 2 == 0) {
            local_data[i] = 1;
            local_even++;
        } else {
            local_data[i] = 0;
            local_odd++;
        }
    }

    MPI_Gather(local_data, chunk_size, MPI_INT, result, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    int total_even = 0, total_odd = 0;
    MPI_Reduce(&local_even, &total_even, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_odd, &total_odd, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resultant Array: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", result[i]);
        }
        printf("\nEven (Count) = %d\n", total_even);
        printf("Odd (Count) = %d\n", total_odd);
    }

    MPI_Finalize();
    return 0;
}
