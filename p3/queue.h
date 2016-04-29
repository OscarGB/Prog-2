/* 
 * File:   queue.h
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 8 de marzo de 2016, 13:11
 */

#ifndef QUEUE_H
#define	QUEUE_H

#include <stdio.h>
#include "types.h"
#include "elequeue.h"
#define MAXQUEUE 4096

typedef struct _Queue Queue;
/**----------------------------------------------------------------------------
Inicializa la cola: reserva memoria para ella e inicializa todos sus elementos. 
Es importante que no se reserve memoria para los elementos de la cola.
-------------------------------------------------------------------------------*/
Queue* queue_ini();
/**------------------------------------------------------------------
Libera la cola y todos sus elementos.
------------------------------------------------------------------*/
void queue_free(Queue *cola);
/**------------------------------------------------------------------
Comprueba si la cola está vacía.
------------------------------------------------------------------*/
Bool queue_isEmpty(const Queue *cola);
/**------------------------------------------------------------------
Comprueba si la cola está llena.
------------------------------------------------------------------*/
Bool queue_isFull(const Queue* cola);
/**------------------------------------------------------------------
Inserta un elemento en la cola realizando para ello una copia del mismo, 
reservando memoria nueva para él.
------------------------------------------------------------------*/
Queue* queue_insert(Queue *cola, const EleQueue* pele);
/**--------------------------------------------------------------------------------
Extrae un elemento de la cola. Es importante destacar que la cola deja de apuntar a 
este elemento por lo que la gestión de su memoria debe ser coherente: devolver el 
puntero al elemento o devolver una copia liberando el elemento en la cola.
-----------------------------------------------------------------------------------*/
EleQueue* queue_extract(Queue *cola);
/**------------------------------------------------------------------
Devuelve el número de elementos de la cola.
------------------------------------------------------------------*/
int queue_size(const Queue *cola);
/**------------------------------------------------------------------
Imprime toda la cola, devolviendo el número de caracteres escritos.
------------------------------------------------------------------*/
int queue_print(FILE *f, const Queue *cola);

#endif /*QUEUE_H*/