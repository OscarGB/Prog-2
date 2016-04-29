/* 
 * File:   dtree.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 24 de abril de 2016, 22:37
 */

#include <stdio.h>
#include <stdlib.h>
#include "eletree.h"
#include "types.h"
#include "tree.h"
#include "list.h"
#include "elelist.h"

typedef struct _NodeBT {
	EleTree *info;
	struct _NodeBT *left;
	struct _NodeBT *right;
} NodeBT;

struct _Tree {
	NodeBT *root;
};

/* Inicializa un nodo reservando memoria */
NodeBT* nodo_ini(){
	NodeBT* nodo = NULL;
	nodo = (NodeBT *)malloc(sizeof(NodeBT));
	if(!nodo){
		return NULL;
	}
	nodo->info = NULL; /* Pongo los punteros a NULL para posteriores comprobaciones */
	nodo->left = NULL;
	nodo->right = NULL;
	return nodo;
}

/* Libera la memoria de un nodo*/
void nodo_free(NodeBT* nodo){
	if(nodo){
		eletree_free(nodo->info);
		free(nodo);
	}
	return;
}

/* Función recursiva para liberación del arbol */
void tree_freeREC(NodeBT* nodo){
	if(nodo){ /* Si el nodo existe paso al siguiente, de manera que libero "de abajo a arriba" */
		tree_freeREC(nodo->right);
		tree_freeREC(nodo->left);
		nodo_free(nodo);
	}
	return;
}

/* Función recursiva que introduce un elemento dependiendo de su valor en el árbol */
Status tree_insertREC(NodeBT **pnodo, const EleTree* po, int dim){
	NodeBT *nodo = NULL;
	EleTree *pele= NULL;
	int cmp; /* Entero donde guardare el valor de la comparación, asi ahorro recursos */
	if(!*pnodo){
		nodo = nodo_ini();
		if(!nodo){
			return ERROR;
		}
		pele = eletree_copy((EleTree *)po);
		if(!pele){
			nodo_free(nodo);
			return ERROR;
		}
		nodo->info = pele;
		*pnodo = nodo;
		return OK;
	}
	cmp = eletree_cmpd(po, (*pnodo)->info, dim);
	if(cmp<=0){ /*Si el elemento es menor que el nodo en el que me sitúo sigo hacia la izquierda*/
		return tree_insertREC(&((*pnodo)->left), po, ((dim + 1) % eletree_getDim(po)));
	}
	if(cmp>0){ /*Si, en cambio, es mayor, continúo por la derecha*/
		return tree_insertREC(&((*pnodo)->right), po, ((dim + 1) % eletree_getDim(po)));
	}
	return OK;
}

/* Función recursiva para contar el número de nodos */
int tree_numNodesREC(const NodeBT *nodo){
	if(!nodo){
		return 0;
	}
	return (1 + tree_numNodesREC(nodo->right) + tree_numNodesREC(nodo->left)); /*retorno el valor de los subárboles derecho e izquierdo + el nodo*/
}

/*Funcion recursiva para hallar profundidad de un árbol*/
int tree_depthREC(const NodeBT *nodo){
	int der, izq;
	if(!nodo){
		return 0;
	}
	else{
		der = tree_depthREC(nodo->right);
		izq = tree_depthREC(nodo->left);
	}
	if(der < izq){ /*retorno el que sea mayor*/
		return 1 + izq; 
	}
	else{
		return 1 + der;
	}
}

/* Función recursiva para hallar un elemento en el árbol */
Bool tree_findEleTreeREC(NodeBT *nodo, const EleTree *pele, int dim){
	int cmp;
	if(!nodo){
		return FALSE;
	}
	cmp = eletree_cmpd(nodo->info, (EleTree *)pele, dim);
	if(cmp == 0){
		if(eletree_cmp(nodo->info, (EleTree *)pele) == 0){
					return TRUE;
		}
	}
	else if(cmp < 0){ /* Busco dependiendo del valor del emento para agilizar la búsqueda */
		return tree_findEleTreeREC(nodo->right, pele, ((dim + 1) %  eletree_getDim(pele)));
	}
	else{
		return tree_findEleTreeREC(nodo->left, pele, ((dim + 1) %  eletree_getDim(pele)));
	}
	return FALSE;
}

/* Función recursiva que imprime en preOrden */
Status tree_preOrderREC(FILE *f, NodeBT* nodo){
	if(!nodo){
		return OK;
	}
	if(eletree_print(f, nodo->info) < 0) return ERROR;
	if(tree_preOrderREC(f, nodo->left) == ERROR) return ERROR;
	if(tree_preOrderREC(f, nodo->right) == ERROR) return ERROR;
	return OK;
}

/* Función recursiva que imprime en inOrden */
Status tree_inOrderREC(FILE *f, NodeBT* nodo){
	if(!nodo){
		return OK;
	}
	if(tree_preOrderREC(f, nodo->left) == ERROR) return ERROR;
	if(eletree_print(f, nodo->info) < 0) return ERROR;
	if(tree_preOrderREC(f, nodo->right) == ERROR) return ERROR;
	return OK;
}

/* Función recursiva que imprime en postOrden */
Status tree_postOrderREC(FILE *f, NodeBT* nodo){
	if(!nodo){
		return OK;
	}
	if(tree_preOrderREC(f, nodo->left) == ERROR) return ERROR;
	if(tree_preOrderREC(f, nodo->right) == ERROR) return ERROR;
	if(eletree_print(f, nodo->info) < 0) return ERROR;
	return OK;
}


/* Inicializa el árbol reservando memoria */
Tree* tree_ini(){
	Tree* arbol = NULL;
	arbol = (Tree *)malloc(sizeof(Tree));
	if(!arbol){
		return NULL;
	}
	arbol->root = NULL; /*Pongo el elemento "raiz" a NULL para comprobación de si un árbol está vacío*/
	return arbol;
}

/* Libera el árbol y todos sus elementos */
void tree_free(Tree *pa){
	if(pa){
		tree_freeREC(pa->root);
		free(pa);
	}
	return;
}

/* Comprueba si un árbol está vacío */
Bool tree_isEmpty( const Tree *pa){
	if(!pa || !pa->root){
		return TRUE;
	}
	return FALSE;
}

/* Inserta en el árbol pa el EleTree po, devolviendo ERROR si el elemento ya existía en el árbol */
Status tree_insert(Tree *pa, const EleTree *po){
	if(!pa || !po || tree_findEleTree(pa, po) == TRUE){
		return ERROR;
	}
	return tree_insertREC(&(pa->root), po, 0);
}

/* Devuelve TRUE si se puede encontrar pe en el árbol pa */
Bool tree_findEleTree(Tree* pa, const EleTree* pe){
	if(!pa || !pe){
		return FALSE;
	}
	return tree_findEleTreeREC(pa->root, pe, 0);
}

/* Devuelve la profundidad del árbol pa, considerando que un árbol vacío tiene profundidad -1 */
int tree_depth(const Tree *pa){
	if(tree_isEmpty(pa)){
		return 0;
	}
	return tree_depthREC(pa->root);
}

/* Devuelve el número de nodos del árbol pa, considerando que un árbol vacío tiene 0 nodos */
int tree_numNodes(const Tree *pa){
	if(tree_isEmpty(pa) == TRUE){
		return 0;
	}
	return tree_numNodesREC(pa->root);
}

/******* Funciones de recorrido del árbol (P4_E3) ********/

/* Muestra el recorrido de un árbol en orden previo */
Status tree_preOrder(FILE *f, const Tree *pa){
	if(!f || !pa){
		return ERROR;
	}
	return tree_preOrderREC(f, pa->root);
}

/* Muestra el recorrido de un árbol en orden medio */
Status tree_inOrder(FILE *f, const Tree *pa){
	if(!f || !pa){
		return ERROR;
	}
	return tree_inOrderREC(f, pa->root);
}

/* Muestra el recorrido de un árbol en orden posterior */
Status tree_postOrder(FILE *f, const Tree *pa){
	if(!f || !pa){
		return ERROR;
	}
	return tree_postOrderREC(f, pa->root);
}

/****** Para el ejercicio opcional de P4_E3 *******/

Status tree_preOrderToListREC(List *l, NodeBT* nodo){
	EleList *pele = NULL;
	if(!nodo||!l){
		return OK;
	}
	pele = elelist_ini(); /*Inicializo un elelist para guardar el elemento*/
	if(!pele){
		return ERROR;
	}
	if(!elelist_setInfo(pele, (void *)eletree_getInfo(nodo->info))){
		elelist_free(pele);
		return ERROR;
	}
	if(!list_insertLast(l, pele)){
		elelist_free(pele);
		return ERROR;
	}
	elelist_free(pele);
	if(tree_preOrderToListREC(l, nodo->left) == ERROR) return ERROR;
	if(tree_preOrderToListREC(l, nodo->right) == ERROR) return ERROR;
	return OK;
}
Status tree_inOrderToListREC(List *l, NodeBT* nodo){
	EleList *pele = NULL;
	if(!nodo||!l){
		return OK;
	}
	if(tree_inOrderToListREC(l, nodo->left) == ERROR) return ERROR;
	pele = elelist_ini(); /*Inicializo un elelist para guardar el elemento*/
	if(!pele){
		return ERROR;
	}
	if(!elelist_setInfo(pele, (void *)eletree_getInfo(nodo->info))){
		elelist_free(pele);
		return ERROR;
	}
	if(!list_insertLast(l, pele)){
		elelist_free(pele);
		return ERROR;
	}
	elelist_free(pele);
	if(tree_inOrderToListREC(l, nodo->right) == ERROR) return ERROR;
	return OK;
}

Status tree_postOrderToListREC(List *l, NodeBT* nodo){
	EleList *pele = NULL;
	if(!nodo||!l){
		return OK;
	}
	if(tree_postOrderToListREC(l, nodo->left) == ERROR) return ERROR;
	if(tree_postOrderToListREC(l, nodo->right) == ERROR) return ERROR;
	pele = elelist_ini(); /*Inicializo un elelist para guardar el elemento*/
	if(!pele){
		return ERROR;
	}
	if(!elelist_setInfo(pele, (void *)eletree_getInfo(nodo->info))){
		elelist_free(pele);
		return ERROR;
	}
	if(!list_insertLast(l, pele)){
		elelist_free(pele);
		return ERROR;
	}
	elelist_free(pele);
	return OK;
}

/* Inserta en la lista l el recorrido de un árbol en orden previo */
Status tree_preOrderToList(List *l, const Tree *pa){	
	return tree_preOrderToListREC(l, pa->root);
}

/* Inserta en la lista l el recorrido de un árbol en orden medio */
Status tree_inOrderToList(List *l, const Tree *pa){
	return tree_inOrderToListREC(l, pa->root);
}

/* Inserta en la lista l el recorrido de un árbol en orden posterior */
Status tree_postOrderToList(List *l, const Tree *pa){	
	return tree_postOrderToListREC(l, pa->root);
}