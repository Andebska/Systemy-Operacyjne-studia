#ifndef MQ_LIBRARY_H
#define MQ_LIBRARY_H

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define QUEUE_NAME "/server_queue"
#define MAX_MSG_SIZE 256         //max rozmiar komunikatu
#define BUFFER_SIZE (MAX_MSG_SIZE - sizeof(pid_t))     //rozmiar bufora do przechowywania komunikatu

typedef struct {
	pid_t pid;	
	char operation[BUFFER_SIZE];
}mq_message;


mqd_t create_queue(const char *name, struct mq_attr *attr);
mqd_t open_queue(const char *name, int oflag);
int close_queue(mqd_t mqdes);
int unlink_queue(const char *name);
int get_attributes(mqd_t mqdes, struct mq_attr *attr);
int set_attributes(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr);
int send_msg(mqd_t mqdes, const char *msg_ptr, size_t msg_len);
int receive_msg(mqd_t mqdes, char *msg_ptr, size_t msg_len);
void print_attributes(mqd_t mqdes);







#endif //MQ_LIBRARY_H
