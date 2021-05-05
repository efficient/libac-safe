CFLAGS := -fpic -g3 -Og

example: libisolate.so
example: private LDFLAGS += -Wl,-R\$$ORIGIN

libisolate.so: isolate.h

include libgotcha/libgotcha.mk
