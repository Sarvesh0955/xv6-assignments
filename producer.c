#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFFER_SIZE 5
#define PRODUCER_COUNT 3
#define CONSUMER_COUNT 3

struct bounded_buffer {
    int buffer[BUFFER_SIZE];
    int in;   
    int out;  
    int count; 
};

struct bounded_buffer *buf;

int main() {
    int i, pid;
    int empty_sem = 0;  
    int full_sem = 1;   
    int mutex_sem = 2;  
    int print_sem = 3;  

    buf = (struct bounded_buffer *)malloc(sizeof(struct bounded_buffer));
    buf->in = 0;
    buf->out = 0;
    buf->count = 0;

    sem_init(empty_sem, BUFFER_SIZE); 
    sem_init(full_sem, 0);             
    sem_init(mutex_sem, 1);            
    sem_init(print_sem, 1);            
    for (i = 0; i < PRODUCER_COUNT; i++) {
        if ((pid = fork()) == 0) {
            for (int j = 0; j < 5; j++) {
                sem_down(empty_sem);   
                sem_down(mutex_sem);   
                buf->buffer[buf->in] = j + 1; 
                buf->in = (buf->in + 1) % BUFFER_SIZE;
                buf->count++;

                sem_up(mutex_sem);     
                sem_up(full_sem);      

                sem_down(print_sem);    
                printf(1, "Producer %d produced %d\n", i + 1, j + 1);
                sem_up(print_sem);      

                sleep(100);              
            }
            exit();
        }
    }
    for (i = 0; i < CONSUMER_COUNT; i++) {
        if ((pid = fork()) == 0) {
            for (int j = 0; j < 5; j++) {
                sem_down(full_sem);    
                sem_down(mutex_sem);   

                int item = buf->buffer[buf->out];
                buf->out = (buf->out + 1) % BUFFER_SIZE;
                buf->count--;

                sem_up(mutex_sem);      
                sem_up(empty_sem);      
                sem_down(print_sem);    
                printf(1, "Consumer %d consumed %d\n", i + 1, item);
                sem_up(print_sem);      

                sleep(100);              
            }
            exit();
        }
    }
    for (i = 0; i < PRODUCER_COUNT + CONSUMER_COUNT; i++) {
        wait();
    }
    free(buf);
    exit();
}
