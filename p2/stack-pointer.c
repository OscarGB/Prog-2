/* 
 * File:   stack-pointer.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 04 de marzo de 2016, 12:53
 */

#include <stdlib.h>
#include "stack.h"

struct _Stack {
	EleStack **top;
	EleStack* item[MAXSTACK];
};
/*Inicializamos la pila reservando memoria*/
Stack * stack_ini(){
	Stack *p = NULL;
	int i;
	p = (Stack *)malloc(sizeof(Stack));
	if (!p){
		return NULL;
	}
	p->top =  p->item - 1;
	for (i=0; i<MAXSTACK; i++){
		p->item[i]=NULL;
	}
	return p;
}

/*Elimina la pila*/
void stack_free(Stack *p){
	if (!p){
		return;
	}
	while(!stack_isEmpty(p)){
		elestack_free(*(p->top));
		p->top--;
	}
	free(p);
	return;
}

/*Inserta un elemento en la pila*/
Stack * stack_push(Stack *pila, const EleStack *ele){
	EleStack *e1 = NULL;
	if (!pila || !ele){
		return NULL;
	}
	if (stack_isFull (pila)){
		return NULL;
	}
	e1 = elestack_copy(ele);
	if (!e1){
		return NULL;
	}
	pila->top++;
	*(pila->top) = e1;
	return pila;
}

/*Extrae un elemento de la pila*/
EleStack * stack_pop(Stack *p){
	EleStack *aux = NULL;
	if(!p || stack_isEmpty(p)){
		return NULL;
	}
	aux = *(p->top);
	*(p->top) = NULL;
	p->top--;
	return aux;
}

/*Comprueba si la pila esta vacia.*/
Bool stack_isEmpty(const Stack *p){
	if(!p){
		return FALSE;
	}
	if(p->top == p->item-1){
		return TRUE;
	}
	return FALSE;
}

/*Saca el ultimo elemento sin modificar la pila
RESERVA MEMORIA*/
EleStack * stack_top(const Stack *p){
	EleStack *ele = NULL;;
	if(!p || stack_isEmpty(p)){
		return NULL;
	}
	ele = elestack_copy(*(p->top));
	return ele;
}


/*Comprueba si la pila esta llena*/
Bool stack_isFull(const Stack *p){
	if(!p){
		return FALSE;
	}
	if(*(p->top) == p->item[MAXSTACK-1]){
		return TRUE;
	}
	return FALSE;
}
/*Imprime toda la pila*/
int stack_print(FILE*f, const Stack*p){
	int numcaracteres;
	EleStack **top;
	top = p->top;
	if (!p || !f){
		return -1;
	}
    numcaracteres = 0;
    while((top-p->item)>=0){
    	numcaracteres = numcaracteres + elestack_print(f, *(top));
		fprintf(f,"\n");
		top--;
    }

	return numcaracteres;
}