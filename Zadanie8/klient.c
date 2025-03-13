#include "mq_library.h"
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

mqd_t server_queue = (mqd_t) 0;
mqd_t client_queue = (mqd_t) 0;
char client_queue_name[64];
void clean();
void sig_handler(int sig);

int main (){

snprintf(client_queue_name, 64, "/%d", getpid());

struct mq_attr attr;
attr.mq_flags = 0;
attr.mq_maxmsg = 8;     //max liczba komunikatow w kolejce
attr.mq_msgsize = sizeof(mq_message);        //max rozmiar komunikatu
attr.mq_curmsgs = 0;

client_queue = create_queue(client_queue_name, &attr);
if(client_queue == (mqd_t) 0) {
exit(1);
}

print_attributes(client_queue);

server_queue = open_queue(QUEUE_NAME, O_WRONLY);
if(server_queue == (mqd_t) 0) {
exit(1);
}

atexit(clean);
signal(SIGINT, sig_handler);

char input[BUFFER_SIZE];
mq_message msg;
msg.pid = getpid();

while(1) {
	printf("Wprowadz operacje: (numer1) [+-*/] (numer2)\n");
	if(fgets(input, BUFFER_SIZE, stdin) == NULL) {
	break;
	}

	snprintf(msg.operation, BUFFER_SIZE, "%s", input);

	if(send_msg(server_queue, (char*)&msg, sizeof(msg)) == 0) {
	continue;
	}
	printf("Wyslano operacje do serwera. \n");

	client_queue = open_queue(client_queue_name, O_RDONLY);
	if(client_queue == (mqd_t) 0) {
	exit(1);
	}

	char result[MAX_MSG_SIZE];
	if(receive_msg(client_queue, result, sizeof(result)) == 0) {
	continue;
	}

	printf("Wynik: %s\n", result);

}


return 0;
}


void sig_handler(int sig) {
printf("Zostal dostarczony sygnal SIGINT \n");
clean();
exit(0);
}



void clean() {
if(client_queue != (mqd_t) 0) {
assert(close_queue(client_queue));
assert(unlink_queue(client_queue_name));
}
printf("Kolejka klienta zamknieta i usunieta\n");
if(server_queue != (mqd_t) 0) {
assert(close_queue(server_queue));
}
printf("Kolejka serwera zamknieta\n");
}
