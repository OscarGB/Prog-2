/* 
 * File:   p3_e1.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 10 de marzo de 2016, 17:12
 */


#include "queue.h"
#include "elequeue.h"
#include "point.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
	FILE *f = NULL;
	Queue *cola1 = NULL;
	Queue *cola2 = NULL;
	Queue *cola3 = NULL;
	EleQueue *elemento = NULL;
	int n; /*numero de puntos*/
	int i;
	int x, y;
	char symbol;
	Point *punto = NULL;
	if(argc != 2){ /*Comprobamos argumentos*/
		printf("Faltan argumentos\n");
		return -1;
	}
	f = fopen(argv[1], "r"); /*Abrimos el fichero recibido como argumento*/
	if(!f){
		return -1;
	}
	cola1 =  queue_ini(); /*Inicializamos las 3 colas*/
	if(!cola1){
		fclose (f);
		return -1;
	}
	cola2 =  queue_ini();
	if(!cola2){
		queue_free(cola1);
		fclose (f);
		return -1;
	}
	cola3 =  queue_ini();
	if(!cola3){
		queue_free(cola1);
		queue_free(cola2);
		fclose (f);
		return -1;
	}
	printf("Cola 1: Cola "); /*Imprimimos el estado de las colas*/
		if(queue_isEmpty(cola1)){
			printf("vacia\n");
		}
		else{
			printf("ERROR\n");
		}
	printf("Cola 2: Cola ");
		if(queue_isEmpty(cola2)){
			printf("vacia\n");
		}
		else{
			printf("ERROR\n");
		}
	printf("Cola 3: Cola ");
		if(queue_isEmpty(cola3)){
			printf("vacia\n");
		}
		else{
			printf("ERROR\n");
		}
	printf("\n");
	fscanf(f, "%d", &n); /*Leemos el primer número del fichero que indica el número de puntos a leer*/
	for(i=0; i<n; i++){ /*Introducimos los puntos del fichero en la cola*/
		fscanf(f, "%d,%d,%c", &x, &y, &symbol);
		punto = point_ini(); /*Inicializamos un punto*/
		if(!punto){
			fclose(f);
			queue_free(cola3);
			queue_free(cola2);
			queue_free(cola1);
		}
		if(!point_setCoordinateX(punto, x)){ /*Asignamos al punto la coordenada X del punto del fichero*/
			fclose(f);
			queue_free(cola3);
			queue_free(cola2);
			queue_free(cola1);
			point_free(punto);
			return -1;
		}
		if(!point_setCoordinateY(punto, y)){ /*Asignamos al punto la coordenada Y del punto del fichero*/
			fclose(f);
			queue_free(cola3);
			queue_free(cola2);
			queue_free(cola1);
			point_free(punto);
			return -1;
		}
		if(!point_setSymbol(punto, symbol)){ /*Asignamos al punto el símbolo del punto del fichero*/
			fclose(f);
			queue_free(cola3);
			queue_free(cola2);
			queue_free(cola1);
			point_free(punto);
			return -1;
		}
		elemento = elequeue_ini(); /*Inicializamos el elememto que introduciremos en la cola*/
		if(!elemento){
			fclose(f);
			queue_free(cola3);
			queue_free(cola2);
			queue_free(cola1);
			point_free(punto);
			return -1;
		}
		if(!elequeue_setInfo(elemento, punto)){ /*Asignamos al elemento el valor del punto*/
			fclose(f);
			queue_free(cola3);
			queue_free(cola2);
			queue_free(cola1);
			point_free(punto);
			elequeue_free(elemento);
			return -1;
		}
		if(!queue_insert(cola1, elemento)){ /*Insertamos el elemento en la cola 1*/
			fclose(f);
			queue_free(cola3);
			queue_free(cola2);
			queue_free(cola1);
			point_free(punto);
			elequeue_free(elemento);
			return -1;
		}
		elequeue_free(elemento);
		point_free(punto);
		printf("Cola 1: Cola "); /*Imprimimos de nuevo el estado de las 3 colas*/
			if(queue_isEmpty(cola1)){
				printf("vacia\n");
			}
			else{
				printf("con %d elementos:\n", queue_size(cola1));
				queue_print(stdout, cola1);
			}
		printf("Cola 2: Cola ");
			if(queue_isEmpty(cola2)){
				printf("vacia\n");
			}
			else{
				printf("ERROR\n");
			}
		printf("Cola 3: Cola ");
			if(queue_isEmpty(cola3)){
				printf("vacia\n");
			}
			else{
				printf("ERROR\n");
			}
		printf("\n");
	}
	
	for(i=0; i<(n/2); i++){ /*n/2 será la condición para copiar sólo media cola*/
		elemento = queue_extract(cola1); /*Extraemos el elemento de la cola 1 para meter media cola en la cola 2*/
		if(!elemento){
			fclose(f);
			queue_free(cola3);
			queue_free(cola2);
			queue_free(cola1);
			point_free(punto);
			return -1;
		}
		if(!queue_insert(cola2, elemento)){ /*Insertamos el elemento y comprobamos errores*/
			fclose(f);
			queue_free(cola3);
			queue_free(cola2);
			queue_free(cola1);
			point_free(punto);
			elequeue_free(elemento);
			return -1;
		}
		printf("Cola 1: Cola "); /*Imprimimos los estados de la cola, marcando error si la cola3 no esta vacía*/
			if(queue_isEmpty(cola1)){
				printf("vacia\n");
			}
			else{
				printf("con %d elementos:\n", queue_size(cola1));
				queue_print(stdout, cola1);
			}
		printf("Cola 2: Cola ");
			if(queue_isEmpty(cola2)){
				printf("vacia\n");
			}
			else{
				printf("con %d elementos:\n", queue_size(cola2));
				queue_print(stdout, cola2);
			}
		printf("Cola 3: Cola ");
			if(queue_isEmpty(cola3)){
				printf("vacia\n");
			}
			else{
				printf("ERROR\n");
			}
		printf("\n");
		elequeue_free(elemento); /*Liberamos la memoria para no tener pérdidas*/
	}

	while(!queue_isEmpty(cola1)){ /*En este bucle procedemos hasta que la cola1 esté vacía*/
		elemento = queue_extract(cola1); /*Extraemos el elemento*/
		if(!elemento){
			fclose(f);
			queue_free(cola3);
			queue_free(cola2);
			queue_free(cola1);
			point_free(punto);
			return -1;
		}
		if(!queue_insert(cola3, elemento)){ /*Insertamos el elemento*/
			fclose(f);
			queue_free(cola3);
			queue_free(cola2);
			queue_free(cola1);
			point_free(punto);
			elequeue_free(elemento);
			return -1;
		}
		elequeue_free(elemento); /*Liberamos la memoria para no tener pérdidas*/
		printf("Cola 1: Cola "); /*Imprimimos las colas*/
			if(queue_isEmpty(cola1)){
				printf("vacia\n");
			}
			else{
				printf("con %d elementos:\n", queue_size(cola1));
				queue_print(stdout, cola1);
			}
		printf("Cola 2: Cola ");
			if(queue_isEmpty(cola2)){
				printf("vacia\n");
			}
			else{
				printf("con %d elementos:\n", queue_size(cola2));
				queue_print(stdout, cola2);
			}
		printf("Cola 3: Cola ");
			if(queue_isEmpty(cola3)){
				printf("vacia\n");
			}
			else{
				printf("con %d elementos:\n", queue_size(cola3));
				queue_print(stdout, cola3);
			}
		printf("\n");
	} /*Imprimimos las colas, en este caso no tenemos mensaje ERROR, pero sabemos que cola1 estará vacía*/
	printf("Cola 1: Cola ");
		if(queue_isEmpty(cola1)){
			printf("vacia\n");
		}
		else{
			printf("con %d elementos:\n", queue_size(cola1));
			queue_print(stdout, cola1);
		}
	printf("Cola 2: Cola ");
		if(queue_isEmpty(cola2)){
			printf("vacia\n");
		}
		else{
			printf("con %d elementos:\n", queue_size(cola2));
			queue_print(stdout, cola2);
		}
	printf("Cola 3: Cola ");
		if(queue_isEmpty(cola3)){
			printf("vacia\n");
		}
		else{
			printf("con %d elementos:\n", queue_size(cola3));
			queue_print(stdout, cola3);
		}
	printf("\n");

	fclose(f); /*Cerramos el fichero y liberamos memoria*/
	queue_free(cola3);
	queue_free(cola1);
	queue_free(cola2);
	return 0;

}