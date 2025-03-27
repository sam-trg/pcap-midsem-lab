#include <stdio.h>
#include <mpi.h>

int reverseDigits(int num) {
    int reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

int main(int argc, char* argv[]) {
    int rank, size;
    int input_array[9] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    int output_array[9];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 9) {
        if (rank == 0) {
            printf("Please run the program with 9 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    output_array[rank] = reverseDigits(input_array[rank]);

    // Collect results from all processes
    MPI_Gather(&output_array[rank], 1, MPI_INT, output_array, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Output array: ");
        for (int i = 0; i < 9; i++) {
            printf("%d ", output_array[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
