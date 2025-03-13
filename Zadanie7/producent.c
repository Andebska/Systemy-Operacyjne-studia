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
	const char *prod_filename = "prod.txt";
	
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
	sas->count = 0;	

	if (signal(SIGINT, sig_handler) == SIG_ERR) {
	perror("signal error \n");
	exit(2);
	}

	FILE *prod_file = fopen(prod_filename, "r");
	if(prod_file == NULL) {
	perror("Fopen (prod.txt) error \n");
	exit(1);
	}

	while(1) {	
	char data[NELE];
	if(fgets(data, NELE, prod_file) == NULL) {        //czytamy z pliku
	sas->count = -1;
	assert(post_sem(cons_sem) && "Blad przy podnoszeniu semafora");
	break;       //konczy prace gdy nie ma juz surowca
	}
	sleep(1);
	
	int bytes_read = strlen(data);

	assert(wait_sem(prod_sem) && "Blad przy opuszczaniu semafora");

	strcpy(sas->buffer[sas->insert], data);       //umieszczamy w buforze
	sas->insert = (sas->insert + 1) % NBUF;
	sas->count++;
	printf("Producent zapisal %d bajtow danych: %s\n", bytes_read, data);

	assert(post_sem(cons_sem) && "Blad przy podnoszeniu semafora");
	}

	if(fclose(prod_file) == -1){
	perror("fclose (prod_file) error \n");
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




