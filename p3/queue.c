/* 
 * File:   queue.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 8 de marzo de 2016, 13:11
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "queue.h"

 struct _Queue {
 	EleQueue** head;
	EleQueue** end;
	EleQueue* item[MAXQUEUE];
};

/*Inicializa la cola (reservando memoria) e inicializa sus elementos (no reserva 
memoria para ellos)*/

Queue* queue_ini(){
	Queue *cola = NULL;
	int i;
	cola = (Queue*)malloc(sizeof(Queue));
	if (!cola){
		return NULL;
	}

	for (i=0;i<MAXQUEUE;i++){
		cola->item[i] = NULL;
	}

	cola->head = cola->item;
	cola->end = cola->item;
	return cola;
}

/*Libera la cola y todos sus elementos*/
void queue_free(Queue *cola){
	EleQueue **aux = NULL;
	if (!cola){
		return;
	}
	aux = cola->head;
	while (aux != cola->end){
		elequeue_free (*aux);
		aux = cola->item + (((aux-cola->item)+1)%MAXQUEUE);
	}
	free (cola);
	return;
}

/*Comprueba si la cola está vacía*/
Bool queue_isEmpty(const Queue *cola){
	if (!cola){
		return TRUE;
	}
	if (cola->head == cola->end){
		return TRUE;
	}
	return FALSE;
}

/*Comprueba si la cola está llena*/
Bool queue_isFull(const Queue* cola){
	EleQueue **aux = NULL;
	if (!cola){
		return TRUE;
	}
	if (cola->end == &(cola->item [MAXQUEUE-1])){
		aux = (EleQueue **)cola->item;
	}
	else{
		aux = cola->end;
		aux = aux + 1;
	}
	if (aux == cola->head){
		return TRUE;
	}
	return FALSE;
}

/*Inserta un elemento en la cola, copiando el elemento y reservando memoria para él*/
Queue* queue_insert(Queue *cola, const EleQueue* pele){
	EleQueue *aux = NULL;
	if (!cola || !pele || queue_isFull (cola) == TRUE){
		return NULL;
	}

	aux = elequeue_copy (pele);
	if (!aux){
		return NULL;
	}
	*(cola->end) = aux;
	if (cola->end == &(cola->item [MAXQUEUE-1])){
		cola->end = cola->item;
	}
	else{
		cola->end = cola->end +1;
	}
	return cola;
}

/*Extrae un elemento de la cola, devolviendo el puntero al elemento extraido*/
EleQueue* queue_extract(Queue *cola){
	EleQueue *aux = NULL;
	if (!cola || queue_isEmpty (cola) == TRUE){
	return NULL;
	}

	aux = *(cola->head);

	if (cola->head == &(cola->item [MAXQUEUE-1])){
		cola->head = cola->item;
	}
	else{
		cola->head = cola->head +1;
	}
	return aux;
}

/*Devuelve el número de elementos de la cola*/
int queue_size(const Queue *cola){
	int aux;
	if (!cola){
		return -1;
	}
	aux = cola->end - cola->head;
	if (aux >= 0){
		return aux;
	}
	return MAXQUEUE + aux;
}

/*Imprime toda la cola, devolviendo el número de caracteres escritos*/
int queue_print(FILE *f, const Queue *cola){
	EleQueue **aux = NULL;
	int contador = 0;
	if (!f || !cola){
		return -1;
	}
	aux = cola->head;
	while
	 (aux != cola->end){
		contador += elequeue_print (f, *aux);
		fprintf(f, "\n");
		aux = (EleQueue **)cola->item + (((aux-cola->item)+1)%MAXQUEUE);
		
	}
	return contador;
}