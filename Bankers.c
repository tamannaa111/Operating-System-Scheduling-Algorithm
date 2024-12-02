#include <stdio.h>

// Function to calculate the Need Matrix
void calculateNeed(int need[][10], int max[][10], int alloc[][10], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

// Function to check if a process can execute
int canExecute(int process, int need[][10], int avail[], int m) {
    for (int j = 0; j < m; j++) {
        if (need[process][j] > avail[j]) {
            return 0; // Cannot execute
        }
    }
    return 1; // Can execute
}

// Function to find the Safe Sequence using the Banker's Algorithm
int findSafeSequence(int n, int m, int alloc[][10], int max[][10], int avail[]) {
    int f[n], safeSequence[n], ind = 0;
    int need[10][10];

    // Initialize the finish array (0: not finished, 1: finished)
    for (int i = 0; i < n; i++) {
        f[i] = 0;
    }

    // Calculate the Need Matrix
    calculateNeed(need, max, alloc, n, m);

    // Attempt to find a safe sequence
    int count = 0;
    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (f[i] == 0 && canExecute(i, need, avail, m)) {
                // Process can execute; add to safe sequence
                safeSequence[ind++] = i;

                // Update available resources
                for (int j = 0; j < m; j++) {
                    avail[j] += alloc[i][j];
                }

                // Mark process as finished
                f[i] = 1;
                found = 1;
                count++;
                break; // Move to the next iteration
            }
        }

        // If no process could execute in this round, the system is unsafe
        if (!found) {
            printf("The system is not in a safe state.\n");
            return 0; // Unsafe
        }
    }

    // Print the Safe Sequence
    printf("The system is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < n - 1; i++) {
        printf("P%d -> ", safeSequence[i]);
    }
    printf("P%d\n", safeSequence[n - 1]);

    return 1; // Safe
}

int main() {
    int n, m;

    // Input the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[10][10], max[10][10], avail[10];

    // Input the available resources
    printf("Enter the available instances of each resource:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Input the Allocation Matrix
    printf("Enter the Allocation Matrix (resources currently allocated to each process):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input the Maximum Demand Matrix
    printf("Enter the Maximum Demand Matrix (maximum resources each process may need):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Run the Banker's Algorithm
    findSafeSequence(n, m, alloc, max, avail);

    return 0;
}
