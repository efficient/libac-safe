#include <assert.h>
#include <netdb.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NAMESZ 10

struct args {
	socklen_t addrlen;
	const struct sockaddr *addr;
	char name[NAMESZ];
};

static void *thread(void *arg) {
	struct args *args = arg;
	getnameinfo(args->addr, args->addrlen, args->name, NAMESZ, NULL, 0, 0);
	return NULL;
}

int main(void) {
	struct addrinfo *ai;
	getaddrinfo("127.0.0.1", NULL, NULL, &ai);

	struct sockaddr_storage sa;
	socklen_t salen = ai->ai_addrlen;
	memcpy(&sa, ai->ai_addr, salen);
	freeaddrinfo(ai);
	ai = NULL;

	struct args args = {
		.addrlen = salen,
		.addr = (struct sockaddr *) &sa,
	};
	char acter = '|';
	unsigned canceled = 0;
	while(true) {
		printf("%c\b", acter);
		fflush(stdout);
		switch(acter) {
		case '|':
			acter = '/';
			break;
		case '/':
			acter = '-';
			break;
		case '-':
			acter = '\\';
			break;
		case '\\':
			acter = '|';
			break;
		}

		pthread_t tid;
		pthread_create(&tid, NULL, thread, &args);
		pthread_cancel(tid);

		void *res;
		pthread_join(tid, &res);
		if(res != PTHREAD_CANCELED) {
			printf("%d ", canceled);
			puts(args.name);
			assert(!strcmp(args.name, "localhost"));
		} else
			++canceled;
	}
	return 0;
}
