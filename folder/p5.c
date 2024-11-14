#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process
        // Replace the child process image with a new program
        char *args[] = {"./p4.c", "-l", NULL};  // Example program: ls -l
        execv("/bin/ls", args);

        // If execv fails
        perror("execv failed");
        exit(1);
    } else {  // Parent process
        wait(NULL);  // Wait for child process to finish
        printf("Child process completed.\n");
    }

    return 0;
}
