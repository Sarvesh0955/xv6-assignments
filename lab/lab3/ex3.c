#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int main() {
    char buffer[BUFFER_SIZE];
    int file_fd = open("example.txt", O_RDONLY);
    if (file_fd < 0) {
        perror("open failed");
        exit(1);
    }
    ssize_t bytes_read = read(file_fd, buffer, BUFFER_SIZE);
    if (bytes_read < 0) {
        perror("read failed");
        close(file_fd);
        exit(1);
    }
    printf("Read %ld bytes from the file: %.*s\n", bytes_read, (int)bytes_read, buffer);
    close(file_fd);
    return 0;
}
