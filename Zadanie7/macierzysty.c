#include "buffer.h"
#include "sharedLibrary.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


sem_t *prod_sem = NULL;
sem_t *cons_sem = NULL;
SegmentSM *sas = NULL;
int fd_shm = -1;
void clean();
void sig_handler(int sig);

int main() {
	const char *shm_name = "/segment";
	const char *sem_prod_name = "/PROD";
	const char *sem_cons_name = "/CONS";

	int fd_shm = shm_create(shm_name, sizeof(SegmentSM));
	assert(fd_shm != 0 && "Blad przy tworzeniu segmentu pamieci dzielonej. \n");

	prod_sem = create_sem(sem_prod_name, NBUF);
	assert(prod_sem != NULL && "Blad przy tworzeniu semafora producenta\n");
	cons_sem = create_sem(sem_cons_name, 0);
	assert(cons_sem != NULL && "Blad przy tworzeniu semafora konsumenta\n");
	
	if (signal(SIGINT, sig_handler) == SIG_ERR) {
	perror("signal error \n");
	exit(2);
	}

	sas = (SegmentSM *)mapMemory(fd_shm, sizeof(SegmentSM), PROT_READ | PROT_WRITE, MAP_SHARED);        //sas - shared address space
	assert(sas != NULL && "Blad przy odwzorowaniu pamieci dzielonej. \n");
	sas->insert = 0;
	sas->remove = 0;

	pid_t pid;
	for(int i = 0; i<2; ++i) {
	pid = fork();
	if(pid == -1) {
	perror("Fork error \n");
	exit(1);
	} 
	else if(pid == 0) {
		if(i == 0) {
		execlp("./producent", "./producent", NULL);
		perror("Execlp (producent) error \n");
		exit(1);
		} 
		else {
		execlp("./konsument", "./konsument", NULL);
		perror("Execlp (konsument) error \n");
		exit(1);
		}
	}
	}

	for(int i = 0; i < 2; ++i) {
	wait(NULL);
	}

atexit(clean);
return 0;
}


void clean() {
const char *shm_name = "/segment";
const char *sem_prod_name = "/PROD";
const char *sem_cons_name = "/CONS";

if(prod_sem != NULL) {        
	if(close_sem(prod_sem) == 0) {
	fprintf(stderr, "Blad przy zamykaniu semafora producenta w pliku %s oraz linii: %d \n", __FILE__, __LINE__);
	exit(2);
	}
if(open_sem(sem_prod_name) != 0) {	   //sprawdzamy czy semafor istnieje
	if(remove_sem(sem_prod_name) == 0) {
	fprintf(stderr, "Blad przy usuwaniu semafora producenta w pliku %s oraz linii: %d \n", __FILE__, __LINE__);
	exit(2);
	}
}
}
if(cons_sem != NULL) {        
	if(close_sem(cons_sem) == 0) {
	fprintf(stderr, "Blad przy zamykaniu semafora konsumenta w pliku %s oraz linii: %d \n", __FILE__, __LINE__);
	exit(2);
	}
if(open_sem(sem_cons_name) != 0) {	   //sprawdzamy czy semafor istnieje
	if(remove_sem(sem_cons_name) == 0) {
	fprintf(stderr, "Blad przy usuwaniu semafora konsumenta w pliku %s oraz linii: %d \n", __FILE__, __LINE__);
	exit(2);
	}
}
}
printf("Semafory zostaly zamkniete i usuniete \n");


if(unmapMemory(sas, sizeof(SegmentSM)) == 0) {
	fprintf(stderr,"Blad przy usuwaniu odwzorowania pamieci dzielonej w pliku %s oraz linii: %d\n", __FILE__, __LINE__);
	exit(2);
}

if(fd_shm != -1) {                          //sprawdzamy czy istnieje
if(shm_close(fd_shm) == 0){
fprintf(stderr,"Blad przy zamykaniu segmentu pamieci dzielonej w pliku %s oraz linii: %d\n", __FILE__, __LINE__);
	exit(2);
}
}

if(shm_destroy(shm_name) == 0) {
fprintf(stderr,"Blad przy usuwaniu segmentu pamieci dzielonej w pliku %s oraz linii: %d\n", __FILE__, __LINE__);
	exit(2);
}

printf("Obiekt pamieci dzielonej zostal usuniety \n");
}


void sig_handler(int sig) {
printf("Zostal dostarczony sygnal SIGINT \n");
clean();
exit(0);
}


