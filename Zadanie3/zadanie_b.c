#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>


int main (int argc, char *argv[]) {

if(argc != 3) {
fprintf(stderr,"Nieprawidlowa ilosc argumentow.\n");
fprintf(stderr, "Uruchom program w taki sposob: %s  [twoj_wybor] [numer_sygnalu_do_wyslania]\n", argv[0]);
fprintf(stderr, "[twoj_wybor] = \n (1) Wykonanie operacji domyslnej\n (2) Ignorowanie sygnalu\n (3) Przechwycenie i wlasna obsluga sygnalu\n");
exit(1);
}

int sig = atoi(argv[2]);
pid_t pid;
int status;

switch(pid = fork()) 
{
case -1:
perror("Fork error \n");
exit(2);

case 0:
execlp("./zadanie_2_a", "zadanie_2_a", argv[1], argv[2], NULL);
perror("execlp error \n");
_exit(2);


default:

sleep(1);
if (kill(pid, 0) == -1) {
	if (errno == ESRCH) {
	printf("Proces nie istnieje\n");
	exit(4);
	}
	else {
	perror("Kill error \n");
	exit(2);
	}
}

kill(pid, sig);

if(wait(&status) != -1) {
printf("PID procesu potomnego: %d\n", pid);
printf("Status zakonczenia procesu potomnego: %d\n", status);
  if(WIFSIGNALED(status)) {
  printf("Proces potomny zakonczony przez sygnal o numerze: %d oraz nazwie: %s \n", WTERMSIG(status), strsignal(WTERMSIG(status)) );
  }
}
else {
perror("Wait error \n");
exit(2);
}  
break;
};

return 0;
}

