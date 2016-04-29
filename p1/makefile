
all: p1_e1 p1_e2 clean

p1_e1: point.o p1_e1.o
	gcc -g -Wall -ansi -pedantic -o p1_e1 point.o p1_e1.o

p1_e2: point.o maze.o p1_e2.o
	gcc -g -Wall -ansi -pedantic -o p1_e2 point.o maze.o p1_e2.o

point.o: point.c point.h types.h
	gcc -g -Wall -ansi -pedantic -c point.c

p1_e1.o: p1_e1.c point.h types.h
	gcc -g -Wall -ansi -pedantic -c p1_e1.c

maze.o: maze.c maze.h types.h point.h
	gcc -g -Wall -ansi -pedantic -c maze.c

p1_e2.o: maze.h point.h types.h p1_e2.c
	gcc -g -Wall -ansi -pedantic -c p1_e2.c

clean:
	rm *.o