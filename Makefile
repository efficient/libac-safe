CFLAGS := -fpic -g3 -Og

libisolate.so: isolate.h

include libgotcha/libgotcha.mk
