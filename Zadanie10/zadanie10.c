#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM_THREADS 5
#define NUM_ITERATIONS 3

volatile bool choosing[NUM_THREADS];
volatile int num[NUM_THREADS];
int shared_counter = 0;
int current_private_line = 3;
int current_critical_line = 3;

void *thread_fun(void *arg);

int main(){

pthread_t threads[NUM_THREADS];
int id_threads[NUM_THREADS];
int thr;

for(int i = 0; i < NUM_THREADS; i++) {        //inicjalizacja tablic
	choosing[i] = false;
	num[i] = 0;
	id_threads[i] = 0;
}

for(int i = 0; i < NUM_THREADS; i++) {
	id_threads[i] = i;
	if((thr = pthread_create(&threads[i], NULL, thread_fun, &id_threads[i])) != 0) {
	fprintf(stderr, "pthread_create error: %s \n", strerror(thr));
	exit(1);
	}
}


for(int i = 0; i < NUM_THREADS; i++) {
	if((thr = pthread_join(threads[i], NULL)) != 0) {
	fprintf(stderr, "pthread_join error: %s \n", strerror(thr));
	exit(1);
	}
}


if(shared_counter == NUM_THREADS * NUM_ITERATIONS) {
	printf("Wartosc wspolnego licznika: %d prawidlowa\n", shared_counter);
} else {
	printf("Wartosc wspolnego licznika: %d nieprawidlowa\n", shared_counter);
}


return 0;
}


void *thread_fun(void *arg){

int i = *((int *)arg);
int priv_counter = 0;


for(int itr = 0; itr < NUM_ITERATIONS; itr++) {
	int line_private, line_critical;

	//sekcja prywatna
	line_private = current_private_line++;
	printf("\033[%d;1H\033[2K", line_private);
	printf("Watek o ID: %d w sekcji prywatnej \n", i);
	fflush(stdout);
	sleep(1);

	//wejscie do sekcji krytycznej
	choosing[i] = true;
	int max_num = 0;
	for(int k = 0; k < NUM_THREADS; k++) {
	if(num[k] > max_num) {
		max_num = num[k];
	}
	}
	num[i] = max_num + 1;
	choosing[i] = false;

	for(int j = 0; j < NUM_THREADS; j++) {
	while(choosing[j]);
	while(num[j] != 0 && (num[j] < num[i] || (num[j] == num[i] && j < i)));
	}

	//sekcja krytyczna
	line_critical = current_critical_line++;
	printf("\033[%d;80H\033[2K", line_critical);
	printf("Watek o ID: %d w sekcji krytycznej. Wartosc prywatnego licznika: %d \n", i, 	priv_counter);
	fflush(stdout);
	priv_counter = shared_counter;
	priv_counter++;
	sleep(1);
	shared_counter = priv_counter;

	//wyjscie z sekcji krytycznej
	num[i] = 0;
	printf("\033[%d;1H\033[2K", line_critical);
	printf("Watek o ID: %d zakonczyl sekcje krytyczna. Wartosc prywatnego licznika: %d \n", i, priv_counter);
	fflush(stdout);

	//reszta
}
return NULL;
}







