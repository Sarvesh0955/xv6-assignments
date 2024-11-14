#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char message[] = "I was created in step 3 and now i am being used in extra ques 1 which is executed by child process after giving data to parent process\n";
    write(STDOUT_FILENO, message, sizeof(message) - 1);  // Write to standard output

    return 0;
}
