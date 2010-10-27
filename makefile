CFLAGS = -O3
all: test

test: kmp.o test.o

test.o: test.c
kmp.o: kmp.c