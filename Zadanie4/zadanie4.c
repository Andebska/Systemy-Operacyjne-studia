#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define PRODUCER_BUFFER_SIZE 512
#define CONSUMER_BUFFER_SIZE 256

void producer(int *filedes, const char* prod_path);
void consumer(int *filedes, const char* cons_path);

int main(int argc, char*argv[]) {

if(argc !=3) {
fprintf(stderr,"Nieprawidlowa ilosc argumentow. \n");
fprintf(stderr, "Uruchom pragram w taki sposob: \n./zadanie4.c prod.txt kons.txt\n");
exit(1);
}

int filedes[2];
pid_t pid;
const char* prod_path = argv[1];
const char* cons_path = argv[2];


if (pipe(filedes) == -1) {       //tworzy potok nienazwany
perror("Pipe error \n");
exit(2);
}

pid = fork();
switch(pid) {

case -1:
perror("Fork error \n");
exit(2);

case 0:
close(filedes[1]);                   //zamknij nieuzywane (zapis)
consumer(filedes, cons_path);
break;

default:
close(filedes[0]);                   //zamknij nieuzywane (odczyt)
producer(filedes, prod_path);
wait(NULL);
break;                          //czekaj na zakonczenie potomka
};

return 0; 
}


void producer(int *filedes, const char* prod_path) {
char buffer[PRODUCER_BUFFER_SIZE];
ssize_t nbytes;

int producerfd = open(prod_path, O_RDONLY);
if(producerfd == -1) {
	perror("Open error \n");
	exit(1);
}
while((nbytes = read(producerfd, buffer, PRODUCER_BUFFER_SIZE)) != 0) {
	if(write(filedes[1], buffer, nbytes) == -1) {
	perror("Write error \n");
	exit(1);
	}
	printf("Producent zapisal: %zd bajtow towaru: %.*s \n\n", nbytes, (int)nbytes, buffer);
	sleep(5);
}
close(producerfd);
close(filedes[1]);
}


void consumer(int *filedes, const char* cons_path) {
char buffer[CONSUMER_BUFFER_SIZE];
ssize_t nbytes;

int consumerfd = open(cons_path, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
if(consumerfd == -1) {
	perror("Open error \n");
	exit(2);
}
while((nbytes = read(filedes[0], buffer, CONSUMER_BUFFER_SIZE)) != 0) {
	if(write(consumerfd, buffer, nbytes) == -1) {
	perror("Write error \n");
	exit(2);
}
	printf("Konsument odczytal: %zd bajtow towaru: %.*s \n", nbytes, (int)nbytes, buffer);
	sleep(3);
}
close(consumerfd);
close(filedes[0]);
}
