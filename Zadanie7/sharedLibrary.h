#ifndef SHAREDLIBRARY_H
#define SHAREDLIBRARY_H

#include <sys/mman.h>
#include <semaphore.h>

int shm_create(const char *name, off_t length);    //tworzenie/otwieranie

int setSize(int fd, off_t length);       //ustawianie rozmiaru

void *mapMemory(int fd, size_t length, int prot, int flags);      //odwzorowywanie pamieci

int unmapMemory(void *addr, size_t length);                //usuwanie odwzorowania 

int shm_close(int fd);                            //zamykanie deskryptora odwzorowania

int shm_destroy (const char *name);                //usun obiekt shm

sem_t *create_sem (const char *name, unsigned int value);    //tworzenie semafora

sem_t *open_sem(const char *name);     //otwieranie semafora

int post_sem(sem_t *sem);           //uruchamianie semafora (zwiekszenie wartosci)

int wait_sem(sem_t *sem);            //wstrzymywanie semafora

int close_sem(sem_t *sem);           //zamykanie semafora

int remove_sem(const char *name);    //usuwanie semafora


#endif
