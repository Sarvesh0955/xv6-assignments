#include "types.h"
#include "stat.h"
#include "user.h"

#define MAX_PROCESSES 10

struct Process {
    char id[5];
    int at;      // Arrival time
    int bt;      // Burst time
    int ct;      // Completion time
    int wt;      // Waiting time
    int tat;     // Turnaround time
    int rem;     // Remaining time
};

// Round Robin scheduling function with Gantt Chart
void roundRobin(struct Process ps[], int n, int q) {
    int t = 0, done = 0;
    double totalWt = 0, totalTat = 0;

    // Initialize remaining time and completion time
    for (int i = 0; i < n; i++) {
        ps[i].rem = ps[i].bt;
        ps[i].ct = 0;
    }

    // Display Gantt Chart Header
    printf(1, "\nGantt Chart:\n");

    // Round Robin Scheduling with Gantt Chart
    while (done < n) {
        int idle = 1;

        for (int i = 0; i < n; i++) {
            if (ps[i].rem > 0 && ps[i].at <= t) {
                idle = 0;
                int slice = (q < ps[i].rem) ? q : ps[i].rem;
                printf(1, "| %s ", ps[i].id);  // Display process in Gantt Chart
                t += slice;
                ps[i].rem -= slice;

                if (ps[i].rem == 0) {  // Process completed
                    ps[i].ct = t;             // Completion time
                    ps[i].tat = ps[i].ct - ps[i].at; // Turnaround time
                    ps[i].wt = ps[i].tat - ps[i].bt; // Waiting time
                    totalWt += ps[i].wt;
                    totalTat += ps[i].tat;
                    done++;
                }
            }
        }
        if (idle) {
            printf(1, "| idle ");
            t++;
        }
    }
    printf(1, "|\n");  // End Gantt Chart

    // Display Results
    printf(1, "\nID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf(1, "%s\t%d\t%d\t%d\t%d\t%d\n", ps[i].id, ps[i].at, ps[i].bt, ps[i].ct, ps[i].wt, ps[i].tat);
    }

    printf(1, "\nAverage WT: %d\n", (int)(totalWt / n));
    printf(1, "Average TAT: %d\n", (int)(totalTat / n));
}

int main() {
    // Hardcoded input values
    int n = 3;  // Number of processes
    struct Process ps[MAX_PROCESSES] = {
        {"P1", 0, 10, 0, 0, 0, 0},
        {"P2", 2, 5, 0, 0, 0, 0},
        {"P3", 4, 8, 0, 0, 0, 0}
    };
    int q = 3;  // Time quantum

    // Execute Round Robin scheduling
    roundRobin(ps, n, q);
    exit();
}
