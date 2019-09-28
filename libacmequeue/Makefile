CC=g++
CFLAGS=-I. -L.

libacmequeue.o: libacmequeue.cpp libacmequeue.h
	$(CC) -c -o $@ $< $(CFLAGS)

libacmequeue.a: libacmequeue.o
	ar rcs libacmequeue.a libacmequeue.o

aqtest: aqtest.cpp libacmequeue.a
	gcc $(CFLAGS) -lacmequeue -o aqtest aqtest.cpp 

all: libacmequeue.o libacmequeue.a aqtest

clean:
	rm *.o *.a aqtest
