CC=g++
CFLAGS=-I. -L. -lc++

libacmequeue.o: libacmequeue.cpp libacmequeue.h
	$(CC) -c -o $@ $< $(CFLAGS)

libacmequeue.a: libacmequeue.o
	ar rcs libacmequeue.a libacmequeue.o

aqtest: aqtest.cpp libacmequeue.a
	$(CC) $(CFLAGS) -lacmequeue -o aqtest aqtest.cpp 

all: libacmequeue.o libacmequeue.a aqtest

clean:
	rm -fr *.o *.a aqtest AcmeQueueTest
