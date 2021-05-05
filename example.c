#include "isolate.h"

#include <stdio.h>

static void *realm(void *args) {
	(void) args;
	fputs("realm()\n", stderr);
	return NULL;
}

int main(void) {
	realm(NULL);
	isolate(realm, NULL);

	return 0;
}
