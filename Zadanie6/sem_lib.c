#include "sem_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

sem_t *create_sem (const char *name, unsigned int value) {
	sem_t *sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if(sem == SEM_FAILED) {
	perror("sem_open (create) error \n");
	return NULL;
	}
	return sem;
}


sem_t *open_sem(const char *name) {
	sem_t *sem = sem_open(name, 0);
	if(sem == SEM_FAILED) {
	perror("sem_open error \n");
	return NULL;
	}
	return sem;
}


int get_value(sem_t *sem) {
	int sval;                                   //lub int *sval
	if(sem_getvalue(sem, &sval) == -1) {
	perror("get_value error \n");
	return 0;
	}
	return sval;
}


int post_sem(sem_t *sem) {
	if(sem_post(sem) == -1) {
	perror("sem_post error \n");
	return 0;
	}
	return 1;
}


int wait_sem(sem_t *sem) {
	if(sem_wait(sem) == -1) {
	perror("sem_wait error \n");
	return 0;
	}
	return 1;
}


int close_sem(sem_t *sem) {
	if(sem_close(sem) == -1) {
	perror("sem_close error \n");
	return 0;
	}
	return 1;
}


int remove_sem(const char *name) {
	if(sem_unlink(name) == -1) {
	perror("sem_unlink error \n");
	return 0;
	}
	return 1;
}








