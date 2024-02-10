CFLAGS = -g -Wno-unused-parameter
CC = gcc



.PHONY:	all clean

all: main

biblioLC: biblioLC.o  biblioLC.h
	$(CC) -o $@ $(CFLAGS) $^

entreeSortieLC: entreeSortieLC.o main.o biblioLC.h 
	$(CC) -o $@ $(CFLAGS) $^

main: biblioLC.o entreeSortieLC.o main.o
	$(CC) -o $@ $(CFLAGS) $^



clean:
	rm -f *.o *~ $(PROGRAMS)

