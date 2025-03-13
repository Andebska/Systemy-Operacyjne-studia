#include "sem_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <time.h>



const char *sem_name = "/my_semaphore";
sem_t *sem = NULL;


void clean();
void sig_handler(int sig);

int main(int argc, char *argv[]) {

if (argc != 2) {
        fprintf(stderr, "Bledna ilosc argumentow\n");
        fprintf(stderr, "Uruchom program w taki sposob: %s liczba_sekcji_krytycznych\n", argv[0]);
        exit(1);
}

int num_sections = atoi(argv[1]);

sem = open_sem(sem_name);
assert(sem != NULL && "Blad przy tworzeniu semafora");

if (signal(SIGINT, sig_handler) == SIG_ERR) {
perror("signal error \n");
exit(2);
}


do {
	FILE *file = fopen("numer.txt", "r+");
	if(file == NULL) {
	fprintf(stderr, "fopen (numer.txt) error \n");
	exit(3);
	}
	int num;
	if(fscanf(file, "%d", &num) != 1) {
	perror("fscanf error");
	exit(3);
	}
	rewind(file);                       //powrot do poczatku pliku
	printf("Numer.txt: %d\n", num);
	num++;
	printf("Numer zostal zwiekszony o 1: %d\n", num);
	fprintf(file, "%d", num);

	srand(time(NULL));           
	int sleep_time = rand() % 4 + 1;     //losowy czas od 1 do 4 sekund
	sleep(sleep_time);
	printf("Zapisywanie do pliku \n");
	if(fclose(file) != 0) {
	perror("fclose (numer.txt) error \n");
	exit(3);
	}

	
		sleep(2);

	num_sections--;
} while(num_sections > 0);

   sem_unlink(sem_name);
    return 0;
}

void clean() {
if(sem != NULL) {        
	if(close_sem(sem) == 0) {
	fprintf(stderr, "Blad przy zamykaniu semafora w pliku %s oraz linii: %d \n", __FILE__, __LINE__);
	exit(2);
	}
if(open_sem(sem_name) != 0) {	   //sprawdzamy czy semafor istnieje
	if(remove_sem(sem_name) == 0) {
	fprintf(stderr, "Blad przy usuwaniu semafora w pliku %s oraz linii: %d \n", __FILE__, __LINE__);
	exit(2);
	}
}
printf("Semafor zostal zamkniety i usuniety \n");
}
}


void sig_handler(int sig) {
printf("Zostal dostarczony sygnal SIGINT \n");
clean();
exit(0);
}






