/* 
 * File:   p4_e5.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 29 de abril de 2016, 13:35
 */

#include <stdio.h>
#include <stdlib.h>
#include "eletree.h"
#include "types.h"
#include "tree.h"
#include <string.h>
#include "cadena.h"

#define MAX 256

int main (int argc, char *argv[]){
	FILE *f = NULL;
	Tree *tree = NULL;
	EleTree *pele = NULL;
	Cadena* cad = NULL;
	int numnodos, profundidad;
	char cadena[MAX], buscar[MAX];


	if(argc != 2){ /*Comprobamos argumentos*/
	printf("Faltan argumentos\n");
	return -1;
	}

	f = fopen (argv[1], "r"); /*Abrimos el fichero recibido como argumento*/
	if (!f){
		return -1;
	}

	tree = tree_ini(); /*Inicializamos el árbol en el que vamos a guardar las cadenas*/
	if (!tree){
		fclose(f);
		return -1;
	}

	while (feof(f) == 0){ /*Bucle que lee uno a uno las cadenas del fichero*/
		fscanf (f, "%s\n", cadena); /*Guardamos el dato leido en cadena*/
		pele = eletree_ini(); /*Inicializamos un EleTree*/
		if (!pele){
			fclose(f);
			tree_free(tree);
			return -1;
		}
		cad = cadena_ini(); /*Inicializamos una cadena*/
		if(!cad){
			eletree_free(pele);
			fclose(f);
			tree_free(tree);
			return -1;
		}
		if(!cadena_setInfo(cad, cadena)){
			fclose(f);
			tree_free(tree);
			eletree_free(pele);
			cadena_free(cad);
			return -1;
		}
		if (!eletree_setInfo (pele, cad)){ /*Asignamos al EleTree la cadena guardada*/
			fclose(f);
			tree_free(tree);
			eletree_free(pele);
			cadena_free(cad);
			return -1;
		}
		tree_insert (tree, pele); /*Insertamos el EleTree en el árbol*/
		eletree_free(pele);
		cadena_free(cad);
	}
	numnodos = tree_numNodes (tree);
	profundidad = tree_depth (tree);
	printf ("Número de nodos: %d\n", numnodos);
	printf ("Profundidad: %d\n", profundidad);
	if(tree_inOrder(stdout, tree) == ERROR){
		fclose (f);
		tree_free(tree);
		return -1;
	}
	printf ("Introduce una cadena para buscar en el árbol (siguiendo el mismo formato que en el fichero de entrada): ");
	scanf ("%s", buscar);
	pele = eletree_ini(); /*Inicializamos un EleTree*/
	if (!pele){
		fclose (f);
		tree_free(tree);
		return -1;
	}
	cad = cadena_ini(); /*Inicializamos una cadena*/
	if(!cad){
		fclose (f);
		tree_free(tree);
		eletree_free(pele);
		return -1;		
	}
	if(!cadena_setInfo(cad, buscar)){
		fclose(f);
		tree_free(tree);
		eletree_free(pele);
		cadena_free(cad);
		return -1;
	}
	if (!eletree_setInfo(pele, cad)){ /*Asignamos al EleTree la cadena "buscar"*/
		fclose (f);
		tree_free(tree);
		eletree_free(pele);
		return -1;
	}
	if (tree_findEleTree (tree, pele) == TRUE){ /*Buscamos en el árbol el entero introducido previamente*/
		printf ("El dato %s se encuentra dentro del árbol\n", buscar);
	}
	else {
		printf ("El dato %s NO se encuentra dentro del árbol\n", buscar);
	}
	tree_free(tree); /*Liberamos toda la memoria*/
	eletree_free(pele);
	fclose (f);
	cadena_free(cad);
	return -1;
}