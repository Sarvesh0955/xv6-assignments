#include "types.h"
#include "stat.h"
#include "user.h"

int main(){
    printf(1,"callling my syscall\n");
    printf(1,"%d",mysyscall());
    exit();
}