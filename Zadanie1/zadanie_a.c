#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main () {

printf(" UID = %d\n GID = %d\n PID = %d\n PPID = %d\n PGID = %d\n", getuid(), getgid(), getpid(), getppid(), getpgid(0));

    return 0;
}