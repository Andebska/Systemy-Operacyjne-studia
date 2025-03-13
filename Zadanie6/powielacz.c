#include "sem_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include <errno.h>


const char *sem_name = "/my_semaphore";
sem_t *sem = NULL;

void clean();

int main(int argc, char *argv[]) {
if (argc != 4) {
	fprintf(stderr, "Bledna ilosc argumentow\n");
        fprintf(stderr, "Uruchom program w taki sposob: %s nazwa_programu liczba_procesów liczba_sekcji_krytycznych\n", argv[0]);
        exit(1);
}

const char *program_name = argv[1];
int num_processes = atoi(argv[2]);
int num_sections = atoi(argv[3]);
sem = create_sem(sem_name, 1);
assert(sem != NULL && "Blad przy tworzeniu semafora");

FILE *file = fopen("numer.txt", "w");
if(file == NULL) {
	fprintf(stderr, "fopen (numer.txt) error \n");
	exit(2);
}

fprintf(file, "0");
if(fclose(file) != 0) {
	fprintf(stderr, "fclose (numer.txt) error \n");
	exit(2);
}

for(int i = 0; i < num_processes; ++i) {
    switch(fork()) {
	case -1:
	  perror("Fork error \n");
	  exit(1);
	case 0:
	  execlp(program_name, program_name, argv[3], NULL);
	  perror("Execlp error \n");
	  exit(1);
	default:
	  break;
	};
}
for(int i = 0; i < num_processes; ++i) {       //czekanie na zakonczenie procesow potomnych
	wait(NULL);
}
printf("Procesy potomne zakonczyly dzialanie \n");

file = fopen("numer.txt", "r");              //sprawdzanie poprawnosci numeru koncowego
if(file == NULL) {
perror("fopen (numer.txt) error \n");
exit(2);
}
int final_num;
if(fscanf(file, "%d", &final_num) != 1) {
perror("fscanf error");
exit(2);
}
fclose(file);
if(final_num == num_processes*num_sections) {
printf("Koncowy numer: %d jest poprawny\n", final_num); 
} else {
printf("Koncowy numer: %d nie jest poprawny\n", final_num);
exit(3);
}

atexit(clean);
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


