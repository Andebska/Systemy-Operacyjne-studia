#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>


#define PRODUCER_BUFFER_SIZE 256
#define CONSUMER_BUFFER_SIZE 128

void producer();
void consumer();
void destroy();


int main() {

    mkfifo("pipe", 0644);

    if (fork() == 0) {
        producer();
        printf("Proces producenta zakonczyl prace\n");
    }

    if (fork() == 0) {
        consumer();
        printf("Proces konsumenta zakonczyl prace\n");
    }

    wait(NULL);
        
atexit(destroy);
return 0;
}

   
void producer() {
    int producerfd;
    FILE *inputFile;
    char buffer[PRODUCER_BUFFER_SIZE];
    size_t nbytes = 0;
    ssize_t bytesRead;

    if((inputFile = fopen("prod.txt", "r")) == NULL) {
	perror("Fopen error \n");
	exit(1);
    }

    producerfd = open("pipe", O_WRONLY);     //otwieramy potok

    while((bytesRead = fread(buffer, 1, PRODUCER_BUFFER_SIZE, inputFile)) >0 ) {
	nbytes += bytesRead;
	printf("Producent wyprodukowal: %zu bajtow danych:  %.*s \n", bytesRead, (int)bytesRead, buffer);
	if(write(producerfd, buffer, bytesRead) == -1){
	perror("Write error \n");
	exit(2);
	}
	sleep(1);
    }
    fclose(inputFile);
    close(producerfd);
}

void consumer() {
    int consumerfd;
    FILE *outputFile;
    char buffer[CONSUMER_BUFFER_SIZE];
    size_t nbytes = 0;
    ssize_t bytesReceived;


    if((outputFile = fopen("kons.txt", "w")) == NULL) {
	perror("Fopen error \n");
	exit(2);
    }

    consumerfd = open("pipe", O_RDONLY);

    while((bytesReceived = read(consumerfd, buffer, CONSUMER_BUFFER_SIZE)) > 0) {
	nbytes += bytesReceived;
	printf("Konsument odczytal: %zu bajtow danych: %.*s\n", bytesReceived, (int)bytesReceived, buffer);
	fwrite(buffer, 1, bytesReceived, outputFile);
	sleep(3);
    }
    fclose(outputFile);
    close(consumerfd);
}

void destroy() {
	unlink("pipe");
	printf("Potok usuniety \n");
}
