//server side: writing to shared memory
// gcc client and server, run both
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHM_SIZE 1024  // Shared memory size

int main() 
{ 
    // Generate a unique key using ftok() (use a valid file path and a unique id)
    key_t key = ftok(".", 65); 
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create a shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); 
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach to the shared memory
    char *str = (char*) shmat(shmid, NULL, 0); 
    if ((long)str == -1) {
        perror("shmat failed");
        exit(1);
    }

    // Input data from the user
    printf("Write Data: ");
    fgets(str, SHM_SIZE, stdin);  // Use fgets instead of gets() for safety

    printf("Data written in memory: %s\n", str);

    // Detach from shared memory
    if (shmdt(str) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    // Keep the server process running to allow clients to read
    // Optionally, clean up shared memory here if server terminates:
    // shmctl(shmid, IPC_RMID, NULL);

    return 0; 
}
