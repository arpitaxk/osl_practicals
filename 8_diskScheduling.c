#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function Prototypes
int SSTF();
int SCAN();
int CLOOK();

int main() {
    int ch, YN = 1, i;
    do {
        printf("\n\n\t*********** MENU ***********");
        printf("\n\n\t1:SSTF\n\n\t2:SCAN\n\n\t3:CLOOK\n\n\t4:EXIT");
        printf("\n\n\tEnter your choice: ");

        if (scanf("%d", &ch) != 1) {
            printf("Invalid input! Please enter a valid number.\n");
            while(getchar() != '\n');  // clear the input buffer
            continue;
        }

        switch (ch) {
            case 1:
                SSTF();
                break;
            case 2:
                SCAN();
                break;
            case 3:
                CLOOK();
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }

        printf("\n\n\tDo you want to continue? If YES, press 1; if NO, press 0: ");

        if (scanf("%d", &YN) != 1) {
            printf("Invalid input! Please enter a valid number.\n");
            while(getchar() != '\n');  // clear the input buffer
            continue;
        }
    } while (YN == 1);

    return 0;
}

// SSTF Algorithm
int SSTF() {
    int RQ[100], i, n, TotalHeadMovement = 0, initial, count = 0;
    printf("Enter the number of Requests: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input! Please enter a valid number.\n");
        return 0;
    }

    printf("Enter the Requests sequence: ");
    for (i = 0; i < n; i++) {
        if (scanf("%d", &RQ[i]) != 1) {
            printf("Invalid input! Please enter a valid number.\n");
            return 0;
        }
    }

    printf("Enter initial head position: ");
    if (scanf("%d", &initial) != 1) {
        printf("Invalid input! Please enter a valid number.\n");
        return 0;
    }

    while (count != n) {
        int min = 1000, d, index;
        for (i = 0; i < n; i++) {
            d = abs(RQ[i] - initial);
            if (min > d) {
                min = d;
                index = i;
            }
        }
        TotalHeadMovement += min;
        initial = RQ[index];
        RQ[index] = 1000;
        count++;
    }
    printf("Total head movement is %d\n", TotalHeadMovement);
    return 0;
}

// SCAN Algorithm
int SCAN() {
    int RQ[100], i, j, n, TotalHeadMovement = 0, initial, size, move;
    printf("Enter the number of Requests: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input! Please enter a valid number.\n");
        return 0;
    }

    printf("Enter the Requests sequence: ");
    for (i = 0; i < n; i++) {
        if (scanf("%d", &RQ[i]) != 1) {
            printf("Invalid input! Please enter a valid number.\n");
            return 0;
        }
    }

    printf("Enter initial head position: ");
    if (scanf("%d", &initial) != 1) {
        printf("Invalid input! Please enter a valid number.\n");
        return 0;
    }

    printf("Enter total disk size: ");
    if (scanf("%d", &size) != 1) {
        printf("Invalid input! Please enter a valid number.\n");
        return 0;
    }

    printf("Enter the head movement direction for high (1) and for low (0): ");
    if (scanf("%d", &move) != 1) {
        printf("Invalid input! Please enter a valid number.\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    int index;
    for (i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }

    if (move == 1) {
        for (i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        TotalHeadMovement += abs(size - RQ[i - 1] - 1);
        initial = size - 1;
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    } else {
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        TotalHeadMovement += abs(RQ[i + 1] - 0);
        initial = 0;
        for (i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    printf("Total head movement is %d\n", TotalHeadMovement);
    return 0;
}

// C-LOOK Algorithm
int CLOOK() {
    int RQ[100], i, j, n, TotalHeadMovement = 0, initial, size, move;
    printf("Enter the number of Requests: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input! Please enter a valid number.\n");
        return 0;
    }

    printf("Enter the Requests sequence: ");
    for (i = 0; i < n; i++) {
        if (scanf("%d", &RQ[i]) != 1) {
            printf("Invalid input! Please enter a valid number.\n");
            return 0;
        }
    }

    printf("Enter initial head position: ");
    if (scanf("%d", &initial) != 1) {
        printf("Invalid input! Please enter a valid number.\n");
        return 0;
    }

    printf("Enter total disk size: ");
    if (scanf("%d", &size) != 1) {
        printf("Invalid input! Please enter a valid number.\n");
        return 0;
    }

    printf("Enter the head movement direction for high (1) and for low (0): ");
    if (scanf("%d", &move) != 1) {
        printf("Invalid input! Please enter a valid number.\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    int index;
    for (i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }

    if (move == 1) {
        for (i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        for (i = 0; i < index; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    } else {
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        for (i = n - 1; i >= index; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    printf("Total head movement is %d\n", TotalHeadMovement);
    return 0;
}
