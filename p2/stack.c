/* 
 * File:   stack.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 16 de febrero de 2016, 12:53
 */

#include <stdlib.h>
#include "stack.h"

struct _Stack {
	int top; 
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
	p->top = -1;
	for (i=0;i<MAXSTACK;i++){
		p->item[i]=NULL;
	}
	return p;
}

/*Elimina la pila*/
void stack_free(Stack *p){
	int i;
	if (!p){
		return;
	}
	for (i=0;i<=p->top;i++){
		elestack_free(p->item[i]);
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
	pila->item[pila->top] = e1;
	return pila;
}

/*Extrae un elemento de la pila*/
EleStack * stack_pop(Stack *p){
	EleStack *aux = NULL;
	if(!p || stack_isEmpty(p)){
		return NULL;
	}
	aux = p->item[p->top];
	p->item[p->top] = NULL;
	p->top--;
	return aux;
}

/*Comprueba si la pila esta vacia.*/
Bool stack_isEmpty(const Stack *p){
	if(!p){
		return FALSE;
	}
	if(p->top == -1){
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
	ele = elestack_copy(p->item[p->top]);
	return ele;
}


/*Comprueba si la pila esta llena*/
Bool stack_isFull(const Stack *p){
	if(!p){
		return FALSE;
	}
	if(p->top == (MAXSTACK-1)){
		return TRUE;
	}
	return FALSE;
}
/*Imprime toda la pila*/
int stack_print(FILE*f, const Stack*p){
	int i, numcaracteres;
	if (!p || !f){
		return -1;
	}
    numcaracteres = 0;
	for (i = p->top; i >= 0; i--){
		numcaracteres = numcaracteres + elestack_print(f, p->item[i]);
		fprintf(f,"\n");
	}
	return numcaracteres;
}