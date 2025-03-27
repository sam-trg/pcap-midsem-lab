#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

void toggleString(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper(str[i])) 
            str[i] = tolower(str[i]);
        else if (islower(str[i]))
            str[i] = toupper(str[i]);
    }
}

int main(int argc, char* argv[]) {
    int rank;
    char word[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        strcpy(word, "HelloWorld");
        printf("Process 0 sending word: %s\n", word);
        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(word, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received toggled word: %s\n", word);
    } 
    else if (rank == 1) {
        MPI_Recv(word, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        toggleString(word);

        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
