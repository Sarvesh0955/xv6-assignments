#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int status;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process
        // Replace the child process image with a new program
        char *args[] = {"q3", "-l", NULL};  // Example program: ls -l
        execv("q3", args);

        // If execv fails
        perror("execv failed");
        exit(1);
    } else {  // Parent process
        wait(NULL);
        printf("Child process completed.\n");
    }

    return 0;
}
