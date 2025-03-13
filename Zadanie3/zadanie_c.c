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

pid_t pid = fork();
switch(pid) {
case -1:
perror("Fork error ");
exit(EXIT_FAILURE);

case 0:
setpgid(0,0);
execlp("./zadanie_c_p", "zadanie_c_p", argv[1], argv[2], NULL);
perror("execlp error");
_exit(2);

default: 
sleep(1);     //czekanie na utworzenie nowej grupy procesow
pid_t pgid;
pgid = getpgid(pid);

if (kill(-pgid, 0) == -1) {
	if (errno == ESRCH) {
	perror("Grupa procesow potomnych nie istnieje\n");
	exit(3);
	}
	else {
	perror("Kill error \n");
	exit(2);
	}
}

if(kill(-pgid, sig) == -1){
perror("Kill error \n");
exit(3);
}
else {
printf("Do grupy procesow potomnych zostal wyslany sygnal: %d\n", sig);
}

int status;
if(wait(&status) != -1) {
	printf("PID pierwszego procesu potomnego: %d\n", pid);
	printf("Status zakonczenia procesu potomnego pierwszego procesu macierzystego: %d\n", status);
}
else {
	perror("Wait error \n");
	exit(2);
} 

   
break;
};


return 0;
}

