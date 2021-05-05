#define LIBISOLATE_C_
#include "isolate.h"

#include "libgotcha/libgotcha_api.h"

#include <assert.h>
#include <string.h>
#include <threads.h>

struct isolate {
	libgotcha_group_t group;
};

void *isolate(void *(*fun)(void *), void *arg) {
	static thread_local struct isolate group;
	return isolate_r(fun, arg, &group);
}

void *isolate_r(void *(*fun)(void *), void *arg, struct isolate *ctx) {
	assert(fun);
	assert(sizeof *ctx == ISOLATE_OPAQUE_BYTES);

	libgotcha_group_t group;
	if(ctx && ctx->group)
		group = ctx->group;
	else {
		group = libgotcha_group_new();
		assert(group != LIBGOTCHA_GROUP_ERROR);
		if(ctx)
			ctx->group = group;
	}

	libgotcha_group_thread_set(group);

	void *res = fun(arg);

	libgotcha_group_thread_set(LIBGOTCHA_GROUP_SHARED);
	return res;
}
