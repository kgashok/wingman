main: CircularBuffer.h CircularBuffer.c main.c
	clang -std=c99 -pedantic -Wall *.c -o $@
