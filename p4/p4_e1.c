/* 
 * File:   p4_e1.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 19 de abril de 2016, 13:35
 */

#include <stdio.h>
#include <stdlib.h>
#include "eletree.h"
#include "types.h"
#include "tree.h"
#include <string.h>
#include "list.h"


int main (int argc, char *argv[]){
	List *lista = NULL;
	FILE *f = NULL;
	Tree *tree = NULL;
	EleTree *pele = NULL;
	int entero, buscar, numnodos, profundidad;


	if(argc != 2){ /*Comprobamos argumentos*/
	printf("Faltan argumentos\n");
	return -1;
	}

	f = fopen (argv[1], "r"); /*Abrimos el fichero recibido como argumento*/
	if (!f){
		return -1;
	}

	tree = tree_ini(); /*Inicializamos el árbol en el que vamos a guardar los números*/
	if (!tree){
		fclose(f);
		return -1;
	}

	while (feof(f) == 0){ /*Bucle que lee uno a uno los enteros del fichero*/
		fscanf (f, "%d", &entero); /*Guardamos el dato leido en entero*/
		pele = eletree_ini(); /*Inicializamos un EleTree*/
		if (!pele){
			fclose(f);
			tree_free(tree);
			return -1;
		}
		if (!eletree_setInfo (pele, &entero)){ /*Asignamos al EleTree la dirección al entero guardado*/
			fclose(f);
			tree_free(tree);
			eletree_free(pele);
			return -1;
		}
		tree_insert (tree, pele); /*Insertamos el EleTree en el árbol*/
		eletree_free(pele);
	}
	numnodos = tree_numNodes (tree);
	profundidad = tree_depth (tree);
	printf ("Número de nodos: %d\n", numnodos);
	printf ("Profundidad: %d\n", profundidad);

	/*Cambios requeridos para el ejercicio p4_e3*/

	if (strcmp("./p4_e3", argv[0]) == 0) {
		printf ("Orden previo: ");
		if (tree_preOrder (stdout, tree) == ERROR){ /*Imprimimos el árbol en orden previo*/
			fclose (f);
			tree_free(tree);
			return -1;
		}
		printf ("\nOrden medio: ");
		if (tree_inOrder (stdout, tree) == ERROR){ /*Imprimimos el árbol en orden medio*/
			fclose (f);
			tree_free(tree);
			return -1;
		}
		printf ("\nOrden posterior: ");
		if (tree_postOrder (stdout, tree) == ERROR){ /*Imprimimos el árbol en orden posterior*/
			fclose (f);
			tree_free(tree);
			return -1;
		}
		printf("\nOrden previo con lista:\n");
		lista = list_ini(); /*Inicializamos la lista*/
		if(!lista){
			fclose (f);
			tree_free(tree);
			return -1;
		}
		if(tree_preOrderToList(lista, tree) == ERROR){ /*Introducimos el arbol en la lista en orden previo*/
			fclose (f);
			tree_free(tree);
			list_free(lista);
			return -1;
		} 
		if(list_print(stdout, lista) < 0){ /*Imprimimos la lista*/
			fclose (f);
			tree_free(tree);
			list_free(lista);
			return -1;
		}
		list_free(lista);
		printf("Orden medio con lista:\n");
		lista = list_ini(); /*Inicializamos la lista*/
		if(!lista){
			fclose (f);
			tree_free(tree);
			return -1;
		}
		if(tree_inOrderToList(lista, tree) == ERROR){ /*Introducimos el arbol en la lista en orden medio*/
			fclose (f);
			tree_free(tree);
			list_free(lista);
			return -1;
		} 
		if(list_print(stdout, lista) < 0){ /*Imprimimos la lista*/
			fclose (f);
			tree_free(tree);
			list_free(lista);
			return -1;
		}
		list_free(lista);
		printf("Orden posterior con lista:\n");
		lista = list_ini(); /*Inicializamos la lista*/
		if(!lista){
			fclose (f);
			tree_free(tree);
			return -1;
		}
		if(tree_postOrderToList(lista, tree) == ERROR){ /*Introducimos el arbol en la lista en orden posterior*/
			fclose (f);
			tree_free(tree);
			list_free(lista);
			return -1;
		} 
		if(list_print(stdout, lista) < 0){ /*Imprimimos la lista*/
			fclose (f);
			tree_free(tree);
			list_free(lista);
			return -1;
		}
		list_free(lista);
	}

	printf ("Introduzca un número: ");
	scanf ("%d", &buscar);
	pele = eletree_ini(); /*Inicializamos un EleTree*/
	if (!pele){
		fclose (f);
		tree_free(tree);
		return -1;
	}
	if (!eletree_setInfo(pele, &buscar)){ /*Asignamos al EleTree la dirección del entero buscar*/
		fclose (f);
		tree_free(tree);
		eletree_free(pele);
		return -1;
	}
	if (tree_findEleTree (tree, pele) == TRUE){ /*Buscamos en el árbol el entero introducido previamente*/
		printf ("El dato %d se encuentra dentro del árbol\n", buscar);
	}
	else {
		printf ("El dato %d NO se encuentra dentro del árbol\n", buscar);
	}
	tree_free(tree); /*Liberamos memoria*/
	eletree_free(pele);
	fclose (f);
	return -1;
}