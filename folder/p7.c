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

    if (pid == 0) {  // Child process
        close(pipe_fd[0]);  // Close unused read end

        // Open the file and read its contents
        int file_fd = open("input.txt", O_RDONLY);
        if (file_fd < 0) {
            perror("open failed");
            exit(1);
        }

        ssize_t bytes_read;
        while ((bytes_read = read(file_fd, buffer, BUFFER_SIZE)) > 0) {
            write(pipe_fd[1], buffer, bytes_read);  // Send data to the pipe
        }

        close(file_fd);
        close(pipe_fd[1]);  // Close write end of the pipe
        exit(0);
    } else {  // Parent process
        close(pipe_fd[1]);  // Close unused write end

        // Read from the pipe and write to standard output
        ssize_t bytes_read;
        while ((bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE)) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }

        close(pipe_fd[0]);  // Close read end of the pipe
        wait(NULL);  // Wait for child process to finish
    }

    return 0;
}
