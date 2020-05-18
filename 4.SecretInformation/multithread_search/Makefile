CFLAGS=-c -std=c++1z -O3
LFLAGS=-lpthread -lstdc++fs
CC=g++

HEADERS=file_manager.h KMP.h threads_manager.h


all: multisearch

clean:
	rm -rf multisearch *.o

multisearch: main.o KMP.o file_manager.o threads_manager.o
	$(CC) main.o KMP.o file_manager.o threads_manager.o $(LFLAGS) -o multisearch



main.o: main.cpp $(HEADERS)
	$(CC) $(CFLAGS) main.cpp
KMP.o: KMP.cpp $(HEADERS)
	$(CC) $(CFLAGS) KMP.cpp
file_manager.o: KMP.cpp $(HEADERS)
	$(CC) $(CFLAGS) file_manager.cpp
threads_manager.o: KMP.cpp $(HEADERS)
	$(CC) $(CFLAGS) threads_manager.cpp


