#define LIBISOLATE_C_
#include "isolate.h"

#include "libgotcha/libgotcha_api.h"

#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

#define MAGIC "isolate"

struct isolate {
	libgotcha_group_t group;
	char magic[sizeof MAGIC];
};

static thread_local struct isolate group;

void *isolate(void *(*fun)(void *), void *arg) {
	return isolate_r(fun, arg, &group);
}

static void init(struct isolate *isolate, libgotcha_group_t group) {
	assert(group);
	assert(group != LIBGOTCHA_GROUP_ERROR);
	isolate->group = group;
	strcpy(isolate->magic, MAGIC);
}

void *isolate_r(void *(*fun)(void *), void *arg, struct isolate *ctx) {
	assert(fun);
	assert(sizeof *ctx == ISOLATE_OPAQUE_BYTES);

	libgotcha_group_t group;
	if(ctx && !strncmp(ctx->magic, MAGIC, sizeof MAGIC))
		group = ctx->group;
	else {
		group = libgotcha_group_new();
		if(ctx)
			init(ctx, group);
	}

	libgotcha_group_thread_set(group);

	void *res = fun(arg);

	libgotcha_group_thread_set(LIBGOTCHA_GROUP_SHARED);
	return res;
}

struct wrapper {
	void *(*fun)(void *);
	void *arg;
	struct isolate group;
	char *release;
};

static void release(void *release) {
	struct wrapper *wrapper = release;
	if(wrapper->release)
		*wrapper->release = *MAGIC;
	free(wrapper);
}

static void *wrapper(void *arg) {
	struct wrapper *wrapper = arg;
	pthread_cleanup_push(release, wrapper);
	arg = isolate_r(wrapper->fun, wrapper->arg, &wrapper->group);
	pthread_cleanup_pop(true);
	return arg;
}

static void disable(void) {
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
}

static void enable(void) {
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
}

#pragma weak libisolate_pthread_create = pthread_create
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*fun)(void *), void *arg) {
	static bool bootstrapped;
	if(!bootstrapped) {
		libgotcha_shared_prehook(disable);
		libgotcha_shared_hook(enable);
		if(strncmp(group.magic, MAGIC, sizeof MAGIC))
			init(&group, libgotcha_group_new());
		bootstrapped = true;
	}

	struct wrapper *args = malloc(sizeof *args);
	char magic = *MAGIC;
	args->fun = fun;
	args->arg = arg;
	args->release = NULL;
	if(atomic_compare_exchange_strong(group.magic, &magic, '\0')) {
		memcpy(&args->group, &group, sizeof args->group);
		*args->group.magic = *MAGIC;
		args->release = group.magic;
	}
	return pthread_create(thread, attr, wrapper, args);
}
