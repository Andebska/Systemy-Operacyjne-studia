#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>



int main() {

    printf("Identyfikatory procesu potomnego: ");
    printf(" UID = %d GID = %d PID = %d PPID = %d PGID = %d\n", getuid(), getgid(), getpid(), getppid(), getpgid(0));

 return 0;
}