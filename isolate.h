#ifndef LIBISOLATE_H_
#define LIBISOLATE_H_

#define ISOLATE_OPAQUE_BYTES 8

#ifdef LIBISOLATE_C_
typedef struct isolate isolate_t;
#else
typedef unsigned char isolate_t[ISOLATE_OPAQUE_BYTES];
#endif

void *isolate(void *(*)(void *), void *);
void *isolate_r(void *(*)(void *), void *, isolate_t *);

#endif
