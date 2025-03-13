#include "sharedLibrary.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int shm_create(const char *name, off_t length) {

int fd = shm_open(name, O_CREAT | O_RDWR, 0644);
if(fd == -1) {
perror("shm_open error \n");
return 0;
}
if(setSize(fd, length) == -1) {
close(fd);
perror("setSize error\n");
return 0;
}
return fd;
}

int setSize(int fd, off_t length) {
if(ftruncate(fd,length) == -1) {
perror("ftruncate error \n");
return 0;
}
return 1;
}


void *mapMemory(int fd, size_t length, int prot, int flags) {            
void *addr = mmap(NULL, length, prot, flags, fd, 0);
if(addr == MAP_FAILED) {
perror("nmap error \n");
return NULL;
}
return addr;
}


int unmapMemory(void *addr, size_t length) {
if(munmap(addr, length) == -1) {
perror("munmap error \n");
return 0;
}
return 1;
}


int shm_close(int fd){
if(close(fd) == -1) {
perror("shm close error \n");
return 0;
}
return 1;
}

int shm_destroy (const char *name) {
if(shm_unlink(name) == -1) {
perror("shm_unlink error \n");
return 0;
}
return 1;
}


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




















