CFLAGS = -g -Wall -pedantic -ansi

all: p4_e1 p4_e2 p4_e2_bal p4_e3 p4_e4 p4_e4_bal p4_e5

#incluimos makefile externo para compilacion de p4_e2, p4_e2_bal, p4_e4 y p4_e4_bal
include makefile_ext 

p4_e1: p4_e1.o tree.o eletree.o  elelist-int.o list.o point.o
	gcc $(CFLAGS) -o p4_e1 p4_e1.o tree.o eletree.o elelist-int.o list.o point.o

p4_e3: p4_e1.o tree.o eletree.o  elelist-int.o list.o 
	gcc $(CFLAGS) -o p4_e3 p4_e1.o tree.o eletree.o elelist-int.o list.o 

p4_e5: p4_e5.o tree.o eletree-cad.o cadena.o elelist-int.o list.o 
	gcc $(CFLAGS) -o p4_e5 p4_e5.o tree.o eletree-cad.o cadena.o elelist-int.o list.o 

p4_e5.o: p4_e5.c tree.h eletree.h cadena.h
	gcc $(CFLAGS) -c p4_e5.c

eletree-cad.o: eletree-cad.c eletree.h cadena.h
	gcc $(CFLAGS) -c eletree-cad.c

cadena.o: cadena.c cadena.h
	gcc $(CFLAGS) -c cadena.c

p4_e1.o: p4_e1.c tree.h types.h eletree.h list.h elelist.h point.h
	gcc $(CFLAGS) -c p4_e1.c

tree.o: tree.c eletree.h list.h types.h tree.h elelist.h
	gcc $(CFLAGS) -c tree.c

dtree.o: dtree.c eletree.h list.h types.h tree.h elelist.h
	gcc $(CFLAGS) -c dtree.c

eletree.o: eletree.c eletree.h types.h
	gcc $(CFLAGS) -c eletree.c

elelist-int.o: elelist-int.c elelist.h 
	gcc $(CFLAGS) -c elelist-int.c

elelist-point.o: elelist-point.c elelist.h 
	gcc $(CFLAGS) -c elelist-point.c

list.o: list.c list.h elelist.h
	gcc $(CFALGS) -c list.c

clean:
	rm -f p4_e1  *.o p4_e2 p4_e2_bal p4_e3 p4_e4 p4_e4_bal p4_e5 