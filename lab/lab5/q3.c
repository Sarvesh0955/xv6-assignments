#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFER_SIZE 5

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;  
    int out; 
} bounded_buffer_t;

bounded_buffer_t *buffer;
sem_t *empty;
sem_t *full;
sem_t *mutex;

void *producer(void *arg);
void *consumer(void *arg);
void cleanup();

int main() {
    int shm_fd = shm_open("/bounded_buffer", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(bounded_buffer_t));
    buffer = mmap(0, sizeof(bounded_buffer_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    buffer->in = 0;
    buffer->out = 0;

    empty = sem_open("/empty", O_CREAT, 0666, BUFFER_SIZE);
    full = sem_open("/full", O_CREAT, 0666, 0);
    mutex = sem_open("/mutex", O_CREAT, 0666, 1);

    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            producer(NULL);
            exit(0);
        }
        if (fork() == 0) {
            consumer(NULL);
            exit(0);
        }
    }

    for (int i = 0; i < 6; i++) {
        wait(NULL);
    }

    cleanup();

    return 0;
}

void *producer(void *arg) {
    for (int i = 0; i < 5; i++) {
        sleep(1); 

        sem_wait(empty); 
        sem_wait(mutex); 

       
        buffer->buffer[buffer->in] = rand() % 100; 
        printf("Produced: %d\n", buffer->buffer[buffer->in]);
        buffer->in = (buffer->in + 1) % BUFFER_SIZE;

        sem_post(mutex);
        sem_post(full);   
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 5; i++) {
        sleep(1); 

        sem_wait(full);  
        sem_wait(mutex);

        
        int item = buffer->buffer[buffer->out];
        printf("Consumed: %d\n", item);
        buffer->out = (buffer->out + 1) % BUFFER_SIZE;

        sem_post(mutex);
        sem_post(empty);  
    }
    return NULL;
}

void cleanup() {
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    sem_unlink("/empty");
    sem_unlink("/full");
    sem_unlink("/mutex");
    munmap(buffer, sizeof(bounded_buffer_t));
    shm_unlink("/bounded_buffer");
}
