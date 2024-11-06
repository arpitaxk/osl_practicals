#include <limits.h>
#include <stdio.h>

struct Process {
  int id;             // Process ID
  int burstTime;      // Burst time (total time required)
  int remainingTime;  // Remaining burst time for SJF preemptive
  int arrivalTime;    // Arrival time
  int waitingTime;    // Waiting time
  int turnaroundTime; // Turnaround time
  int completionTime; // Completion time
};

int numProcesses;       // Number of processes
struct Process arr[10]; // Array to store processes (maximum 10)

// Function to calculate waiting time and turnaround time for SJF Preemptive
void calculateTimes() {
  int totalWaitingTime = 0, totalTurnaroundTime = 0;
  int currentTime = 0, completed = 0;

  // Initialize remaining burst time for each process
  for (int i = 0; i < numProcesses; i++) {
    arr[i].remainingTime = arr[i].burstTime;
    arr[i].completionTime = -1; // Mark as uncompleted initially
  }

  // SJF Preemptive Scheduling
  while (completed < numProcesses) {
    int minRemainingTime = INT_MAX;
    int spi = -1; // Shortest Process Index

    // Find the process with the shortest remaining burst time that has arrived
    for (int i = 0; i < numProcesses; i++) {
      if (arr[i].arrivalTime <= currentTime && arr[i].remainingTime > 0 &&
          arr[i].remainingTime < minRemainingTime) {
        minRemainingTime = arr[i].remainingTime;
        spi = i;
      }
    }

    // If no process has arrived yet, just increment the time
    if (spi == -1) {
      currentTime++;
      continue;
    }

    // Execute the process (decrease its remaining burst time)
    arr[spi].remainingTime--;

    // If the process has finished, calculate its waiting and turnaround times
    if (arr[spi].remainingTime == 0) {
      completed++;

      // Completion time is currentTime + 1 because we just processed the last
      // time unit
      arr[spi].completionTime = currentTime + 1;

      // Calculate turnaround time: Completion time - Arrival time
      arr[spi].turnaroundTime = arr[spi].completionTime - arr[spi].arrivalTime;

      // Calculate waiting time: Turnaround time - Burst time
      arr[spi].waitingTime = arr[spi].turnaroundTime - arr[spi].burstTime;

      // Accumulate total waiting and turnaround times
      totalWaitingTime += arr[spi].waitingTime;
      totalTurnaroundTime += arr[spi].turnaroundTime;
    }

    currentTime++; // Move time forward by 1 unit
  }

  // Print the process table with better formatting
  printf("\n%-12s%-12s%-15s%-15s%-18s\n", "Process ID", "Burst Time",
         "Arrival Time", "Waiting Time", "Turnaround Time");
  for (int i = 0; i < numProcesses; i++) {
    printf("%-12d%-12d%-15d%-15d%-18d\n", arr[i].id, arr[i].burstTime,
           arr[i].arrivalTime, arr[i].waitingTime, arr[i].turnaroundTime);
  }

  // Print averages
  printf("\nAverage waiting time: %.2f",
         (float)totalWaitingTime / numProcesses);
  printf("\nAverage turnaround time: %.2f",
         (float)totalTurnaroundTime / numProcesses);
}

// Function to input process details
void inputProcesses() {
  printf("\nEnter the number of processes: ");
  scanf("%d", &numProcesses);

  // Input burst times and arrival times
  for (int i = 0; i < numProcesses; i++) {
    arr[i].id = i + 1; // Automatically assign process IDs starting from 1
    printf("\nEnter burst time for Process %d: ", i + 1);
    scanf("%d", &arr[i].burstTime);
    arr[i].remainingTime =
        arr[i].burstTime; // Set remaining time initially equal to burst time
    printf("Enter arrival time for Process %d: ", i + 1);
    scanf("%d", &arr[i].arrivalTime);
  }
}

// Main function
int main() {
  inputProcesses(); // Get input from user
  calculateTimes(); // Calculate waiting and turnaround times
  return 0;
}
// bt at 62 25 81 30 44 tat: 9.2 wt: 4.6
//31 14 42 06 23 tat:7 wt: 3.8
