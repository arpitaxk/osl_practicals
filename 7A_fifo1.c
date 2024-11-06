// process1.c

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define N 100

int main() {
    int fd1, fd2;

    // FIFO file paths
    char *myfifo1 = "/tmp/myfifo1"; // FIFO for sending input to Process 2
    char *myfifo2 = "/tmp/myfifo2"; // FIFO for receiving result from Process 2

    // Creating the FIFOs if they do not exist
    mkfifo(myfifo1, 0666);
    mkfifo(myfifo2, 0666);

    char arr1[N], arr2[N];
    while (1) {
        // Open FIFO for write only (to send data to Process 2)
        fd1 = open(myfifo1, O_WRONLY);

        // Take an input sentence from the user
        printf("\nEnter Sentence: ");
        fgets(arr2, N, stdin);

        // Write the sentence to FIFO 1
        write(fd1, arr2, strlen(arr2) + 1);
        close(fd1);

        // Open FIFO 2 for read only (to receive processed data from Process 2)
        fd2 = open(myfifo2, O_RDONLY);

        // Read the processed result (character, word, line count)
        read(fd2, arr1, sizeof(arr1));

        // Print the processed result
        printf("Processed Output:\n%s", arr1);
        close(fd2);
    }

    return 0;
}
// gcc 7A_fifo1.c -o 7A_fifo1
// gcc 7A_fifo2.c -o 7A_fifo2
// ./7A_fifo2 & to run in bg
// ./7A_fifo1 