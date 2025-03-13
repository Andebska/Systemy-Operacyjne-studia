#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main (int argn,char *argv[]) {

printf("Identyfikatory procesu macierzystego: ");
printf(" UID = %d GID = %d PID = %d PPID = %d PGID = %d\n", getuid(), getgid(), getpid(), getppid(), getpgid(0));

for(int i=0; i<3; i++) {

switch(fork()) {
    case -1:
    perror("Fork error ");
    exit(EXIT_FAILURE);

    case 0:
    execlp(argv[1], argv[1], NULL);
    perror("execlp error");
    _exit(2);

    default: 
    wait(NULL);
    break;
};


}

    return 0;
}
