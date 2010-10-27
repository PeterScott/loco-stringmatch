CFLAGS = -O3
all: test kmp.s

test: kmp.o test.o

test.o: test.c
kmp.o: kmp.c

kmp.s: kmp.c
	gcc -O3 -S kmp.c