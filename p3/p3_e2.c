/* 
 * File:   p3_e2.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 
 * Created on 26 de marzo de 2016, 15:45
 */

 #include "queue.h"
 #include "elequeue.h"
 #include "maze.h"
 #include "point.h"
 #include "types.h"
 #include <stdio.h>
 #include <stdlib.h>

 Queue* Recorrer(Maze *m, Point *input){
 	int i;
 	Queue *colaAux = NULL; /*cola auxiliar*/
 	Queue *colaCamino = NULL; /*cola del camino seguido*/
 	EleQueue *pele = NULL; /*punto donde nos encontramos*/
 	EleQueue *pelepoint = NULL; /*Punto vecino*/
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
 	colaAux = queue_ini();
 	if (!colaAux){
 		printf ("Error en reserva memoria colaAux\n");
 		return NULL;
 	}
 	colaCamino = queue_ini();
 	if (!colaCamino){
 		printf ("Error reserva memoria colaCamino\n");
 		queue_free (colaAux);
 		return NULL; 
 	}
 	pele = elequeue_ini();
 	if (!pele){
 		printf ("Error reserva memoria pele\n");
 		queue_free(colaAux);
 		queue_free(colaCamino);
 		return NULL;
 	}
 	if (!elequeue_setInfo(pele, input)){ /*Guardamos el punto input en pele*/
 		printf ("Error en setInfo de pele\n");
 		elequeue_free(pele);
 		queue_free(colaAux);
 		queue_free(colaCamino);
 		return NULL;
 	}
 	if(!queue_insert (colaAux, pele)){ /*Introducimos pele en la cola auxiliar*/
 		printf("Error insert del input\n");
 		elequeue_free(pele);
 		queue_free(colaAux);
 		queue_free(colaCamino);
 		return NULL;
 	}
 	elequeue_free(pele); 
 	while (!queue_isEmpty(colaAux)){ /*mientras la cola auxiliar no esta vacia*/
 		pele = queue_extract(colaAux); /*extraemos el punto superior de la cola y nos "situamos" ahi*/
 		queue_insert(colaCamino, pele); /*Como visitamos ese punto lo introducimos en el camino*/
 		point_setSymbol(maze_getPoint(m, point_getCoordinateX((Point *)elequeue_getInfo(pele)), point_getCoordinateY((Point *)elequeue_getInfo(pele))), VISITADO);
 		/*Modificamos el simbolo del punto a VISITADO, lo guardamos en el laberinto original*/

		
		for(i = 0; i <= DOWN; i++){ /*Comprobamos las 4 direcciones que se pueden seguir dentro de un laberinto*/
			pelepoint = elequeue_ini();
			if(!pelepoint){
				printf("Error en eleQueue_ini\n");
				elequeue_free(pele);
	 			queue_free(colaAux);
	 			queue_free(colaCamino);
 			return NULL;
			}
			ppoint2 = (Point*)elequeue_getInfo(pele); /*Obtenemos el punto de pele*/
			if(!ppoint2){
				printf("Error al obtener el punto de pele");
				elequeue_free(pelepoint);
	 			elequeue_free(pele);
	 			queue_free(colaAux);
	 			queue_free(colaCamino);
	 			return NULL;
			}
			ppoint = maze_getNeighborPoint(m, ppoint2, i); /*Obtenemos el punto vecino en la direccion que indica "i"*/
			if(!ppoint){
				printf("Error ppoint 1\n");
				elequeue_free(pelepoint);
	 			elequeue_free(pele);
	 			queue_free(colaAux);
	 			queue_free(colaCamino);
	 			return NULL;
			}
			if(!elequeue_setInfo(pelepoint, (void*)ppoint)){ /*Asignamos a pelepoint el punto vecino*/
				printf("Error setinfo\n");
				elequeue_free(pelepoint);
	 			elequeue_free(pele);
	 			queue_free(colaAux);
	 			queue_free(colaCamino);
	 			return NULL;
			}
			if(point_getSymbol(ppoint) == SPACE){ /*Introducimos el punto en la cola auxiliar SOLO si es un SPACE*/
				if(!queue_insert(colaAux, pelepoint)){
					printf("Error al hacer el insert de pelepoint");
					elequeue_free(pelepoint);
		 			elequeue_free(pele);
		 			queue_free(colaAux);
		 			queue_free(colaCamino);
		 			return NULL;
				}
			}
			else if(point_getSymbol(ppoint) == OUTPUT){ /*Si el punto es el OUTPUT, lo introduce en el camino y devuelve dicha cola*/
				queue_insert(colaCamino, pelepoint);
				elequeue_free(pelepoint);
				elequeue_free(pele);
				queue_free(colaAux);
				return colaCamino;
			}
			elequeue_free(pelepoint);
		}
 		
 		elequeue_free(pele);
 	}
 	queue_free(colaAux);
 	queue_free(colaCamino);
	return NULL;
 }

int main (int argc, char *argv[]){
	FILE *f = NULL;
	Maze *pmaze = NULL;
	Point *ppoint = NULL;
	Queue *cola = NULL; /*cola donde guardaremos el camino*/
	if(argc != 2){
		printf("Faltan argumentos\n");
		return -1;
	}
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
 	cola = Recorrer(pmaze, ppoint);
 	if (!cola){ /*Si la cola esta vacía es porque no ha encontrado camino o ha ocurrido algún error*/
 		printf("No es posible encontrar un camino\n");
 	}
 	else{
 		printf("Es posible encontrar un camino\n");
 		queue_print(stdout, cola);
 	}
 	queue_free(cola);
 	maze_free(pmaze);
	return 0;
}