#include "buffer.h"
#include "sharedLibrary.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <assert.h>
#include <string.h>
#include <signal.h>

sem_t *prod_sem = NULL;
sem_t *cons_sem = NULL;
SegmentSM *sas = NULL;
int fd_shm = -1;
void clean();
void sig_handler(int sig);

int main () {

	const char *shm_name = "/segment";
	const char *sem_prod_name = "/PROD";
	const char *sem_cons_name = "/CONS";
	const char *cons_filename = "kons.txt";

	prod_sem = open_sem(sem_prod_name);
	assert(prod_sem != NULL && "Blad przy otwieraniu semafora");
	cons_sem = open_sem(sem_cons_name);
	assert(cons_sem != NULL && "Blad przy otwieraniu semafora");

	int fd_shm = shm_create(shm_name, sizeof(SegmentSM));
	assert(fd_shm != 0 && "Blad przy tworzeniu segmentu pamieci dzielonej. \n");

	sas = (SegmentSM *)mapMemory(fd_shm, sizeof(SegmentSM), PROT_READ | PROT_WRITE, MAP_SHARED);        //sas - shared address space
	assert(sas != NULL && "Blad przy odwzorowaniu pamieci dzielonej. \n");
	sas->insert = 0;
	sas->remove = 0;

	if (signal(SIGINT, sig_handler) == SIG_ERR) {
	perror("signal error \n");
	exit(2);
	}

	FILE *cons_file = fopen(cons_filename, "w");
	if(cons_file == NULL) {
	perror("Fopen (kons.txt) error \n");
	exit(1);
	}

	while(1) {
	
	assert(wait_sem(cons_sem) && "Blad przy opuszczaniu semafora");	

	char consumed_product[NELE];
	strcpy(consumed_product, sas->buffer[sas->remove]);
	sas->remove = (sas->remove + 1) % NBUF;

	int bytes_consumed = strlen(consumed_product);
	fprintf(cons_file, "%s", consumed_product);
	printf("Konsument odczytal %d bajtow danych: %s\n", bytes_consumed, consumed_product);	
	if (sas->count == -1) {
        break; // zakoncz petle gdy bufor jest pusty
        }

	assert(post_sem(prod_sem) && "Blad przy podnoszeniu semafora");

	}

	if(fclose(cons_file) == -1) {
	perror("fclose (cons_file) error \n");
	exit(2);
	}

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


