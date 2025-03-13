#include "mq_library.h"


mqd_t create_queue(const char *name, struct mq_attr *attr) {
	mqd_t mqdes = mq_open(name, O_CREAT | O_RDWR, 0644, attr);
	if(mqdes == (mqd_t) - 1) {
	perror("mq_open error \n");
	return (mqd_t) 0;
	}
	return mqdes;
}


mqd_t open_queue(const char *name, int oflag) {
	mqd_t mqdes = mq_open(name, oflag);
	if(mqdes == (mqd_t) - 1) {
	perror("mq_open error \n");
	return (mqd_t) 0;
	}
	return mqdes;
}


int close_queue(mqd_t mqdes) {
	if(mq_close(mqdes) == -1) {
	perror("mq_close error \n");
	return 0;
	}
	return 1;
}


int unlink_queue(const char *name) {
	if(mq_unlink(name) == -1) {
	perror("mq_unlink error \n");
	return 0;
	}
	return 1;
}


int get_attributes(mqd_t mqdes, struct mq_attr *attr) {
	if(mq_getattr(mqdes, attr) == -1) {
	perror("mq_getattr error \n");
	return 0;
	}
	return 1;
}


int set_attributes(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr) {
	if(mq_setattr(mqdes, newattr, oldattr) == -1) {
	perror("mq_setattr error \n");
	return 0;
	}
	return 1;
}


int send_msg(mqd_t mqdes, const char *msg_ptr, size_t msg_len) {
	if(mq_send(mqdes, msg_ptr, msg_len, 0) == -1) {
	perror("mq_send error \n");
	return 0;
	}
	return 1;
}


int receive_msg(mqd_t mqdes, char *msg_ptr, size_t msg_len) {
	if(mq_receive(mqdes, msg_ptr, msg_len, NULL) == -1) {
	perror("mq_receive error \n");
	return 0;
	}
	return 1;
}


void print_attributes(mqd_t mqdes) {
	struct mq_attr attr;
	if(mq_getattr(mqdes, &attr) == -1) {
	perror("mq_getattr error \n");
	return;
	}
	printf("Atrybuty kolejki: \n");
	printf("Flagi: %ld\n", attr.mq_flags);
	printf("Maksymalna liczba komunikatow w kolejce: %ld\n", attr.mq_maxmsg);
	printf("Maksymalny rozmiar komunikatu: %ld bajtow\n", attr.mq_msgsize);
	printf("Liczba komunikatow aktualnie w kolejce: %ld\n", attr.mq_curmsgs);
}





