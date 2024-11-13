#include "types.h"
#include "stat.h"
#include "user.h"

#define BUFFER_SIZE 100

// Helper function to read an integer from the user
int read_int() {
    char buffer[BUFFER_SIZE];
    int n = read(0, buffer, BUFFER_SIZE);
    buffer[n - 1] = '\0'; // Replace newline character with null terminator
    return atoi(buffer);
}

// Helper function to read a string from the user
void read_string(char *str) {
    int n = read(0, str, BUFFER_SIZE);
    str[n - 1] = '\0'; // Replace newline character with null terminator
}

int main() {
    int n;
    printf(1, "Enter number of processes: ");
    n = read_int();

    char q[n][20]; // Array to store process names (max length 19 chars)
    printf(1, "Processes: ");
    for(int i = 0; i < n; i++) {
        read_string(q[i]);
    }

    int arrival[n];
    printf(1, "Arrival time: ");
    for(int i = 0; i < n; i++) {
        arrival[i] = read_int();
    }

    int burst[n];
    printf(1, "Burst time: ");
    for(int i = 0; i < n; i++) {
        burst[i] = read_int();
    }

    printf(1, "\nGantt Chart: |");
    for(int i = 0; i < n; i++) {
        printf(1, "%s|", q[i]);
    }
    printf(1, "\n");

    int t = arrival[0];
    int total_wait = 0;
    int total_turn = 0;
    int wait[n];
    int turn[n];

    for(int i = 0; i < n; i++) {
        wait[i] = (t > arrival[i]) ? t - arrival[i] : 0;
        t += burst[i];
        total_wait += wait[i];
        turn[i] = t - arrival[i];
        total_turn += turn[i];
    }

    double avg_wait = (double) total_wait / n;
    double avg_turn = (double) total_turn / n;

    printf(1, "Waiting Time: ");
    for(int i = 0; i < n; i++) {
        printf(1, "%s=%d,", q[i], wait[i]);
    }
    printf(1, "\n");

    printf(1, "Turnaround Time: ");
    for(int i = 0; i < n; i++) {
        printf(1, "%s=%d,", q[i], turn[i]);
    }
    printf(1, "\n");

    printf(1, "Average Waiting Time: %d.%d\n", (int)avg_wait, (int)((avg_wait - (int)avg_wait) * 100));
    printf(1, "Average Turnaround Time: %d.%d\n", (int)avg_turn, (int)((avg_turn - (int)avg_turn) * 100));

    exit();
}
