#include <stdio.h>

struct Process {
  int id;             // Process ID
  int burstTime;      // Burst Time (total time required by the process)
  int remainingTime;  // Remaining burst time for Round Robin
  int arrivalTime;    // Arrival time of the process
  int waitingTime;    // Waiting time of the process
  int turnaroundTime; // Turnaround time of the process
  int completionTime; // Completion time of the process
};

void roundRobinScheduling(struct Process processes[], int numProcesses,
                          int quantum) {
  int totalWaitingTime = 0, totalTurnaroundTime = 0;
  int currentTime = 0; // Current time in the system
  int completed = 0;   // Number of processes that have completed execution

  // Initialize all processes
  for (int i = 0; i < numProcesses; i++) {
    processes[i].remainingTime = processes[i].burstTime;
    processes[i].waitingTime = 0;
    processes[i].turnaroundTime = 0;
    processes[i].completionTime = -1;
  }

  // Round Robin Scheduling
  while (completed < numProcesses) {
    int allProcessesFinished = 1;

    for (int i = 0; i < numProcesses; i++) {
      if (processes[i].remainingTime > 0) {
        allProcessesFinished = 0;
        if (processes[i].arrivalTime <= currentTime) {
          int timeToExecute = (processes[i].remainingTime > quantum)
                                  ? quantum
                                  : processes[i].remainingTime;

          // Process executes for 'timeToExecute' units
          processes[i].remainingTime -= timeToExecute;
          currentTime += timeToExecute;

          if (processes[i].remainingTime == 0) {
            // Completion time
            processes[i].completionTime = currentTime;

            // Calculate turnaround time and waiting time
            processes[i].turnaroundTime =
                processes[i].completionTime - processes[i].arrivalTime;
            processes[i].waitingTime =
                processes[i].turnaroundTime - processes[i].burstTime;

            totalWaitingTime += processes[i].waitingTime;
            totalTurnaroundTime += processes[i].turnaroundTime;

            completed++;
          }
        }
      }
    }

    // If all processes are finished, break the loop
    if (allProcessesFinished) {
      break;
    }
  }

  // Print the process table with better formatting
  printf("\n%-12s%-12s%-15s%-15s%-18s%-15s\n", "Process ID", "Burst Time",
         "Arrival Time", "Waiting Time", "Turnaround Time", "Completion Time");

  for (int i = 0; i < numProcesses; i++) {
    printf("%-12d%-12d%-15d%-15d%-18d%-15d\n", processes[i].id,
           processes[i].burstTime, processes[i].arrivalTime,
           processes[i].waitingTime, processes[i].turnaroundTime,
           processes[i].completionTime);
  }

  // Print averages
  printf("\nAverage Waiting Time: %.2f",
         (float)totalWaitingTime / numProcesses);
  printf("\nAverage Turnaround Time: %.2f\n",
         (float)totalTurnaroundTime / numProcesses);
}

int main() {
  int numProcesses, quantum;

  // Input the number of processes and quantum time
  printf("Enter the number of processes: ");
  scanf("%d", &numProcesses);

  struct Process processes[numProcesses];

  // Input process burst times and arrival times
  for (int i = 0; i < numProcesses; i++) {
    processes[i].id = i + 1; // Process IDs starting from 1
    printf("Enter burst time for Process %d: ", i + 1);
    scanf("%d", &processes[i].burstTime);
    printf("Enter arrival time for Process %d: ", i + 1);
    scanf("%d", &processes[i].arrivalTime);
  }

  // Input time quantum
  printf("Enter the time quantum: ");
  scanf("%d", &quantum);

  // Call the round-robin scheduling function
  roundRobinScheduling(processes, numProcesses, quantum);

  return 0;
}
// bt 10 5 8 arrival 0 0 0 tat:19.67 wt:12
// bt 5 4 2 1 arrival 0 1 2 4 tat: 7.7 wt: 4.7