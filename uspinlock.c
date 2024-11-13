/*----------xv6 sync lab----------*/
#include "types.h"
#include "x86.h"
#include "uspinlock.h"

#define NLOCK 10
struct uspinlock {
  uint locked; // 0 if free, 1 if locked
  char *name;  // Name of lock for debugging
};

struct uspinlock uspinlocks[NLOCK]; // Array of spinlocks

int
uspinlock_init(void)
{
  for (int i = 0; i < NLOCK; i++) {
    uspinlocks[i].locked = 0; // All locks are initially free
    uspinlocks[i].name = "uspinlock";
  }
  return 0;
}

int
uspinlock_acquire(int index)
{
  if (index < 0 || index >= NLOCK)
    return -1;

  // Spin until the lock is acquired
  while (xchg(&uspinlocks[index].locked, 1) != 0)
    ;

  return 0;
}

int
uspinlock_release(int index)
{
  if (index < 0 || index >= NLOCK)
    return -1;

  uspinlocks[index].locked = 0;  // Release lock
  return 0;
}

int
uspinlock_holding(int index)
{
  if (index < 0 || index >= NLOCK)
    return -1;

  return uspinlocks[index].locked != 0;
}
