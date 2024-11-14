#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];
    char *filename = "textfile.txt";
    int file;

    if (pipe(pipefd) == -1) {
        error("pipe");
    }

    pid = fork();

    if (pid == -1) {
        error("fork");
    } else if (pid == 0) {
        close(pipefd[0]);
        file = open(filename, O_RDONLY);
        if (file == -1) {
            error("open");
        }
        ssize_t bytes_read = read(file, buffer, BUFFER_SIZE - 1);
        if (bytes_read == -1) {
            error("read");
        }
        buffer[bytes_read] = '\0';  
        close(file);
        write(pipefd[1], buffer, bytes_read + 1);
        close(pipefd[1]);
        char *args[] = {"/bin/ls", "-l", NULL};  
        execv(args[0], args);
        error("execv");
    } else {
        close(pipefd[1]);
        wait(NULL);
        ssize_t bytes_read = read(pipefd[0], buffer, BUFFER_SIZE);
        if (bytes_read == -1) {
            error("read from pipe");
        }
        buffer[bytes_read] = '\0';  
        printf("Data received from child process:\n%s\n", buffer);
        close(pipefd[0]);
    }

    return 0;
}
