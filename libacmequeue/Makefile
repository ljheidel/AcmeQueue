CC=g++
CFLAGS=-I. -L. -lc++ -O

libacmequeue.o: libacmequeue.cpp libacmequeue.h
	$(CC) -c -o $@ $< $(CFLAGS)

libacmequeue.a: libacmequeue.o
	ar rcs libacmequeue.a libacmequeue.o

aqtest: aqtest.cpp libacmequeue.a
	$(CC) $(CFLAGS) -lacmequeue -o aqtest aqtest.cpp 

aqpush: aqpush.cpp libacmequeue.a
	$(CC) $(CFLAGS) -lacmequeue -o aqpush aqpush.cpp 

aqtool: aqtool.cpp libacmequeue.a
	$(CC) $(CFLAGS) -lacmequeue -o aqtool aqtool.cpp 

all: libacmequeue.o libacmequeue.a aqtest aqpush aqtool

clean:
	rm -fr *.o *.a aqtest aqpush aqtool AcmeQueueTest
