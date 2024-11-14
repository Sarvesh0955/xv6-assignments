#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define BLOCK_SIZE 1024  

void print_last_n_lines(const char *filename, int num_lines) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Error getting file size");
        close(fd);
        exit(EXIT_FAILURE);
    }
    off_t file_size = st.st_size;
    off_t offset = file_size;  
    int lines_found = 0;
    char buffer[BLOCK_SIZE];
    char *buf_ptr;
    ssize_t bytes_read;  
    int total_lines_to_print = num_lines; 
    char *output_buffer = (char *)malloc(file_size + 1);
    if (!output_buffer) {
        perror("Memory allocation error");
        close(fd);
        exit(EXIT_FAILURE);
    }
    output_buffer[0] = '\0';  
    while (offset > 0 && lines_found < num_lines) {
        ssize_t bytes_to_read = (offset < BLOCK_SIZE) ? offset : BLOCK_SIZE;
        offset -= bytes_to_read;
        if (lseek(fd, offset, SEEK_SET) == -1) {
            perror("Error seeking in file");
            close(fd);
            exit(EXIT_FAILURE);
        }
        bytes_read = read(fd, buffer, bytes_to_read);
        if (bytes_read == -1) {
            perror("Error reading file");
            close(fd);
            exit(EXIT_FAILURE);
        }
        for (buf_ptr = buffer + bytes_read - 1; buf_ptr >= buffer; --buf_ptr) {
            if (*buf_ptr == '\n') {
                lines_found++;
                if (lines_found > num_lines) {
                    break;
                }
            }
        }
        strncat(output_buffer, buffer, bytes_read);
    }
    char *start = output_buffer + strlen(output_buffer);
    int current_line = 0;
    while (start >= output_buffer && current_line < num_lines) {
        if (*start == '\n') {
            current_line++;
        }
        start--;
    }
    printf("%s", start + 2);  
    free(output_buffer);
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s -n <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int num_lines = atoi(argv[1] + 1);  
    const char *filename = argv[2];
    if (num_lines <= 0) {
        fprintf(stderr, "Number of lines should be greater than 0\n");
        exit(EXIT_FAILURE);
    }
    print_last_n_lines(filename, num_lines);
    return 0;
}
