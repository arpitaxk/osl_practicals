// client side: reading from shared memory
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>
#include <stdlib.h>

#define SHM_SIZE 1024  // Shared memory size

int main() 
{ 
    // Generate a unique key using ftok() (use a valid file path and a unique id)
    key_t key = ftok(".", 65); 
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Access the shared memory segment (it should already exist)
    int shmid = shmget(key, SHM_SIZE, 0666); 
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

    // Print the data read from shared memory
    printf("Data read from memory: %s\n", str);

    // Detach from shared memory
    if (shmdt(str) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    return 0; 
}
