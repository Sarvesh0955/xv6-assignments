#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid;
    char buffer[100];
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        exit(1);
    }
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {  
        close(pipe_fd[0]);  
        char message[] = "Hello from child process!\n";
        write(pipe_fd[1], message, strlen(message));  
        close(pipe_fd[1]);  
        exit(0);
    } else {  
        close(pipe_fd[1]);  
        read(pipe_fd[0], buffer, sizeof(buffer));  
        printf("Parent received: %s", buffer);  
        close(pipe_fd[0]);  
        wait(NULL);  
    }
    return 0;
}
