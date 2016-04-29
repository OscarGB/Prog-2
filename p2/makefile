all: p2_e1 p2_e2 p2_e3 p2_e4

p2_e1: p2_e1.o stack.o elestack-int.o
	gcc -g -Wall -ansi -pedantic -o p2_e1 stack.o p2_e1.o elestack-int.o

p2_e2: p2_e2.o stack.o elestack-point.o maze.o point.o
	gcc -g -Wall -ansi -pedantic -o p2_e2 p2_e2.o stack.o elestack-point.o maze.o point.o

p2_e3: stack.o elestack-point.o point.o maze.o p2_e3.o
	gcc -g -Wall -ansi -pedantic -o p2_e3 p2_e3.o stack.o elestack-point.o maze.o point.o

p2_e4: stack-pointer.o elestack-point.o point.o maze.o p2_e3.o
	gcc -g -Wall -ansi -pedantic -o p2_e4 stack-pointer.o elestack-point.o point.o maze.o p2_e3.o

elestack-int.o: elestack-int.c elestack.h types.h
	gcc -g -Wall -ansi -pedantic -c elestack-int.c

stack.o: stack.c stack.h elestack.h types.h
	gcc -g -Wall -ansi -pedantic -c stack.c

p2_e1.o: stack.h elestack.h types.h p2_e1.c 
	gcc -g -Wall -ansi -pedantic -c p2_e1.c

p2_e2.o: stack.h elestack.h types.h point.h maze.h p2_e2.c
	gcc -g -Wall -ansi -pedantic -c p2_e2.c

p2_e3.o: stack.h elestack.h point.h maze.h types.h p2_e3.c
	gcc -g -Wall -ansi -pedantic -c p2_e3.c

stack-pointer.o: stack-pointer.c stack.h elestack.h types.h
	gcc -g -Wall -ansi -pedantic -c stack-pointer.c

elestack-point.o: elestack-point.c elestack.h types.h
	gcc -g -Wall -ansi -pedantic -c elestack-point.c

maze.o: maze.c maze.h types.h point.h
	gcc -g -Wall -ansi -pedantic -c maze.c

point.o: point.c point.h types.h
	gcc -g -Wall -ansi -pedantic -c point.c

clean:
	rm -f p2_e1 p2_e2 p2_e3 p2_e4 *.o
