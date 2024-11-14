#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int pipe_fd[2];
    pid_t pid;
    char buffer[100];
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        exit(1);
    }
    pid = fork();
   
    if (pid == 0) {  
        close(pipe_fd[0]);  
        char buffer1[100];
        int file_fd = open("example.txt", O_RDONLY);
        
        ssize_t bytes_read = read(file_fd, buffer1, 100);
        write(pipe_fd[1], buffer1, strlen(buffer1));  
        close(pipe_fd[1]);  

        char *args[] = {"./ex1", "-l", NULL};  
        execv("./ex1", args);
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
