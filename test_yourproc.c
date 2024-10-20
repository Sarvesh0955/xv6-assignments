#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int pid = yourproc();  
    if (pid == 0) {
        printf(1, "Child process created using customfork, PID: %d\n", getpid());
        wait();
    } else if (pid > 0) {
        
    } else {
        printf(1, "customfork failed!\n");
    }
    exit();
}
