#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

void my_sighandler(int sig) {
printf("Wykonanie przechwycenia i wlasnej obslugi dla sygnalu: %d\n", sig);
}

int main (int argc, char *argv[]) {

if(argc != 3) {
fprintf(stderr,"Nieprawidlowa ilosc argumentow.\n");
fprintf(stderr, "Uruchom program w taki sposob: %s  [twoj_wybor] [numer_sygnalu_do_wyslania]\n", argv[0]);
fprintf(stderr, "[twoj_wybor] = \n (1) Wykonanie operacji domyslnej\n (2) Ignorowanie sygnalu\n (3) Przechwycenie i wlasna obsluga sygnalu\n");
exit(1);
}

int sig = atoi(argv[2]);


if(strcmp(argv[1], "1") == 0) {
	if(signal(sig, SIG_DFL) == SIG_ERR) {
	perror("Wystapil blad przy wykonaniu operacji domyslnej.\n");
	exit(2);
	}
	else {
	printf("Wykonanie operacji domyslnej dla sygnalu: %d\n", sig);
	}
}

else if(strcmp(argv[1], "2") == 0) {
	if(signal(sig, SIG_IGN) == SIG_ERR) {
	perror("Wystapil blad przy ignorowaniu sygnalu.");
	exit(3);
	}
	else {
	printf("Wykonanie ignorowania dla sygnalu: %d\n", sig);
	printf("Uzyj funkcji kill -sig pid do wyslania wybranego sygnalu.\n");
	printf("(Mozesz sprawdzic pid przy pomocy polecenia: ps aux | grep zadanie_a)\n");
	pause();


	}

}

else if(strcmp(argv[1], "3") == 0) {

	if(signal(sig, my_sighandler) == SIG_ERR) {
	perror("Wystapil blad przy przechwyceniu i wlasnej obsludze sygnalu.");
	exit(4);
	}
	else {
	my_sighandler(sig);


	}

}

else {
printf("Wybrano nieprawidlowa cyfre. Mozliwe to: 1/2/3\n");
printf("Uzyj funkcji kill -sig pid do wyslania wybranego sygnalu.\n");
printf("(Mozesz sprawdzic pid przy pomocy polecenia: ps aux | grep zadanie_a)\n");
pause();

}


return 0;
}

