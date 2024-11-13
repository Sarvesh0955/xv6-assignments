#include "types.h"
#include "stat.h"
#include "user.h"
#include "semaphore.h"

#define MAX_PHILOSOPHERS 5
int output_lock; 


enum { THINKING, HUNGRY, EATING };
int states[MAX_PHILOSOPHERS];
int philosophers[MAX_PHILOSOPHERS];

int mutex;
int forks[MAX_PHILOSOPHERS];

void test(int philosopher) {
  if (states[philosopher] == HUNGRY &&
      states[(philosopher + MAX_PHILOSOPHERS - 1) % MAX_PHILOSOPHERS] != EATING &&
      states[(philosopher + 1) % MAX_PHILOSOPHERS] != EATING) {
    states[philosopher] = EATING;
    sem_up(forks[philosopher]);
  }
}

void pick_up_forks(int philosopher) {
  sem_down(mutex);                 
  states[philosopher] = HUNGRY;    
  test(philosopher);               
  sem_up(mutex);                   
  sem_down(forks[philosopher]);    
}

void put_down_forks(int philosopher) {
  sem_down(mutex);                 
  states[philosopher] = THINKING;  
  test((philosopher + MAX_PHILOSOPHERS - 1) % MAX_PHILOSOPHERS);
  test((philosopher + 1) % MAX_PHILOSOPHERS);
  sem_up(mutex);
}

void philosopher(int id) {
  while (1) {
    sem_down(output_lock);
    printf(1, "Philosopher %d is thinking\n", id);
    sem_up(output_lock);

    sleep(100);

    sem_down(output_lock);
    printf(1, "Philosopher %d is hungry\n", id);
    sem_up(output_lock);

    pick_up_forks(id);

    sem_down(output_lock);
    printf(1, "Philosopher %d is eating\n", id);
    sem_up(output_lock);

    sleep(200);

    put_down_forks(id);

    sem_down(output_lock);
    printf(1, "Philosopher %d is done eating\n", id);
    sem_up(output_lock);
  }
}

void init_philosophers() {
  mutex = sem_init(0, 1);
  output_lock = sem_init(MAX_PHILOSOPHERS, 1);  
  for (int i = 0; i < MAX_PHILOSOPHERS; i++) {
    forks[i] = sem_init(i + 1, 0);
    states[i] = THINKING;
  }
}

int main(void) {
  init_philosophers();
  for (int i = 0; i < MAX_PHILOSOPHERS; i++) {
    if (fork() == 0) {
      philosopher(i);  
      exit();
    }
  }

  for (int i = 0; i < MAX_PHILOSOPHERS; i++) {
    wait();
  }

  exit();
}
