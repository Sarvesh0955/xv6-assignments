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
    if (pid == 0) {  
        char *args[] = {"./ex1", "-l", NULL};  
        execv("./ex1", args);
        perror("execv failed");
        exit(1);
    } else {  
        wait(NULL);  
        printf("Child process completed.\n");
    }
    return 0;
}
