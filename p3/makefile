CFLAGS = -g -Wall -pedantic -ansi

all: p3_e1 p3_e2 p3_e3 p3_e4 p3_e5

p3_e1: p3_e1.o point.o elequeue-point.o queue.o
	gcc $(CFLAGS) -o p3_e1 p3_e1.o point.o elequeue-point.o queue.o

p3_e2: p3_e2.o point.o elequeue-point.o queue.o maze.o
	gcc $(CFLAGS) -o p3_e2 p3_e2.o point.o elequeue-point.o queue.o maze.o

p3_e3: p3_e3.o point.o elequeue-point.o queue.o maze.o elestack-point.o stack-pointer.o solve_mazes.o list.o elelist-solution.o solution.o
	gcc $(CFLAGS) -o p3_e3 p3_e3.o point.o elequeue-point.o queue.o maze.o elestack-point.o stack-pointer.o solve_mazes.o list.o elelist-solution.o solution.o

p3_e4: p3_e4.o list.o elelist-int.o
	gcc $(CFLAGS) -o p3_e4 p3_e4.o list.o elelist-int.o

p3_e5: p3_e5.o point.o elequeue-point.o queue.o maze.o elestack-point.o stack-pointer.o solve_mazes.o list.o elelist-solution.o solution.o
	gcc $(CFLAGS) -o p3_e5 p3_e5.o point.o elequeue-point.o queue.o maze.o elestack-point.o stack-pointer.o solve_mazes.o list.o elelist-solution.o solution.o

elelist-solution.o: elelist-solution.c elelist.h solution.h
	gcc $(CFLAGS) -c elelist-solution.c

solution.o: solution.c solution.h maze.h
	gcc $(CFLAGS) -c solution.c

p3_e4.o: p3_e4.c types.h elelist.h list.h
	gcc $(CFLAGS) -c p3_e4.c

list.o: list.c elelist.h list.h types.h
	gcc $(CFLAGS) -c list.c

elelist-int.o: elelist-int.c elelist.h types.h
	gcc $(CFLAGS) -c elelist-int.c

solve_mazes.o: solve_mazes.c solve_mazes.h elestack.h stack.h maze.h point.h elequeue.h queue.h list.h solution.h elelist.h
	gcc $(CFLAGS) -c solve_mazes.c

p3_e3.o: p3_e3.c point.h maze.h elequeue.h queue.h types.h elestack.h stack.h
	gcc $(CFLAGS) -c p3_e3.c

elestack-point.o: elestack-point.c elestack.h point.h types.h
	gcc $(CFLAGS) -c elestack-point.c

stack-pointer.o: stack-pointer.c stack.h elestack.h types.h
	gcc $(CFLAGS) -c stack-pointer.c

maze.o: maze.c maze.h point.h types.h
	gcc $(CFLAGS) -c maze.c

p3_e2.o: p3_e2.c point.h maze.h elequeue.h queue.h types.h
	gcc $(CFLAGS) -c p3_e2.c

point.o: point.c point.h types.h
	gcc $(CFLAGS) -c point.c

elequeue-point.o: elequeue-point.c elequeue.h point.h types.h
	gcc $(CFLAGS) -c elequeue-point.c

queue.o: queue.c queue.h elequeue.h types.h
	gcc $(CFLAGS) -c queue.c

p3_e1.o: p3_e1.c queue.h elequeue.h types.h point.h
	gcc $(CFLAGS) -c p3_e1.c

clean: 
	rm -f p3_e1 p3_e2 p3_e3 p3_e4 p3_e5 *.o
