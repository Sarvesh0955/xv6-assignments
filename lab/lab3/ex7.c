#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    int pipe_fd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];
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
        int file_fd = open("input.txt", O_RDONLY);
        if (file_fd < 0) {
            perror("open failed");
            exit(1);
        }
        ssize_t bytes_read;
        while ((bytes_read = read(file_fd, buffer, BUFFER_SIZE)) > 0) {
            write(pipe_fd[1], buffer, bytes_read);  
        }
        close(file_fd);
        close(pipe_fd[1]);  
        exit(0);
    } else {  
        close(pipe_fd[1]);  
        ssize_t bytes_read;
        while ((bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE)) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
        close(pipe_fd[0]);  
        wait(NULL);  
    }
    return 0;
}
