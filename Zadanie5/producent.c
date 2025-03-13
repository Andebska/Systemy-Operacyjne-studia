#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[]) {

    if(argc !=3) {
    fprintf(stderr,"Nieprawidlowa ilosc argumentow. \n");
    fprintf(stderr, "Uruchom program w taki sposob: \n./producent nazwa_potoku prod.txt\n");
    exit(1);
    }

    const char *path = argv[1];        //nazwa potoku
    const char *prod_file = argv[2];   //nazwa pliku z "towarem" producenta
    char buffer[BUFFER_SIZE];
    int producerfd;
    FILE *inputFile;
    size_t nbytes = 0;
    ssize_t bytesRead;

    if((producerfd = open(path, O_WRONLY | O_NONBLOCK)) == -1) {
        perror("Open error \n");
        exit(2);
    }

    if((inputFile = fopen(prod_file, "r")) == NULL) {
	perror("Fopen error \n");
	close(producerfd);
	exit(2);
    }


    while((bytesRead = fread(buffer, 1, BUFFER_SIZE, inputFile)) >0 ) {
	nbytes += bytesRead;
	printf("Producent wyprodukowal: %zu bajtow danych:  %.*s \n", bytesRead, (int)bytesRead, buffer);
	ssize_t bytesWritten = write(producerfd, buffer, bytesRead);
	if(bytesWritten == -1) {
	perror("Write error \n");
	exit(2);
	}
	sleep(2);
    }

    fclose(inputFile);
    close(producerfd);

    return 0;
}

