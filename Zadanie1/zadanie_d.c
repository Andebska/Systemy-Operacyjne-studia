#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main () {

printf("Identyfikatory procesu macierzystego: ");
printf(" UID = %d GID = %d PID = %d PPID = %d PGID = %d\n", getuid(), getgid(), getpid(), getppid(), getpgid(0));

for(int i=0; i<3; i++) {

switch(fork()) {
    case -1:
    perror("Fork error ");
    exit(EXIT_FAILURE);
    break;

    case 0:
    printf("Identyfikatory procesu potomnego: ");
    printf(" UID = %d GID = %d PID = %d PPID = %d PGID = %d\n", getuid(), getgid(), getpid(), getppid(), getpgid(0));
    sleep(3);
    break;

    default: 
    sleep(5);
    break;
}

}

    return 0;
}