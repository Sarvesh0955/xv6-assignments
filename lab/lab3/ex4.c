#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char message[] = "Hello, this is a test message!\n";
    write(STDOUT_FILENO, message, sizeof(message) - 1); 
    return 0;
}
