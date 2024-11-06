#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i, n, target, found = 0, index = -1;
    int arr[10]; // Array to store the numbers from the parent program
    int low = 0, high, mid;

    // Check if we have received arguments (the numbers) from the parent process
    if (argc < 2) {
        printf("No arguments passed.\n");
        return 1; // Exit with error if no arguments are passed
    }

    // Convert command-line arguments (sorted array passed from parent) to integers
    for (i = 1; i < argc; i++) {
        arr[i - 1] = atoi(argv[i]); // Convert string arguments to integers
    }
    n = argc - 1; // Number of elements in the array (based on the number of arguments passed)

    // Print the array in reverse order
    printf("Array in reverse order: ");
    for (i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Perform binary search for a target value
    printf("Enter the number to search: ");
    if (scanf("%d", &target) != 1) { // Check if the input is valid
        printf("Error: Invalid input for target number.\n");
        return 1; // Exit with error if the input is invalid
    }

    // Binary search (assuming array is sorted)
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == target) {
            found = 1;
            index = mid; // Store the index where the number is found
            break;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (found) {
        printf("Number %d found at index %d in the sorted array.\n", target, index);
    } else {
        printf("Number %d not found in the array.\n", target);
    }

    return 0;
}
