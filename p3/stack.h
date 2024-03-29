
/* 
 * File:   stack.h
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 16 de febrero de 2016, 12:53
 */

#ifndef STACK_H
#define STACK_H

#include "types.h"
#include "elestack.h"


#define MAXSTACK 4096

typedef struct _Stack Stack;

/**------------------------------------------------------------------
Inicializa la pila reservando memoria. 
Salida: NULL si ha habido error o la pila si ha ido bien
------------------------------------------------------------------*/
Stack * stack_ini();
/**------------------------------------------------------------------
Elimina la pila 
Entrada: la pila que se va a eliminar
------------------------------------------------------------------*/
void stack_free(Stack *);
/**-----------------------------------------------------------------
Inserta un elemento en la pila. 
Entrada: un elemento y la pila donde insertarlo. 
Salida: NULL si no logra insertarlo o la pila resultante si lo logra
------------------------------------------------------------------*/
Stack * stack_push(Stack *, const EleStack *);
/**------------------------------------------------------------------
Extrae un elemento en la pila. 
Entrada: la pila de donde extraerlo. 
Salida: NULL si no logra extraerlo o el elemento extraido si lo logra. Nótese que la pila quedará modificada
------------------------------------------------------------------*/
EleStack * stack_pop(Stack *);
/**--------------------------------------------------------
Copia un elemento (reservando memoria) sin modificar el top de la pila. 
Entrada: la pila de donde copiarlo. 
Salida: NULL si no logra copiarlo o el elemento si lo logra
------------------------------------------------------------------*/
EleStack * stack_top(const Stack *);
/**------------------------------------------------------------------
Comprueba si la pila esta vacia. 
Entrada: pila. 
Salida: TRUE si está vacia o FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack *);
/**------------------------------------------------------------------
Comprueba si la pila esta llena. 
Entrada: pila. 
Salida: TRUE si está llena o FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isFull(const Stack *);
/**------------------------------------------------------------------
Imprime toda la pila, colocando el elemento en la cima al principio de la impresión(y un elemento por línea).
Entrada: pila y fichero donde imprimirla. 
Salida: Devuelve el número de caracteres escritos.
------------------------------------------------------------------*/
int stack_print(FILE*, const Stack*);

#endif /* STACK_H*/