#include "isolate.h"

#include <stdio.h>

static void *realm(void *args) {
	(void) args;
	fputs("realm()\n", stderr);
	return NULL;
}

struct realm2 {
	int (*fputs)(const char *, FILE *);
	FILE *stderr;
};

static void *realm2(void *args) {
	struct realm2 *io = args;
	io->fputs("realm2()\n", io->stderr);
	return NULL;
}

int main(void) {
	realm(NULL);
	isolate(realm, NULL);

	struct realm2 io = {
		.fputs = fputs,
		.stderr = stderr,
	};
	isolate(realm2, &io);

	return 0;
}
