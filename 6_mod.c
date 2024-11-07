#include<stdio.h>

typedef struct {
    char frames[20][2]; // Renamed data[] to frames[] for better clarity
    int frameCount; // Renamed 'end' to 'frameCount' to better describe its purpose
} FrameQueue;

void addFrame(FrameQueue *q, char page, int position); 
char removeFrame(FrameQueue *q, int position); 
void fifo(char referenceString[], int frameSize, int referenceCount); 
void optimal(char referenceString[], int frameSize, int referenceCount); 
void lru(char referenceString[], int frameSize, int referenceCount); 

void main() { 
    int frameSize, referenceCount, i, choice; 
    char referenceString[50]; 

    printf("Enter the page reference string: "); 
    referenceCount = 0; 

    // Reading the page reference string
    do { 
        scanf("%c", &referenceString[referenceCount]); 
        referenceCount++; 
    } while (referenceString[referenceCount - 1] != '\n'); 

    referenceCount--; // Exclude newline character from the reference string

    // Getting the frame size from the user
    printf("\nEnter the size of the frame: "); 
    scanf("%d", &frameSize); 

    // Display the menu for page replacement algorithms
    do { 
        printf("\nMENU\n====\n1. FIFO\n2. Least Recently Used (LRU)\n3. Optimal\n4. Exit\n\nYour Choice:"); 
        scanf("%d", &choice); 

        switch(choice) { 
            case 1:
                fifo(referenceString, frameSize, referenceCount); 
                break;
            case 2:
                lru(referenceString, frameSize, referenceCount); 
                break; 
            case 3:
                optimal(referenceString, frameSize, referenceCount); 
                break; 
            case 4:
                //exit(0); // Exiting functionality is not needed, loop will end naturally
                break; 
            default:
                printf("\nInvalid choice! Please try again!"); 
                continue; 
        }
    } while (choice != 4); 
}

// Function to add a page to the frame queue
void addFrame(FrameQueue *q, char page, int position) { 
    q->frames[position][0] = page; 
}

// Function to remove a page from the frame queue at a given position
char removeFrame(FrameQueue *q, int position) { 
    char removedPage = q->frames[position][0]; 
    return removedPage; 
}

// FIFO Page Replacement Algorithm
void fifo(char referenceString[], int frameSize, int referenceCount) { 
    int i, j, pageFaults = 0, pageFound, framePointer = -1; 
    FrameQueue q; 
    q.frameCount = 0; 

    printf("\nPage Requested\tFrame contents\t    Page Fault\n==============================================");

    // Loop through each page reference in the reference string
    for (i = 0; i < referenceCount; i++) { 
        printf("\n\n\t%c", referenceString[i]); 
        pageFound = 0; 

        // Check if the page is already in the frame
        for (j = 0; j < q.frameCount; j++) { 
            if (referenceString[i] == q.frames[j][0]) { 
                pageFound = 1; 
                break; 
            } 
        }

        // If the page is not found in the frame, it is a page fault
        if (!pageFound) { 
            pageFaults++; 

            if (q.frameCount < frameSize) {
                // If space is available, add the page to the frame
                addFrame(&q, referenceString[i], q.frameCount); 
                q.frameCount++; 
            } else { 
                // If no space, remove the oldest page (FIFO)
                removeFrame(&q, framePointer); 
                framePointer = (framePointer + 1) % q.frameCount; 
                addFrame(&q, referenceString[i], framePointer); 
            }

            // Print the current frame contents
            printf("\t  ");
            for (j = 0; j < q.frameCount; j++) { 
                printf("%c   ", q.frames[j][0]); 
            }
            printf("\t\tY"); // Indicates a page fault
        } else { 
            // If the page was found in the frame, no page fault
            printf("\t  ");
            for (j = 0; j < q.frameCount; j++) { 
                printf("%c   ", q.frames[j][0]); 
            } 
            printf("\t\tN"); // Indicates no page fault
        }
    }

    printf("\n\n=============================================="); 
    printf("\nTotal no. of Page Faults: %d\n\n", pageFaults); 
}

// Optimal Page Replacement Algorithm
void optimal(char referenceString[], int frameSize, int referenceCount) { 
    int i, j, pageFaults = 0, pageFound, maxDistance, distance[20], pageToReplace; 
    FrameQueue q; 
    q.frameCount = 0; 

    printf("\nPage Requested\tFrame contents\t    Page Fault\n==============================================");

    // Loop through each page reference in the reference string
    for (i = 0; i < referenceCount; i++) { 
        printf("\n\n\t%c", referenceString[i]); 
        pageFound = 0; 

        // Check if the page is already in the frame
        for (j = 0; j < q.frameCount; j++) { 
            if (referenceString[i] == q.frames[j][0]) { 
                pageFound = 1; 
                break; 
            } 
        }

        if (!pageFound) { 
            pageFaults++; 

            if (q.frameCount < frameSize) { 
                addFrame(&q, referenceString[i], q.frameCount); 
                q.frames[q.frameCount][1] = i; // Store the reference index
                q.frameCount++; 
            } else { 
                // Find the page that will be used the furthest in the future
                for (j = 0; j < q.frameCount; j++) {
                    distance[j] = 0;
                }

                for (j = 0; j < q.frameCount; j++) { 
                    for (int k = i + 1; k < referenceCount; k++) {
                        if (referenceString[k] == q.frames[j][0]) { 
                            distance[j] = k - i; 
                            break; 
                        }
                    }

                    if (distance[j] == 0) { 
                        distance[j] = 999; // If the page doesn't appear later
                    }
                }

                // Find the page that has the maximum distance in future (not used soon)
                maxDistance = 0;
                for (j = 0; j < q.frameCount; j++) { 
                    if (distance[j] > maxDistance) { 
                        maxDistance = distance[j]; 
                        pageToReplace = j; 
                    } 
                }

                // Replace the page
                removeFrame(&q, pageToReplace); 
                addFrame(&q, referenceString[i], pageToReplace); 
            }

            // Print the current frame contents
            printf("\t  ");
            for (j = 0; j < q.frameCount; j++) { 
                printf("%c   ", q.frames[j][0]); 
            } 
            printf("\t\tY");
        } else { 
            // If the page was found in the frame, no page fault
            printf("\t  ");
            for (j = 0; j < q.frameCount; j++) { 
                printf("%c   ", q.frames[j][0]); 
            }
            printf("\t\tN");
        }
    }

    printf("\n\n=============================================="); 
    printf("\nTotal no. of Page Faults: %d\n\n", pageFaults); 
}

// Least Recently Used (LRU) Page Replacement Algorithm
void lru(char referenceString[], int frameSize, int referenceCount) { 
    int i, j, pageFaults = 0, pageFound, leastRecentTime, pageToReplace; 
    FrameQueue q; 
    q.frameCount = 0; 

    printf("\nPage Requested\tFrame contents\t    Page Fault\n==============================================");

    // Loop through each page reference in the reference string
    for (i = 0; i < referenceCount; i++) { 
        printf("\n\n\t%c", referenceString[i]); 
        pageFound = 0; 

        // Check if the page is already in the frame
        for (j = 0; j < q.frameCount; j++) { 
            if (referenceString[i] == q.frames[j][0]) { 
                q.frames[j][1] = (i + 1); // Update time of use
                pageFound = 1; 
                break; 
            } 
        }

        if (!pageFound) { 
            pageFaults++; 

            if (q.frameCount < frameSize) { 
                addFrame(&q, referenceString[i], q.frameCount); 
                q.frames[q.frameCount][1] = (i + 1); 
                q.frameCount++; 
            } else { 
                // Find the least recently used page to replace
                leastRecentTime = 999; 
                for (j = 0; j < q.frameCount; j++) { 
                    if (q.frames[j][1] < leastRecentTime) { 
                        leastRecentTime = q.frames[j][1]; 
                        pageToReplace = j; 
                    } 
                }

                // Replace the least recently used page
                removeFrame(&q, pageToReplace); 
                addFrame(&q, referenceString[i], pageToReplace); 
                q.frames[pageToReplace][1] = (i + 1); 
            }

            // Print the current frame contents
            printf("\t  ");
            for (j = 0; j < q.frameCount; j++) { 
                printf("%c   ", q.frames[j][0]); 
            } 
            printf("\t\tY");
        } else { 
            // If the page was found in the frame, no page fault
            printf("\t  ");
            for (j = 0; j < q.frameCount; j++) { 
                printf("%c   ", q.frames[j][0]); 
            } 
            printf("\t\tN");
        }
    }

    printf("\n\n=============================================="); 
    printf("\nTotal no. of Page Faults: %d\n\n", pageFaults); 

    // 3fifo 1, 3, 0, 3, 5, 6, 3 pf:3
// 4optimal 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3 pf:6
// 4lru 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3  pf:6
// 3optimal 5, 0, 1, 0, 2, 3, 0, 2, 4, 3, 3, 2, 0, 2, 1, 2, 7, 0, 1, 1, 0  pf:9
// 3lru  5, 0, 1, 0, 2, 3, 0, 2, 4, 3, 3, 2, 0, 2, 1, 2, 7, 0, 1, 1, 0  pf:12
// 3fifo 5, 0, 1, 0, 2, 3, 0, 2, 4, 3, 3, 2, 0, 2, 1, 2, 7, 0, 1, 1, 0 pf: 11
// 4all 1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6 fifo:14, lru:10, optimal:8

}
