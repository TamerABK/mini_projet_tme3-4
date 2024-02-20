CFLAGS = -g -Wno-unused-parameter -ggdb
CC = gcc 

PROGRAMS= mainLC mainH mainTest

.PHONY:	all clean

all: mainLC mainH mainTest

biblioLC: biblioLC.o  biblioLC.h
	$(CC) -o $@ $(CFLAGS) $^

entreeSortieLC: entreeSortieLC.o mainLC.o biblioLC.h 
	$(CC) -o $@ $(CFLAGS) $^

biblioH: biblioH.o biblioH.h
	$(CC) -o $@ $(CFLAGS) $^

entreeSortieH: entreeSortieH.o mainH.o biblioH.h
	$(CC) -o $@ $(CFLAGS) $^

mainLC: biblioLC.o entreeSortieLC.o mainLC.o
	$(CC) -o $@ $(CFLAGS) $^

mainH: biblioH.o entreeSortieH.o mainH.o
	$(CC) -o $@ $(CFLAGS) $^

mainTest: biblioH.o entreeSortieH.o biblioLC.o entreeSortieLC.o mainTest.o
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm -f *.o *~ $(PROGRAMS)

