#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

int main(int argc, char *argv[]) {
    if(argc !=3) {
    fprintf(stderr,"Nieprawidlowa ilosc argumentow. \n");
    fprintf(stderr, "Uruchom program w taki sposob: \n./konsument nazwa_potoku kons.txt\n");
    exit(1);
    }

    const char *path = argv[1];            //nazwa potoku
    const char *cons_file = argv[2];       //nazwa pliku , do ktorego konsument zapisuje dane
    char buffer[BUFFER_SIZE];
    int consumerfd;
    FILE *outputFile;
    size_t nbytes = 0;
    ssize_t bytesReceived;

    if((consumerfd = open(path, O_RDONLY)) == -1) {
        perror("Open error \n");
        exit(2);
    }

    if((outputFile = fopen(cons_file, "w")) == NULL) {
	perror("Fopen error \n");
	close(consumerfd);
	exit(2);
    }

    while((bytesReceived = read(consumerfd, buffer, BUFFER_SIZE)) > 0) {
	nbytes += bytesReceived;
	printf("Konsument odczytal: %zu bajtow danych: %.*s\n", bytesReceived, (int)bytesReceived, buffer);
	fwrite(buffer, 1, bytesReceived, outputFile);
	sleep(3);
    }

    fclose(outputFile);
    close(consumerfd);

    return 0;
}
