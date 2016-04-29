/* 
 * File:   p2_e3.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 2 de febrero de 2016, 13:11
 */

 #include "stack.h"
 #include "elestack.h"
 #include "maze.h"
 #include "point.h"
 #include "types.h"
 #include <stdio.h>
 #include <stdlib.h>

 Stack* Recorrer(Maze *m, Point *input){
 	int i;
 	Stack *paux = NULL; /*pila auxiliar*/
 	Stack *pcamino = NULL; /*pila del camino seguido*/
 	EleStack *pele = NULL; /*punto donde nos encontramos*/
 	EleStack *pelepoint = NULL; /*Punto vecino*/
 	Point *ppoint = NULL;
 	Point *ppoint2 = NULL;
 	if(!m){
 		printf("Error pasando el maze\n");
 		return NULL;
 	}
 	if(!input){
 		printf("Error pasando el input\n");
 		return NULL;
 	}
 	paux = stack_ini();
 	if (!paux){
 		printf ("Error en reserva memoria paux\n");
 		return NULL;
 	}
 	pcamino = stack_ini();
 	if (!pcamino){
 		printf ("Error reserva memoria pcamino\n");
 		stack_free (paux);
 		return NULL; 
 	}
 	pele = elestack_ini();
 	if (!pele){
 		printf ("Error reserva memoria pele\n");
 		stack_free(paux);
 		stack_free(pcamino);
 		return NULL;
 	}
 	if (!elestack_setInfo(pele, input)){ /*Guardamos el punto input en pele*/
 		printf ("Error en setInfo de pele\n");
 		elestack_free(pele);
 		stack_free(paux);
 		stack_free(pcamino);
 		return NULL;
 	}
 	if(!stack_push (paux, pele)){ /*Introducimos pele en la pila auxiliar*/
 		printf("Error push del input\n");
 		elestack_free(pele);
 		stack_free(paux);
 		stack_free(pcamino);
 		return NULL;
 	}
 	elestack_free(pele); 
 	while (!stack_isEmpty(paux)){ /*mientras la pila auxiliar no esta vacia*/
 		pele = stack_pop(paux); /*extraemos el punto superior de la pila y nos "situamos" ahi*/
 		stack_push(pcamino, pele); /*Como visitamos ese punto lo introducimos en el camino*/
 		point_setSymbol(maze_getPoint(m, point_getCoordinateX((Point *)elestack_getInfo(pele)), point_getCoordinateY((Point *)elestack_getInfo(pele))), VISITADO);
 		/*Modificamos el simbolo del punto a VISITADO, lo guardamos en el laberinto original*/

		
		for(i = 0; i <= DOWN; i++){ /*Comprobamos las 4 direcciones que se pueden seguir dentro de un laberinto*/
			pelepoint = elestack_ini();
			if(!pelepoint){
				printf("Error en elestack_ini\n");
				elestack_free(pele);
	 			stack_free(paux);
	 			stack_free(pcamino);
 			return NULL;
			}
			ppoint2 = (Point*)elestack_getInfo(pele); /*Obtenemos el punto de pele*/
			if(!ppoint2){
				printf("Error al obtener el punto de pele");
				elestack_free(pelepoint);
	 			elestack_free(pele);
	 			stack_free(paux);
	 			stack_free(pcamino);
	 			return NULL;
			}
			ppoint = maze_getNeighborPoint(m, ppoint2, i); /*Obtenemos el punto vecino en la direccion que indica "i"*/
			if(!ppoint){
				printf("Error ppoint 1\n");
				elestack_free(pelepoint);
	 			elestack_free(pele);
	 			stack_free(paux);
	 			stack_free(pcamino);
	 			return NULL;
			}
			if(!elestack_setInfo(pelepoint, (void*)ppoint)){ /*Asignamos a pelepoint el punto vecino*/
				printf("Error setinfo\n");
				elestack_free(pelepoint);
	 			elestack_free(pele);
	 			stack_free(paux);
	 			stack_free(pcamino);
	 			return NULL;
			}
			if(point_getSymbol(ppoint) == SPACE){ /*Introducimos el punto en la pila auxiliar SOLO si es un SPACE*/
				if(!stack_push(paux, pelepoint)){
					printf("Error al hacer el push de pelepoint");
					elestack_free(pelepoint);
		 			elestack_free(pele);
		 			stack_free(paux);
		 			stack_free(pcamino);
		 			return NULL;
				}
			}
			else if(point_getSymbol(ppoint) == OUTPUT){ /*Si el punto es el OUTPUT, lo introduce en el camino y devuelve dicha pila*/
				stack_push(pcamino, pelepoint);
				elestack_free(pelepoint);
				elestack_free(pele);
				stack_free(paux);
				return pcamino;
			}
			elestack_free(pelepoint);
		}
 		
 		elestack_free(pele);
 	}
 	stack_free(paux);
 	stack_free(pcamino);
	return NULL;
 }

int main (int argc, char *argv[]){
	FILE *f = NULL;
	Maze *pmaze = NULL;
	Point *ppoint = NULL;
	Stack *pila = NULL; /*Pila donde guardaremos el camino*/
	f = fopen(argv[1], "r"); /*Abrimos el archivo en escritura para no modificar su contenido*/
 	if(!f){
 		printf("Error de apertura de fichero\n");
 		return -1;
 	}
 	pmaze = maze_ini();
 	if(!pmaze){
 		printf("Error reserva pmaze\n");
 		fclose(f);
 		return -1;
 	}
 	if(!maze_read(f, pmaze)){ /*Leemos el archivo para guardar el laberinto*/
 		fclose(f);
 		printf("Error lectura maze\n");
 		maze_free(pmaze);
 		return -1;
 	}
 	fclose(f);
 	ppoint = maze_getInput(pmaze); /*Conseguimos el input de nuestro laberinto*/
 	if(!ppoint){
 		printf("Error ppoint input\n");
 		maze_free(pmaze);
 		return -1;
 	}
 	pila = Recorrer(pmaze, ppoint);
 	if (!pila){ /*Si la pila esta vacía es porque no ha encontrado camino o ha ocurrido algún error*/
 		printf("No es posible encontrar un camino\n");
 	}
 	else{
 		printf("Es posible encontrar un camino\n");
 		stack_print(stdout, pila);
 	}
 	stack_free(pila);
 	maze_free(pmaze);
	return 0;
}