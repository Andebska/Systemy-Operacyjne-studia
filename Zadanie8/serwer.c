#include "mq_library.h"
#include <assert.h>
#include <signal.h>
#include <stdbool.h>

mqd_t server_queue = (mqd_t) 0;
void clean();
void sig_handler(int sig);
bool cleaned = false;

int main(){

struct mq_attr attr;
attr.mq_flags = 0;
attr.mq_maxmsg = 8;     //max liczba komunikatow w kolejce
attr.mq_msgsize = sizeof(mq_message);        //max rozmiar komunikatu
attr.mq_curmsgs = 0;

server_queue = create_queue(QUEUE_NAME, &attr);
if(server_queue == (mqd_t) 0) {
exit(1);
}

print_attributes(server_queue);

atexit(clean);
signal(SIGINT, sig_handler);

while(1) {

	mq_message msg;
	if(receive_msg(server_queue, (char*)&msg, sizeof(msg)) == 0) {
	continue;
	}
	printf("Odebrano operacje od klienta. \n");
	int num1, num2;
	int result;
	char result_str[64];
	char operator;
	sscanf(msg.operation, "%d %c %d", &num1, &operator, &num2);
	printf("Dzialanie: %d %c %d \n", num1, operator, num2);
	if(operator == '/' && num2 == 0) {
	snprintf(result_str, sizeof(result_str), "Error: dzielenie przez zero\n");
	} else {
	switch(operator) {
	case '+':
		result = num1 + num2;
		break;
	case'-':
		result = num1 - num2;
		break;
	case'*':
		result = num1 * num2;
		break;
	case'/':
		result = num1 / num2;
		break;
	default:
		snprintf(result_str, sizeof(result_str), "Error: operator nie rozpoznany\n");
		break;
	}
	snprintf(result_str, sizeof(result_str), "%d", result);
	}
	
	char client_queue_name[64];
	snprintf(client_queue_name, 64, "/%d", msg.pid);

	mqd_t client_queue = open_queue(client_queue_name, O_WRONLY);
	if (client_queue == 0) {
	continue;
	}

	if(send_msg(client_queue, result_str, strlen(result_str) + 1) == 0) {
	continue;
	}
	printf("Wyslano wynik: %d do klienta\n", result);
	assert(close_queue(client_queue));
	
}


return 0;
}

void sig_handler(int sig) {
printf("Zostal dostarczony sygnal SIGINT \n");
if(!cleaned) {
clean();
cleaned = true;
}
exit(0);
}



void clean() {
if(!cleaned) {
if(server_queue != (mqd_t) 0) {
assert(close_queue(server_queue));
assert(unlink_queue(QUEUE_NAME));
}
printf("Kolejka serwera zamknieta i usunieta\n");
cleaned = true;
}
}
