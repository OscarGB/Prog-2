/* 
 * File:   solve_mazes.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 01 de abril de 2016, 13:15
 */

#include <stdio.h>
#include <stdlib.h>
#include "elestack.h"
#include "stack.h"
#include "maze.h"
#include "point.h"
#include "elequeue.h"
#include "queue.h"
#include "list.h"
#include "solution.h"
#include "elelist.h"

int mazesolver_stack(const char* maze_file, const Move strat[4]){
	int i, j;
 	Stack *paux = NULL; /*Pila auxiliar*/
 	EleStack *pele = NULL; /*Punto donde nos encontramos*/
 	EleStack *pelepoint = NULL; /*Punto vecino*/
 	Point *ppoint = NULL;
 	Point *ppoint2 = NULL;
 	Maze *m = NULL;
 	FILE *f = NULL;
 	int pasos = 0; /*Número de pasos realizados durante el algoritmo*/
	f = fopen(maze_file, "r"); /*Abrimos el archivo en escritura para no modificar su contenido*/
 	if(!f){
 		printf("Error de apertura de fichero\n");
 		return -1;
 	}
 	m = maze_ini();
 	if(!m){
 		printf("Error reserva m\n");
 		return -1;
 	}
 	if(!maze_read(f, m)){ /*Leemos el archivo para guardar el laberinto*/
 		maze_free(m);
 		printf("Error lectura maze\n");
 		return -1;
 	}
 	fclose(f);

 	paux = stack_ini();
 	if (!paux){
 		printf ("Error en reserva memoria paux\n");
 		maze_free(m);
 		return -1;
 	}
 	pele = elestack_ini();
 	if (!pele){
 		printf ("Error reserva memoria pele\n");
 		maze_free(m);
 		stack_free(paux);
 		return -1;
 	}
 	if (!elestack_setInfo(pele, maze_getInput(m))){ /*Guardamos el punto input en pele*/
 		printf ("Error en setInfo de pele\n");
 		maze_free(m);
 		elestack_free(pele);
 		stack_free(paux);
 		return -1;
 	}
 	if(!stack_push (paux, pele)){ /*Introducimos pele en la pila auxiliar*/
 		printf("Error push del input\n");
 		maze_free(m);
 		elestack_free(pele);
 		stack_free(paux);
 		return -1;
 	}
 	elestack_free(pele); 
 	while (!stack_isEmpty(paux)){ /*Mientras la pila auxiliar no esta vacia*/
 		pele = stack_pop(paux); /*Extraemos el punto superior de la pila y nos "situamos" ahí*/
 		pasos++; /*Aumentamos el numero de pasos que damos*/
 		point_setSymbol(maze_getPoint(m, point_getCoordinateX((Point *)elestack_getInfo(pele)), point_getCoordinateY((Point *)elestack_getInfo(pele))), VISITADO);
 		/*Modificamos el símbolo del punto a VISITADO, lo guardamos en el laberinto original*/

		
		for(i = 0; i <= 3; i++){ /*Comprobamos las 4 direcciones de la estrategia*/
			printf("Movimientos restantes: "); /*Imprimimos los movimientos que faltan por realizar*/
			for(j=i; j<4; j++){
				printf("%d", strat[j]);
			}
			printf("\n");
			pelepoint = elestack_ini();
			if(!pelepoint){
				printf("Error en elestack_ini\n");
 				maze_free(m);
				elestack_free(pele);
	 			stack_free(paux);
 			return -1;
			}
			ppoint2 = (Point*)elestack_getInfo(pele); /*Obtenemos el punto de pele*/
			if(!ppoint2){
				printf("Error al obtener el punto de pele");
				elestack_free(pelepoint);
	 			elestack_free(pele);
	 			stack_free(paux);	
 				maze_free(m);
	 			return -1;
			}
			ppoint = maze_getNeighborPoint(m, ppoint2, strat[i]); /*Obtenemos el punto vecino en la dirección que indica "i"*/
			if(!ppoint){
				printf("Error ppoint 1\n");
				elestack_free(pelepoint);
	 			elestack_free(pele);
	 			stack_free(paux);	
 				maze_free(m);
	 			return -1;
			}
			if(!elestack_setInfo(pelepoint, (void*)ppoint)){ /*Asignamos a pelepoint el punto vecino*/
				printf("Error setinfo\n");
				elestack_free(pelepoint);
	 			elestack_free(pele);
	 			stack_free(paux);	
 				maze_free(m);
	 			return -1;
			}
			if(point_getSymbol(ppoint) == SPACE){ /*Introducimos el punto en la pila auxiliar SOLO si es un SPACE*/
				if(!stack_push(paux, pelepoint)){
					printf("Error al hacer el push de pelepoint");
					elestack_free(pelepoint);
		 			elestack_free(pele);
		 			stack_free(paux);		
 					maze_free(m);
		 			return -1;
				}
			}
			else if(point_getSymbol(ppoint) == OUTPUT){ /*Si el punto es el OUTPUT, devuelve el numero de pasos*/
				if(maze_print(stdout, m) < 0){
					printf("Error de impresión del laberinto\n");
					elestack_free(pelepoint);
					elestack_free(pele);
					stack_free(paux);
	 				maze_free(m);
				}
				elestack_free(pelepoint);
				elestack_free(pele);
				stack_free(paux);
 				maze_free(m);
				return pasos;
			}
			if(maze_print(stdout, m) < 0){
				printf("Error de impresión del laberinto\n");
				elestack_free(pelepoint);
				elestack_free(pele);
				stack_free(paux);
 				maze_free(m);
			}
			elestack_free(pelepoint);
		}
 		elestack_free(pele);
 	}
 	stack_free(paux);
	maze_free(m);
	return -1;
}

int mazesolver_queue(const char* maze_file, const Move strat[4]){
	int i, j;
 	Queue *colaux = NULL; /*Cola auxiliar*/
 	EleQueue *pele = NULL; /*Punto donde nos encontramos*/
 	EleQueue *pelepoint = NULL; /*Punto vecino*/
 	Point *ppoint = NULL;
 	Point *ppoint2 = NULL;
 	Maze *m = NULL;
 	FILE *f = NULL;
 	int pasos = 0; /*Número de pasos realizados durante el algoritmo*/
	

	f = fopen(maze_file, "r"); /*Abrimos el archivo en escritura para no modificar su contenido*/
 	if(!f){
 		printf("Error de apertura de fichero\n");
 		return -1;
 	}
 	m = maze_ini();
 	if(!m){
 		printf("Error reserva m\n");
 		return -1;
 	}
 	if(!maze_read(f, m)){ /*Leemos el archivo para guardar el laberinto*/
 		maze_free(m);
 		printf("Error lectura maze\n");
 		return -1;
 	}
 	fclose(f);

 	colaux = queue_ini(); /*Inicializamos la cola*/
 	if (!colaux){
 		printf ("Error en reserva memoria colaux\n");
 		maze_free(m);
 		return -1;
 	}
 	pele = elequeue_ini(); /*Inicializamos el punto donde nos "situamos"*/
 	if (!pele){
 		printf ("Error reserva memoria pele\n");
 		maze_free(m);
 		queue_free(colaux);
 		return -1;
 	}
 	if (!elequeue_setInfo(pele, maze_getInput(m))){ /*Guardamos el punto input del laberinto en pele*/
 		printf ("Error en setInfo de pele\n");
 		maze_free(m);
 		elequeue_free(pele);
 		queue_free(colaux);
 		return -1;
 	}
 	if(!queue_insert (colaux, pele)){ /*Introducimos pele en la cola*/
 		printf("Error push del input\n");
 		maze_free(m);
 		elequeue_free(pele);
 		queue_free(colaux);
 		return -1;
 	}
 	elequeue_free(pele); 
 	while (!queue_isEmpty(colaux)){ /*Mientras la cola no esté vacía*/
 		pele = queue_extract(colaux); /*Extraemos el primer punto de la cola y nos "situamos" ahí*/
 		pasos++; /*Aumentamos el numero de pasos que damos*/
 		point_setSymbol(maze_getPoint(m, point_getCoordinateX((Point *)elequeue_getInfo(pele)), point_getCoordinateY((Point *)elequeue_getInfo(pele))), VISITADO);
 		/*Modificamos el símbolo del punto a VISITADO, lo guardamos en el laberinto original*/

		
		for(i = 0; i <= 3; i++){ /*Comprobamos las 4 direcciones de la estrategia*/
			printf("Movimientos restantes: "); /*Imprimimos los movimientos que faltan por realizar*/
			for(j=i; j<4; j++){
				printf("%d", strat[j]);
			}
			printf("\n");
			pelepoint = elequeue_ini(); /*Inicializamos el punto "vecino"*/
			if(!pelepoint){
				printf("Error en elequeue_ini\n");
 				maze_free(m);
				elequeue_free(pele);
	 			queue_free(colaux);
 			return -1;
			}
			ppoint2 = (Point*)elequeue_getInfo(pele); /*Obtenemos el punto de pele*/
			if(!ppoint2){
				printf("Error al obtener el punto de pele");
				elequeue_free(pelepoint);
	 			elequeue_free(pele);
	 			queue_free(colaux);	
 				maze_free(m);
	 			return -1;
			}
			ppoint = maze_getNeighborPoint(m, ppoint2, strat[i]); /*Obtenemos el punto vecino en la dirección que indica la posición "i" de la estrategia*/
			if(!ppoint){
				printf("Error ppoint 1\n");
				elequeue_free(pelepoint);
	 			elequeue_free(pele);
	 			queue_free(colaux);	
 				maze_free(m);
	 			return -1;
			}
			if(!elequeue_setInfo(pelepoint, (void*)ppoint)){ /*Asignamos a pelepoint el punto vecino*/
				printf("Error setinfo\n");
				elequeue_free(pelepoint);
	 			elequeue_free(pele);
	 			queue_free(colaux);	
 				maze_free(m);
	 			return -1;
			}
			if(point_getSymbol(ppoint) == SPACE){ /*Introducimos el punto en la cola SOLO si es un SPACE*/
				if(!queue_insert(colaux, pelepoint)){
					printf("Error al hacer el insert de pelepoint");
					elequeue_free(pelepoint);
		 			elequeue_free(pele);
		 			queue_free(colaux);		
 					maze_free(m);
		 			return -1;
				}
			}
			else if(point_getSymbol(ppoint) == OUTPUT){ /*Si el punto es el OUTPUT, devuelve el numero de pasos*/
				if(maze_print(stdout, m) < 0){
					printf("Error de impresión del laberinto\n");
					elequeue_free(pelepoint);
					elequeue_free(pele);
					queue_free(colaux);
	 				maze_free(m);
				}
				elequeue_free(pelepoint);
				elequeue_free(pele);
				queue_free(colaux);
 				maze_free(m);
				return pasos;
			}
			if(maze_print(stdout, m) < 0){
				printf("Error de impresión del laberinto\n");
				elequeue_free(pelepoint);
				elequeue_free(pele);
				queue_free(colaux);
 				maze_free(m);
			}
			elequeue_free(pelepoint);
		}
 		elequeue_free(pele);
 	}
 	
 	queue_free(colaux);
	maze_free(m);
	return -1;
}


void mazesolver_run(const char* maze_file, const Move strat[][4], const int num_strategies){
	int i, pasosCola, pasosPila;
	for (i=0; i<num_strategies; i++){ /*Realizamos un bucle para seleccionar la estrategia*/
		printf("ESTRATEGIA %d%d%d%d\n", strat[i][0], strat[i][1], strat[i][2], strat[i][3]);
		pasosCola = mazesolver_queue(maze_file, strat[i]); /*Resolvemos con cola*/
		if(pasosCola != -1){
			pasosPila = mazesolver_stack(maze_file, strat[i]); /*Resolvemos con pila*/
			if(pasosPila !=-1){
				printf("SALIDA ENCONTRADA\n");
				printf("Pasos realizados con cola: %d\n", pasosCola);
				printf("Pasos realizados con pila: %d\n", pasosPila);
			}else{
				printf("SALIDA NO ENCONTRADA\n");
			}
		}else{
			printf("SALIDA NO ENCONTRADA\n");
			break;
		}
	}
	return;
}

void mazesolver_runSolution(const char* maze_file, const Move strat[][4], const int num_strategies){
	int i, pasosCola, pasosPila;
	Solution *sol=NULL;
	List* lista=NULL;
	EleList* pele=NULL;
	lista = list_ini();
	if(!lista){
		return;
	}
	for (i=0; i<num_strategies; i++){ /*Realizamos un bucle para seleccionar la estrategia*/
		printf("ESTRATEGIA %d%d%d%d\n", strat[i][0], strat[i][1], strat[i][2], strat[i][3]);
		pasosCola = mazesolver_queue(maze_file, strat[i]); /*Resolvemos con cola*/
		if(pasosCola != -1){
			sol = solution_ini();
			if(!sol){
				list_free(lista);
				return;
			}
			if(!solution_setStrat(sol, strat[i])){
				solution_free(sol);
				list_free(lista);
				return;
			}
			if(!solution_setType(sol, COLA)){
				solution_free(sol);
				list_free(lista);
				return;
			}
			if(!solution_setPasos(sol, pasosCola)){
				solution_free(sol);
				list_free(lista);
				return;
			}
			pele = elelist_ini();
			if(!pele){
				solution_free(sol);
				list_free(lista);
				return;
			}
			if(!elelist_setInfo(pele, (void *)sol)){
				solution_free(sol);
				list_free(lista);
				elelist_free(pele);
				return;
			}
			if(!list_insertInOrder(lista, pele)){
				solution_free(sol);
				list_free(lista);
				elelist_free(pele);
				return;
			}
			elelist_free(pele);
			pasosPila = mazesolver_stack(maze_file, strat[i]); /*Resolvemos con pila*/
			if(pasosPila !=-1){

				sol = solution_ini();
				if(!sol){
					list_free(lista);
					return;
				}
				if(!solution_setStrat(sol, strat[i])){
					solution_free(sol);
					list_free(lista);
					return;
				}
				if(!solution_setType(sol, PILA)){
					solution_free(sol);
					list_free(lista);
					return;
				}
				if(!solution_setPasos(sol, pasosPila)){
					solution_free(sol);
					list_free(lista);
					return;
				}
				pele = elelist_ini();
				if(!pele){
					solution_free(sol);
					list_free(lista);
					return;
				}
				if(!elelist_setInfo(pele, (void *)sol)){
					solution_free(sol);
					list_free(lista);
					elelist_free(pele);
					return;
				}
				if(!list_insertInOrder(lista, pele)){
					solution_free(sol);
					list_free(lista);
					elelist_free(pele);
					return;
				}
				elelist_free(pele);

				printf("SALIDA ENCONTRADA\n");
				printf("Pasos realizados con cola: %d\n", pasosCola);
				printf("Pasos realizados con pila: %d\n", pasosPila);
			}else{
				printf("SALIDA NO ENCONTRADA\n");
			}
		}else{
			printf("SALIDA NO ENCONTRADA\n");
			break;
		}
	}
	list_print(stdout, lista);
	list_free(lista);
	return;
}