#include "types.h"
#include "stat.h"
#include "user.h"

// Modified function for xv6 to avoid user input
int main() {
    // Matrix for storing Process Id, Burst Time, Average Waiting Time & Average Turn Around Time.
    int A[100][4];
    int i, j, n = 4, total = 0, index, temp;
    float avg_wt, avg_tat;

    // Hardcoded Burst Times for the processes
    int burstTimes[4] = {6, 8, 7, 3}; // Example burst times

    // Setting process ids and burst times
    for (i = 0; i < n; i++) {
        A[i][0] = i + 1;    // Process ID
        A[i][1] = burstTimes[i]; // Burst Time
    }

    // Sorting processes according to their Burst Time
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++) {
            if (A[j][1] < A[index][1]) {
                index = j;
            }
        }
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;

        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }

    // Calculate Waiting Time for each process
    A[0][2] = 0;
    for (i = 1; i < n; i++) {
        A[i][2] = 0;
        for (j = 0; j < i; j++) {
            A[i][2] += A[j][1];
        }
        total += A[i][2];
    }
    avg_wt = (float)total / n;
    total = 0;

    // Calculate Turnaround Time and print the results
    printf(1, "P\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2];
        total += A[i][3];
        printf(1, "P%d\t%d\t%d\t%d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
    }
    avg_tat = (float)total / n;

    printf(1, "Average Waiting Time= %d.%d\n", (int)avg_wt, (int)((avg_wt - (int)avg_wt) * 100));
    printf(1, "Average Turnaround Time= %d.%d\n", (int)avg_tat, (int)((avg_tat - (int)avg_tat) * 100));

    exit();
}
