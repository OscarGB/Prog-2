/* 
 * File:   list.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 3 de abril de 2016, 18:38
 */

#include "list.h"
#include "elelist.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _Nodo {
	EleList* data;
	struct _Nodo *next;
} Nodo;
struct _List {
	Nodo *nodo;
};

Nodo* nodoList_ini() {
	Nodo *pn = NULL; /*Nodo a crear*/
	pn = (Nodo *) malloc(sizeof(Nodo));
	if (!pn){
		return NULL;
	}
	pn->data = NULL; /*Los ponemos a NULL porque no tenemos información de él*/
	pn->next = NULL;
	return pn;
}

void nodoList_free(Nodo *pn) {
	if (!pn) {
		return;
	}
	elelist_free(pn->data); /*Libera elemento de data*/
	free(pn); /*Libera el nodo*/
	return;
}

/* Inicializa la lista reservando memoria e inicializa todos sus elementos. */
List* list_ini(){
	List *pl = NULL;
	pl = (List *)malloc(sizeof(List)); /*Reservo memoria para la lista*/
	if (!pl){
		return NULL;
	}
	pl->nodo = NULL;
	return pl;
}

/* Libera la lista y todos sus elementos. */
void list_free(List* list){
	if (!list){
		return;
	}
	while (list_isEmpty (list) == FALSE){ /*Hasta que la lista no esté vacía*/
		elelist_free(list_extractFirst(list)); /*Liberamos el primer elemento*/
	}
	
	free (list);
	return;
}

/* Inserta al principio de la lista realizando una copia del elemento. */
List* list_insertFirst(List* list, const EleList *elem){
	Nodo* pn = NULL;
	EleList* pele = NULL;
	if(!list || !elem){
		return NULL;
	}
	pn = nodoList_ini(); /*Creo el nodo a insertar*/
	if(!pn){
		return NULL;
	}
	pele = elelist_copy(elem); /*Copio el elemento*/
	if(!pele){
		nodoList_free(pn);
		return NULL;
	}
	pn->data = pele; /*Asigno el elemento copiado*/
	pn->next = list->nodo; /*Asigno next al primer nodo de la lista anterior y modifico nodo para que señale al nuevo nodo*/
	list->nodo = pn;/*Modifico el principio de la lista*/
	return list;
}

/* Inserta al final de la lista realizando una copia del elemento. */
List* list_insertLast(List* list, const EleList *elem){
	Nodo* pn = NULL;
	Nodo* recorrer = NULL;
	EleList* pele = NULL;
	if(!list || !elem){
		return NULL;
	}
	pn = nodoList_ini(); /*Creo nodo*/
	if(!pn){
		return NULL;
	}
	pele = elelist_copy(elem); /*Copio elemento*/
	if(!pele){
		nodoList_free(pn);
		return NULL;
	}
	pn->data = pele; /*Se lo asigno al nodo*/
	if(list_isEmpty(list)){
		list->nodo = pn;
		return list;
	}
	recorrer = list->nodo;
	while(recorrer->next != NULL){ /*Recorro la lista hasta encontrar el final de la misma*/
		recorrer = recorrer->next;
	}
	recorrer->next = pn;
	return list;
}

/* Inserta en orden en la lista realizando una copia del elemento. */
List* list_insertInOrder(List *list, const EleList *pElem){
	EleList* pele = NULL;
	/*int *i, *valor, *siguiente;*/
	Nodo* recorrer = NULL;
	Nodo* insert = NULL;

	if (!list || !pElem){
		return NULL;
	}
	pele = elelist_copy (pElem);
	if (!pele){
		return NULL;
	}
	insert = nodoList_ini();
	if (!insert){
		elelist_free (pele);
		return NULL;
	}
	insert->data = pele; /*Hemos creado el nodo a insertar en la lista*/

	if (!list->nodo){ /*Caso lista vacía*/
		list->nodo = insert;
		return list;
	}

	recorrer = list->nodo;

	if (!list->nodo->next){ /*Caso de lista con un nodo*/
		if (elelist_cmp(recorrer->data, pele) < 0){ /*Si el elemento a introducir es igual que el del nodo de la lista, lo introducimos después*/
			list->nodo->next = insert;
			return list;
		}
		else{
			insert->next = list->nodo;
			list->nodo = insert;
			return list;
		}
	}

	if(elelist_cmp(recorrer->data, pele) > 0 ){/*Caso donde el primer elemento es mayor que el introducido*/
		insert->next = list->nodo;
		list->nodo = insert;
		return list;
	}


	while (elelist_cmp(recorrer->data, pele) < 0 && elelist_cmp(recorrer->next->data, pele) < 0){ /*La condición es que el valor del elemento del nodo donde "estamos" y el
	 												valor del elemento del nodo siguiente sean menores que la variable valor*/
		recorrer = recorrer->next; /*Nos "movemos" al siguiente*/
		if (!recorrer->next){ /*Si "estamos" en el último nodo de la lista*/
			break;
		}
	}
	insert->next = recorrer->next; /*Apuntamos el campo next del nodo a insertar al siguiente nodo en el que "estamos*/
	recorrer->next = insert; /*Apuntamos el campo next de donde "estamos" al nodo que insertamos*/
	return list;
}

/* Extrae del principio de la lista realizando una copia del elemento almacenado en dicho nodo. */
EleList* list_extractFirst(List* list){
	EleList* pele = NULL;
	Nodo* pnodo;
	if (!list || list_isEmpty(list) == TRUE){
		return NULL;
	}
	if (!list->nodo->next){ /*Caso de un solo nodo*/
		pele = elelist_copy (list->nodo->data);
		if(!pele){
			return NULL;
		}
		nodoList_free (list->nodo);
		list->nodo = NULL;
		return pele;
	}
	pele = elelist_copy (list->nodo->data); /*Caso de más de un nodo*/
	if (!pele){
		return NULL;
	}
	pnodo = list->nodo; /*Guardo la dirección del nodo a extraer*/
	list->nodo = list->nodo->next; /*Hacemos que apunte al siguiente nodo*/
	nodoList_free (pnodo);
	return pele;
}

/* Extrae del final de la lista realizando una copia del elemento almacenado en dicho nodo. */
EleList* list_extractLast(List* list){
	EleList* pele = NULL;
	Nodo *recorrer = NULL;
	if(!list || list_isEmpty(list) == TRUE){
		return NULL;
	}
	if(!list->nodo->next){ /*Caso de un solo nodo*/
		pele = elelist_copy(list->nodo->data);
		if(!pele){
			return NULL;
		}
		nodoList_free(list->nodo);
		list->nodo = NULL;
		return pele;
	}
	recorrer = list->nodo;
	while(recorrer->next->next != NULL){ /*Recorro la lista hasta encontrar el penúltimo nodo de la misma*/
		recorrer = recorrer->next;
	}
	pele = elelist_copy(recorrer->next->data);
	if(!pele){
		return NULL;
	}
	nodoList_free(recorrer->next);
	recorrer -> next = NULL;
	return pele;
}

/* Comprueba si una lista está vacía o no. */
Bool list_isEmpty(const List* list){
	if(!list){ /*Si no existe la lista*/
		return TRUE;
	}
	if(!list->nodo){ /*Si no existe ningún nodo*/
		return TRUE;
	}
	return FALSE;
}

/* Devuelve el tamaño de una lista. */
int list_size(const List* list){
	Nodo *pn = NULL;
	int contador = 1;
	if(!list){
		return -1;
	}
	if(list_isEmpty(list) == TRUE){
		return 0;
	}
	pn = list->nodo;
	while(pn->next != NULL){ /*Recorro la lista, aumentando el contador*/
		pn = pn->next;
		contador++;
	}
	return contador;
}

/* Imprime una lista devolviendo el número de caracteres escritos. */
int list_print(FILE *fd, const List* list){
	Nodo *pn;
	int contador = 0, auxiliar;
	if(!fd || !list){
		return -1;
	}
	pn = list->nodo;
	while(pn != NULL){ /*Recorro la lista*/
		auxiliar = elelist_print(fd, pn->data);
		if(auxiliar <= 0){ /*Compruebo si la impresión parcial ha sido exitosa*/
			printf("Error de impresión");
			return -1;
		}
		contador += auxiliar;
		pn = pn->next;
	}
	return contador;
}
