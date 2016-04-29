/* 
 * File:   elelist-int.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 3 de abril de 2016, 18:38
 */

#include <stdio.h>
#include <stdlib.h>
#include "elelist.h"

struct _EleList{
	int *info;
};

/*Inicializa un elemento de la lista.*/
EleList * elelist_ini(){
	EleList *pint = NULL;
	pint = (EleList *)malloc(sizeof(EleList));
	if(!pint){
		return NULL;
	}
	pint->info = (int *)malloc(sizeof(int));
	if(!pint->info){
		free(pint);
		return NULL;
	}
	*(pint->info) = 0;

	return pint;
}

/*libera un elemento de lista*/
void elelist_free(EleList *pint){
	if(!pint){
		return;
	}
	free(pint->info);
	free(pint);
	return;
}

/*Modifica los datos de un elemento*/
EleList * elelist_setInfo(EleList *pint, void *pvoid){
	if(!pint || !pvoid){
		return NULL;
	}
	if(pint->info){
		free(pint->info);
	}
	pint->info = (int *)pvoid;
	return pint;
}

/*Devuelve el puntero a entero almacenado en la estructura*/
void * elelist_getInfo(EleList *pint){
	if (!pint){
		return NULL;
	}
	return (void *)pint->info;
}

/*Copia un elemento en otro, reservando memoria*/
EleList * elelist_copy(const EleList *pint1){
	EleList *pint2 = NULL;
	int *info1 = NULL;
	int *info2 = NULL;
	if(!pint1 || !pint1->info){
		return NULL;
	}
	pint2 = elelist_ini();
    if(!pint2){
        return NULL;
    }
    info1 = (int *)elelist_getInfo((EleList *)pint1);
    if(!info1){
    	elelist_free(pint2);
    	return NULL;
    }
    info2 = (int *)malloc(sizeof(int));
    if(!info2){
    	elelist_free(pint2);
    	return NULL;
    }
    *info2 = *info1;
    if(!elelist_setInfo(pint2, info2)){
    	free(info2);
    	elelist_free(pint2);
    }
	return pint2;
}
/*Compara dos elementos*/
int elelist_cmp(const EleList *pint1, const EleList *pint2){
	if(!pint1 || !pint2 || !pint1->info || !pint2->info){
		return 0;
	}
	return (*(pint1->info) - *(pint2->info));
}
 /*Imprime el contenido de un elemento*/
int elelist_print(FILE *f, const EleList *pint){
	int aImprimir, impreso;
	int *entero;
	if(!f || !pint || !pint->info){
		return -1;
	}
	entero = (int*)elelist_getInfo((EleList*)pint);
	aImprimir = *entero;
	impreso = fprintf(f, "[%d]\n", aImprimir);
	return impreso;
}