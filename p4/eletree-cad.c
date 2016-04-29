/* 
 * File:   eletree-cad.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 19 de abril de 2016, 20:48
 */

#include <stdio.h>
#include <stdlib.h>
#include "eletree.h"
#include "cadena.h"

struct _EleTree{
 	Cadena *info;
};

/*Inicializa un EleTree, reservando memoria*/
EleTree * eletree_ini(){
	EleTree *pe = NULL;
	pe = (EleTree *)malloc(sizeof(EleTree));
	if(!pe){
		return NULL;
	}
	pe->info = NULL;
	
	return pe;
}

/*Libera un EleTree*/
void eletree_free(EleTree *pe){
	if(!pe){
		return;
	}
	cadena_free(pe->info);
	free(pe);
	return;
}

/*Modifica los datos de un EleTree*/
EleTree * eletree_setInfo(EleTree *pe, void *pvoid){
	if(!pe || !pvoid){
		return NULL;
	}
	if(pe->info){
		cadena_free(pe->info);
	}
	pe->info = cadena_copy((Cadena *)pvoid);
	if(!pe->info){
		return NULL;
	}
	
	return pe;
}

/*Devuelve los datos de un EleTree*/
void * eletree_getInfo(const EleTree *pe){
	if (!pe){
		return NULL;
	}
	return (void *)pe->info;
}

/*Copia un EleTree, reservando memoria para la copia*/
EleTree * eletree_copy(const EleTree *pe1){
	EleTree *pe2 = NULL;
	Cadena *info1 = NULL;
	if(!pe1 || !pe1->info){
		return NULL;
	}
	pe2 = eletree_ini();
    if(!pe2){
        return NULL;
    }
    info1 = (Cadena *)eletree_getInfo((EleTree *)pe1);
    if(!info1){
    	eletree_free(pe2);
    	return NULL;
    }

    if(!eletree_setInfo(pe2, (void *)info1)){
    	eletree_free(pe2);
    	return NULL;
    }
	return pe2;
}
/*Compara dos EleTree’s devolviendo un número negativo, cero o positivo según si pe1 es menor, igual o mayor que pe2, respectivamente*/
int eletree_cmp(const EleTree *pe1, const EleTree *pe2){
	if(!pe1 || !pe2 || !pe1->info || !pe2->info){
		return 0;
	}
	return cadena_cmp(pe1->info, pe2->info);
}
 /*Imprime el contenido de un EleTree, devolviendo el número de caracteres escritos */
int eletree_print(FILE *f, const EleTree *pe){
	if(!f || !pe || !pe->info){
		return -1;
	}
	return cadena_print(f, pe->info);
}