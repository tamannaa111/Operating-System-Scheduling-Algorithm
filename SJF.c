#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
};

void sortByArrival(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    int isCompleted[n]; // Array to track completed processes
    for (int i = 0; i < n; i++) {
        processes[i].id = i;
        printf("Enter Arrival Time and Burst Time for Process P%d: ", i);
        scanf("%d%d", &processes[i].arrivalTime, &processes[i].burstTime);
        isCompleted[i] = 0; // Initially, no process is completed
    }

    sortByArrival(processes, n);

    int currentTime = 0;
    int completed = 0;
    float totalWaitingTime = 0, totalTurnAroundTime = 0;

    while (completed < n) {
        int shortest = -1;
        int minBurstTime = 100;

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime < minBurstTime) {
                    minBurstTime = processes[i].burstTime;
                    shortest = i;
                }
                if (processes[i].burstTime == minBurstTime) {
                    // Tie-breaker: choose the one with earlier arrival time
                    if (processes[i].arrivalTime < processes[shortest].arrivalTime) {
                        shortest = i;
                    }
                }
            }
        }

        if (shortest == -1) {
            currentTime++; // No process is ready, increment time
        } else {
            currentTime += processes[shortest].burstTime;
            processes[shortest].completionTime = currentTime;
            processes[shortest].turnAroundTime = processes[shortest].completionTime - processes[shortest].arrivalTime;
            processes[shortest].waitingTime = processes[shortest].turnAroundTime - processes[shortest].burstTime;

            totalWaitingTime += processes[shortest].waitingTime;
            totalTurnAroundTime += processes[shortest].turnAroundTime;

            isCompleted[shortest] = 1; // Mark the process as completed
            completed++;
        }
    }

    // Output
    printf("\nPROCESS\tARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].waitingTime,
               processes[i].turnAroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);

    return 0;
}
