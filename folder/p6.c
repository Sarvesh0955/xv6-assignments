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

    if (pid == 0) {  // Child process
        close(pipe_fd[0]);  // Close unused read end
        char message[] = "Hello from child process!\n";
        write(pipe_fd[1], message, strlen(message));  // Write message to pipe
        close(pipe_fd[1]);  // Close the write end after use
        exit(0);
    } else {  // Parent process
        close(pipe_fd[1]);  // Close unused write end
        read(pipe_fd[0], buffer, sizeof(buffer));  // Read message from pipe
        printf("Parent received: %s", buffer);  // Print the message
        close(pipe_fd[0]);  // Close the read end after use
        wait(NULL);  // Wait for child process to finish
    }

    return 0;
}
