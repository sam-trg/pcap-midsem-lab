#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char ch) {
    char vowels[] = "AEIOUaeiou";
    return strchr(vowels, ch) != NULL;
}

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char str[100], part[100];
    int count = 0, total_count = 0;

    if (rank == 0) {
        printf("Enter a string: ");
        scanf("%s", str);
    }

    int chunk_size = strlen(str) / size;
    MPI_Scatter(str, chunk_size, MPI_CHAR, part, chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk_size; i++) {
        if (!is_vowel(part[i]) && isalpha(part[i])) {
            count++;
        }
    }

    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total non-vowels: %d\n", total_count);
    }

    MPI_Finalize();
    return 0;
}
