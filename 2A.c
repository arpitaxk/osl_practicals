#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

#define Max_Size 20

// Function prototypes for sorting algorithms
void mergesort(int array[Max_Size], int left, int right);
void merge(int array[Max_Size], int left, int mid, int right);
void quicksort(int array[Max_Size], int left, int right);
int partition(int array[Max_Size], int left, int right);

int main() {
    int i, mergesort_size, mergesort_array[Max_Size];
    int quicksort_size, quicksort_array[Max_Size];

    // Create a child process using fork()
    pid_t processID;

    // Input for mergesort array
    printf("Enter the number of elements for mergesort: \n");
    scanf("%d", &mergesort_size);

    printf("Enter the elements for mergesort: \n");
    for(i = 0; i < mergesort_size; i++) {
        scanf("%d", &mergesort_array[i]);
    }

    // Input for quicksort array
    printf("Enter the number of elements for quicksort: \n");
    scanf("%d", &quicksort_size);

    printf("Enter the elements for quicksort: \n");
    for(i = 0; i < quicksort_size; i++) {
        scanf("%d", &quicksort_array[i]);
    }

    // If we are in the child process
  processID = fork();
    if(processID == 0) {
        // Child process information
        printf("I am the child process\n");
        printf("My ID is %d & my parent's ID is %d\n", getpid(), getppid());
        sleep(3);  // Simulate some processing delay

        // Perform mergesort in child process
        printf("Child process is executing mergesort...\n");
        mergesort(mergesort_array, 0, mergesort_size - 1);

        // Output sorted array
        printf("After performing mergesort: \n");
        for(i = 0; i < mergesort_size; i++) {
            printf("%d\t", mergesort_array[i]);
        }
        printf("\n");

        printf("Child process has completed execution.\n");
    }

    // If we are in the parent process
    else {
        // Parent process information
        printf("I am the parent process (ID: %d). Sorting the array with quicksort.\n", getpid());

        // Perform quicksort in parent process
        quicksort(quicksort_array, 0, quicksort_size - 1);

        // Output sorted array
        printf("After performing quicksort: \n");
        for(i = 0; i < quicksort_size; i++) {
            printf("%d\t", quicksort_array[i]);
        }
        printf("\n");

        // Wait for the child process to complete, NUll says that you don't need to collect the exit status of child, it can proceed once the child is completed
        wait(NULL);

        // Print completion message
        printf("Child process has completed. Parent is exiting.\n");
    }

    return 0;
}

// Mergesort function that recursively divides the array into halves
void mergesort(int array[Max_Size], int left, int right) {
    if(left < right) {
        // Find the midpoint of the array
        int mid = (left + right) / 2;

        // Recursively sort the left half
        mergesort(array, left, mid);

        // Recursively sort the right half
        mergesort(array, mid + 1, right);

        // Merge the two sorted halves
        merge(array, left, mid, right);
    }
}

// Merge function that combines two sorted halves into a single sorted array
void merge(int array[Max_Size], int left, int mid, int right) {
    int temp[Max_Size];
    int i = left, j = mid + 1, k = 0;

    // Merge the two halves into temp[]
    while(i <= mid && j <= right) {
        if(array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }

    // Copy any remaining elements from the left half
    while(i <= mid) {
        temp[k++] = array[i++];
    }

    // Copy any remaining elements from the right half
    while(j <= right) {
        temp[k++] = array[j++];
    }

    // Copy the sorted elements back into the original array
    // Notice that this loop will properly copy the sorted temp[] array back into array[]
    for(i = left, k = 0; i <= right; i++, k++) {
        array[i] = temp[k];
    }
}


// Partition function used in quicksort to rearrange the elements
int partition(int array[Max_Size], int left, int right) {
    int pivot = array[left];  // Pivot element is the first element in the array
    int start = left + 1;
    int end = right;

    while(start < end) {
        // Move 'start' index to the right until we find an element greater than the pivot
        while(start <= right && array[start] <= pivot) {
            start++;
        }

        // Move 'end' index to the left until we find an element smaller than the pivot
        while(array[end] > pivot) {
            end--;
        }

        // If 'start' is less than 'end', swap the elements at start and end
        if(start < end) {
            int temp = array[start];
            array[start] = array[end];
            array[end] = temp;
        }
    }

    // Swap the pivot with the element at the 'end' index
    int temp = array[left];
    array[left] = array[end];
    array[end] = temp;

    return end;  // Return the pivot index
}

// Quicksort function that recursively sorts the array using the partition function
void quicksort(int array[Max_Size], int left, int right) {
    if(left < right) {
        // Partition the array and get the pivot index
        int pivot_index = partition(array, left, right);

        // Recursively sort the left and right subarrays
        quicksort(array, left, pivot_index - 1);
        quicksort(array, pivot_index + 1, right);
    }
}
