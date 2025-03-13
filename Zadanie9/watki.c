#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 4
#define NUM_ITERATIONS 3

pthread_mutex_t myMutex;
pthread_mutex_t printMutex;
int shared_counter = 0;
int current_private_line = 3;
int current_critical_line = 3;

void *thread_fun(void *arg);

int main(){

pthread_t threads[NUM_THREADS];
int id_threads[NUM_THREADS];
int thr;

if((thr = pthread_mutex_init(&myMutex, NULL)) != 0) {
	fprintf(stderr, "mutex_init error: %s \n", strerror(thr));
	exit(1);
}

if((thr = pthread_mutex_init(&printMutex, NULL)) != 0) {
	fprintf(stderr, "mutex_init error: %s \n", strerror(thr));
	exit(1);
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

pthread_mutex_destroy(&myMutex);
pthread_mutex_destroy(&printMutex);

if(shared_counter == NUM_THREADS * NUM_ITERATIONS) {
	printf("Wartosc wspolnego licznika: %d prawidlowa\n", shared_counter);
} else {
	printf("Wartosc wspolnego licznika: %d nieprawidlowa\n", shared_counter);
}

return 0;
}


void *thread_fun(void *arg) {
int threadID = *((int *)arg);
int priv_counter = 0;
int thr;

for(int i = 0; i < NUM_ITERATIONS; ++i) {
	int line_private, line_critical;

	//sekcja prywatna
	if ((thr = pthread_mutex_lock(&printMutex)) != 0) {
	fprintf(stderr, "pthread_mutex_lock error: %s\n", strerror(thr));
	exit(1);
	}
	line_private = current_private_line++;
	printf("\033[%d;1H\033[2K", line_private);
	printf("Watek o ID: %d w sekcji prywatnej \n", threadID);
	if ((thr = pthread_mutex_unlock(&printMutex)) != 0) {
	fprintf(stderr, "pthread_mutex_lock error: %s\n", strerror(thr));
	exit(1);
	}

	sleep(1);

	//sekcja krytyczna
	if ((thr = pthread_mutex_lock(&myMutex)) != 0) {
	fprintf(stderr, "pthread_mutex_lock error: %s\n", strerror(thr));
	exit(1);
	}
	if ((thr = pthread_mutex_lock(&printMutex)) != 0) {
	fprintf(stderr, "pthread_mutex_lock error: %s\n", strerror(thr));
	exit(1);
	}
	line_critical = current_critical_line++;
	printf("\033[%d;50H\033[2K", line_critical);
	printf("Watek o ID: %d w sekcji krytycznej. Wartosc prywatnego licznika: %d \n", threadID, priv_counter);
	if ((thr = pthread_mutex_unlock(&printMutex)) != 0) {
	fprintf(stderr, "pthread_mutex_lock error: %s\n", strerror(thr));
	exit(1);
	}

	priv_counter = shared_counter;
	priv_counter++;
	sleep(2);
	shared_counter = priv_counter;
	if ((thr = pthread_mutex_lock(&printMutex)) != 0) {
	fprintf(stderr, "pthread_mutex_lock error: %s\n", strerror(thr));
	exit(1);
	}
	printf("\033[%d;50H\033[2K", line_critical);
	printf("Watek o ID: %d zakonczyl sekcje krytyczna. Wartosc prywatnego licznika: %d \n", threadID, priv_counter);

	if ((thr = pthread_mutex_unlock(&printMutex)) != 0) {
	fprintf(stderr, "pthread_mutex_lock error: %s\n", strerror(thr));
	exit(1);
	}
	if ((thr = pthread_mutex_unlock(&myMutex)) != 0) {
	fprintf(stderr, "pthread_mutex_lock error: %s\n", strerror(thr));
	exit(1);
	}

}

return NULL;
}




