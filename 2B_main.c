#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_SIZE 20

// Bubble sort function to sort the array in ascending order
void bubbleSort(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main() {
  int n, i;
  int arr[MAX_SIZE];
  pid_t pid;

  // Input the array size and elements
  printf("Enter the size of the array: ");
  if (scanf("%d", &n) != 1) {
    printf("Error: Invalid input for array size\n");
    return 1; // Exit with error if input is invalid
  }

  printf("Enter the elements of the array: ");
  for (i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      printf("Error: Invalid input for array element %d\n", i + 1);
      return 1; // Exit with error if input is invalid
    }
  }

  // Sort the array in ascending order
  bubbleSort(arr, n);

  // Create a child process
  pid = fork();
  if (pid == 0) {
    // Child process prepares the arguments for execve
    char *args[MAX_SIZE + 2]; // One for program name and one for NULL terminator

    // Build the arguments to pass to the child program (reverse_display)
    for (i = 0; i < n; i++) {
      args[i + 1] = malloc(10 * sizeof(char)); // Allocate space for each integer argument
      sprintf(args[i + 1], "%d", arr[i]); // Convert int to string
    }
    args[n + 1] = NULL; // Null-terminate the array of arguments

    // Execute the new program that prints the array in reverse and performs binary search
    execve("./2B_reverse", args, NULL);

    // If execve fails
    perror("execve failed");
    exit(1);
  } else if (pid > 0) {
    // Parent waits for the child process to complete
    wait(NULL);
    printf("Parent process complete.\n");
  }

  return 0;
}
