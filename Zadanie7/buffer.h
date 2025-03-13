#ifndef BUFFER_H
#define BUFFER_H


#define NELE 20            //rozmiar pojedynczego elementu
#define NBUF 5             //liczba elementow bufora (ile moze byc przechowywanych jednoczesnie w buforze)

typedef struct {
	char buffer[NBUF][NELE];
	int insert;
	int remove;
	int count;
} SegmentSM;

#endif //BUFFER_H