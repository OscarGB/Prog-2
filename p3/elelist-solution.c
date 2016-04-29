/* 
 * File:   elelist-solution.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 3 de abril de 2016, 18:38
 */

#include <stdio.h>
#include <stdlib.h>
#include "elelist.h"
#include "solution.h"

struct _EleList{
	Solution *info;
};

/*Inicializa un elemento de la lista.*/
EleList * elelist_ini(){
	EleList *pele = NULL;
	pele = (EleList *)malloc(sizeof(EleList));
	if(!pele){
		return NULL;
	}
	pele->info = solution_ini();
	if(!pele->info){
		free(pele);
		return NULL;
	}
	return pele;
}

/*libera un elemento de lista*/
void elelist_free(EleList *pele){
	if(!pele){
		return;
	}
	solution_free(pele->info);
	free(pele);
	return;
}

/*Modifica los datos de un elemento*/
EleList * elelist_setInfo(EleList *pele, void *pvoid){
	if(!pele || !pvoid){
		return NULL;
	}
	if(pele->info){
		solution_free(pele->info);
	}
	pele->info = (Solution *)pvoid;
	return pele;
}

/*Devuelve el puntero a entero almacenado en la estructura*/
void * elelist_getInfo(EleList *pele){
	if (!pele){
		return NULL;
	}
	return (void *)pele->info;
}

/*Copia un elemento en otro, reservando memoria*/
EleList * elelist_copy(const EleList *pele1){
	EleList *pele2 = NULL;
	Solution *info1 = NULL;
	Solution *info2 = NULL;
	if(!pele1 || !pele1->info){
		return NULL;
	}
	pele2 = elelist_ini();
    if(!pele2){
        return NULL;
    }
    info1 = (Solution *)elelist_getInfo((EleList *)pele1);
    if(!info1){
    	elelist_free(pele2);
    	return NULL;
    }
    info2 = solution_copy(info1);
    if(!info2){
    	elelist_free(pele2);
    	return NULL;
    }
    if(!elelist_setInfo(pele2, info2)){
    	free(info2);
    	elelist_free(pele2);
    }
	return pele2;
}
/*Compara dos elementos*/
int elelist_cmp(const EleList *pele1, const EleList *pele2){
	if(!pele1 || !pele2 || !pele1->info || !pele2->info){
		return 0;
	}
	return (solution_getPasos((Solution *)elelist_getInfo((EleList *)pele1)) - solution_getPasos((Solution *)elelist_getInfo((EleList *)pele2)));
}
 /*Imprime el contenido de un elemento*/
int elelist_print(FILE *f, const EleList *pele){
	if(!f || !pele || !pele->info){
		return -1;
	}
	return solution_print(f, elelist_getInfo((EleList *)pele));
}