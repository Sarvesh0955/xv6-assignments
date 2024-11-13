/*----------xv6 sync lab----------*/
#include "types.h"
#include "x86.h"
#include "defs.h"
#include "semaphore.h"

struct semaphore {
  int value;          // Semaphore value
  struct spinlock lock; // Lock for atomic operations
};

#define MAX_SEMAPHORES 10
struct semaphore sem[MAX_SEMAPHORES]; // Array of semaphores

int
sem_init(int index, int val)
{
  if (index < 0 || index >= MAX_SEMAPHORES)
    return -1;

  initlock(&sem[index].lock, "semaphore lock");
  sem[index].value = val;

  return 0;
}

int
sem_down(int index)
{
  if (index < 0 || index >= MAX_SEMAPHORES)
    return -1;

  acquire(&sem[index].lock);  // Lock before modifying value
  while (sem[index].value <= 0) {
    sleep(&sem[index], &sem[index].lock);  // Sleep if unavailable
  }
  sem[index].value--;  // Decrement after it's confirmed to be non-zero
  release(&sem[index].lock);

  return 0;
}

int
sem_up(int index)
{
  if (index < 0 || index >= MAX_SEMAPHORES)
    return -1;

  acquire(&sem[index].lock); // Lock before modifying value
  sem[index].value++;
  wakeup(&sem[index]);       // Wake up processes waiting on semaphore
  release(&sem[index].lock);

  return 0;
}


/*----------xv6 sync lab end----------*/
