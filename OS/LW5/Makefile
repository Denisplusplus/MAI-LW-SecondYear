CC = gcc
FLAGS = -std=c99 -pthread -w -pipe -O2 -Wextra -Werror -Wall -Wno-sign-compare -pedantic -lm

all: run

run: libqueue.so mainStat.o mainDyn.o
	$(CC) $(FLAGS) -o run-stat mainStat.o -L. -lqueue -Wl,-rpath,.
	$(CC) $(FLAGS) -o run-dyn mainDyn.o -ldl

mainStat.o: mainStat.c
	$(CC) -c $(FLAGS) mainStat.c

mainDyn.o: mainDyn.c
	$(CC) -c $(FLAGS) mainDyn.c	

queue.o: queue.c
	$(CC) -c -fPIC $(FLAGS) queue.c

libqueue.so: queue.o
	$(CC) $(FLAGS) -shared -o libqueue.so queue.o

clean:
	rm -f *.o run-stat run-dyn *.so
