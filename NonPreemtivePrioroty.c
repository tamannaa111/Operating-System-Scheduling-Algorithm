#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
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
    int isCompleted[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i;
        printf("Enter Arrival Time, Burst Time, and Priority for Process P%d: ", i);
        scanf("%d%d%d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        isCompleted[i] = 0; // Initially, no process is completed
    }

    sortByArrival(processes, n);

    int completed = 0, currentTime = 0;
    float totalWaitingTime = 0, totalTurnAroundTime = 0;

    while (completed < n) {
        int highestPriority = -1;
        int minPriority = 1e9;

        // Find the process with the highest priority
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime) {
                if (processes[i].priority < minPriority) {
                    minPriority = processes[i].priority;
                    highestPriority = i;
                }
                if (processes[i].priority == minPriority) {
                    // Tie-breaker: choose the process with earlier arrival time
                    if (processes[i].arrivalTime < processes[highestPriority].arrivalTime) {
                        highestPriority = i;
                    }
                }
            }
        }

        if (highestPriority == -1) {
            currentTime++; // No process is ready, increment time
            continue;
        }

        // Execute the selected process
        struct Process *currentProcess = &processes[highestPriority];
        currentTime += currentProcess->burstTime;
        currentProcess->completionTime = currentTime;
        currentProcess->turnAroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
        currentProcess->waitingTime = currentProcess->turnAroundTime - currentProcess->burstTime;

        totalWaitingTime += currentProcess->waitingTime;
        totalTurnAroundTime += currentProcess->turnAroundTime;

        isCompleted[highestPriority] = 1; // Mark the process as completed
        completed++;
    }

    // Output Results
    printf("\nPROCESS\tARRIVAL TIME\tBURST TIME\tPRIORITY\tWAITING TIME\tTURNAROUND TIME\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].priority,
               processes[i].waitingTime,
               processes[i].turnAroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);

    return 0;
}

