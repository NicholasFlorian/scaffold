CC = gcc
CFLAGS = -Wall -g -Iinclude -std=c11

all: main

#------------------------------------------------------------------------------------

#main - main.exe -> scaffold.o, iostr.a, opstr.a


main: lib/libscaffoldInterface.a
	$(CC) $(CFLAGS) -o bin/main -L./lib/ -lscaffoldInterface

#------------------------------------------------------------------------------------

#scaffoldInterface - libscaffoldInterface.a -> scaffoldInterface.o -> 
# scaffoldInterface.c, scaffoldInterface.h


scaffoldInterface: lib/libscaffoldInterface.a

lib/libscaffoldInterface.a: scaffoldInterface.o
	ar cr lib/libscaffoldInterface.a scaffoldInterface.o

scaffoldInterface.o: src/scaffoldInterface.c
	$(CC) $(CFLAGS) -c src/scaffoldInterface.c

#------------------------------------------------------------------------------------

#Utility Funtions

clean:
	rm *.o
	rm lib/*.a
	rm bin/main

run:
	./bin/main

cclear:
	clear
	clear

r: cclear clean main run
