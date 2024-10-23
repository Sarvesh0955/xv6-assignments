#include "types.h"
#include "stat.h"
#include "user.h"

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = {0, 1, 2, 3, 4};
int pipes[N][2]; 

void test(int phnum) {
    if (state[phnum] == HUNGRY
        && state[LEFT] != EATING
        && state[RIGHT] != EATING) {
        state[phnum] = EATING;
        printf(1, "Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
        printf(1, "Philosopher %d is Eating\n", phnum + 1);
        write(pipes[phnum][1], "1", 1);  // Send a signal
    }
}

void take_fork(int phnum) {
    state[phnum] = HUNGRY;
    printf(1, "Philosopher %d is Hungry\n", phnum + 1);
    test(phnum);
    char buf[1];
    read(pipes[phnum][0], buf, 1);
}

void put_fork(int phnum) {
    state[phnum] = THINKING;
    printf(1, "Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
    printf(1, "Philosopher %d is thinking\n", phnum + 1);
    test(LEFT);
    test(RIGHT);
}

void philosopher(int phnum) {
    while (1) {
        sleep(1);  
        take_fork(phnum);  
        sleep(2);  
        put_fork(phnum);  
    }
}

int main() {
    int pid, i;
    for (i = 0; i < N; i++) {
        pipe(pipes[i]); 
        state[i] = THINKING; 
        printf(1, "Philosopher %d is thinking\n", i + 1);
    }
    for (i = 0; i < N; i++) {
        pid = fork();
        if (pid == 0) {
            philosopher(i);  
            exit();
        }
    }
    for (i = 0; i < N; i++) {
        wait();
    }
    exit();
}
