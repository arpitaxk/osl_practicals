#include <stdio.h>

int main() {
    int n, m, i, j, k;

    // Input the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];
    int f[n], ans[n], ind = 0;

    // Input the Allocation Matrix
    printf("\nEnter the Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input the MAX Matrix
    printf("\nEnter the MAX Matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input the Available Resources
    printf("\nEnter the Available Resources: ");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Initialize the "need" matrix (Need = MAX - Allocation)
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize the finished flag array and the answer array
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }

    int y = 0;
    for (k = 0; k < n; k++) {
        // Try to find a process that can finish
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                // If the process can finish, add it to the answer sequence
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    // Check if all processes could finish
    int flag = 1;
    for (i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("\nThe system is not in a safe state.\n");
            break;
        }
    }

    // If all processes finished, print the safe sequence
    if (flag == 1) {
        printf("\nThe system is in a safe state.\n");
        printf("Following is the SAFE Sequence: \n");
        for (i = 0; i < n - 1; i++) {
            printf("P%d -> ", ans[i]);
        }
        printf("P%d", ans[n - 1]);
    }

    return 0;
}
// Enter the number of processes: 5
// Enter the number of resources: 3

// Enter the Allocation Matrix:
// Process P0: 0 1 0
// Process P1: 2 0 0
// Process P2: 3 0 2
// Process P3: 2 1 1
// Process P4: 0 0 2

// Enter the MAX Matrix:
// Process P0: 7 5 3
// Process P1: 3 2 2
// Process P2: 9 0 2
// Process P3: 2 2 2
// Process P4: 4 3 3

// Enter the Available Resources: 3 3 2

// The system is in a safe state.
// Following is the SAFE Sequence: 
// P1 -> P3 -> P4 -> P0 -> P2
