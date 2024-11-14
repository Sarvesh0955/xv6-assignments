#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        printf("Child process (PID: %d) is running\n", getpid());
        sleep(2);  
        printf("Child process is exiting\n");
        exit(42);  
    } else {
        printf("Parent process (PID: %d) is waiting for child to terminate\n", getpid());
        pid_t terminated_pid = wait(&status);
        if (terminated_pid == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status)) {
            printf("Child process (PID: %d) terminated with exit status: %d\n", terminated_pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process (PID: %d) was terminated by signal: %d\n", terminated_pid, WTERMSIG(status));
        }
        printf("Parent process is exiting\n");
    }
    return 0;
}
