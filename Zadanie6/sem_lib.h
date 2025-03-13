#ifndef SEM_LIB_H
#define SEM_LIB_H

#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

sem_t *create_sem (const char *name, unsigned int value);    //tworzenie semafora

sem_t *open_sem(const char *name);     //otwieranie semafora

int get_value(sem_t *sem);         //uzyskiwanie wartosci semafora

int post_sem(sem_t *sem);           //uruchamianie semafora (zwiekszenie wartosci)

int wait_sem(sem_t *sem);            //wstrzymywanie semafora

int close_sem(sem_t *sem);           //zamykanie semafora

int remove_sem(const char *name);    //usuwanie semafora

#endif     //SEM_LIB_H