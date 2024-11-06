// process2.c
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
    char *myfifo1 = "/tmp/myfifo1"; // FIFO for receiving input from Process 1
    char *myfifo2 = "/tmp/myfifo2"; // FIFO for sending result to Process 1

    // Creating the FIFOs if they do not exist
    mkfifo(myfifo1, 0666);
    mkfifo(myfifo2, 0666);

    char str1[N], str2[N];
    while (1) {
        // Open FIFO 1 for read only (to receive sentence from Process 1)
        fd1 = open(myfifo1, O_RDONLY);
        read(fd1, str1, N);
        close(fd1);

        // Print the received sentence
        printf("User1: %s\n", str1);

        // Counting characters, words, and lines
        int characters = 0, words = 0, lines = 0;
        int inWord = 0;

        for (int i = 0; str1[i] != '\0'; i++) {
            characters++;
            if (str1[i] == ' ' || str1[i] == '\t' || str1[i] == '\n') {
                if (inWord) {
                    words++;
                    inWord = 0;
                }
                if (str1[i] == '\n') {
                    lines++;
                }
            } else {
                inWord = 1;
            }
        }

        if (inWord) {
            words++;
        }

        // Add 1 line if the last sentence did not end with a newline
        if (str1[strlen(str1) - 1] != '\n') {
            lines++;
        }

        // Format the result
        sprintf(str2, "Characters: %d\nWords: %d\nLines: %d\n", characters, words, lines);

        // Write the result to a text file
        FILE *file = fopen("output.txt", "w");
        if (file) {
            fprintf(file, "Characters: %d\nWords: %d\nLines: %d\n", characters, words, lines);
            fclose(file);
        }

        // Open FIFO 2 for write only (to send the result back to Process 1)
        fd2 = open(myfifo2, O_WRONLY);
        write(fd2, str2, strlen(str2) + 1);
        close(fd2);
    }

    return 0;
}
