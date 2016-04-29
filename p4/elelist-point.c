/* 
 * File:   elelist-point.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 26 de abril de 2016, 12:43
 */

#include <stdio.h>
#include <stdlib.h>
#include "elelist.h"
#include "point.h"

struct _EleList{
 	Point *info;
};

/*Inicializa un EleList, reservando memoria*/
EleList * elelist_ini(){
	EleList *pe = NULL;
	pe = (EleList *)malloc(sizeof(EleList));
	if(!pe){
		return NULL;
	}
	pe->info = NULL;
	
	return pe;
}

/*Libera un EleList*/
void elelist_free(EleList *pe){
	if(!pe){
		return;
	}
	point_free(pe->info);
	free(pe);
	return;
}

/*Modifica los datos de un EleList*/
EleList * elelist_setInfo(EleList *pe, void *pvoid){
	if(!pe || !pvoid){
		return NULL;
	}
	if(pe->info){
		point_free(pe->info);
	}
	pe->info = point_copy((Point *)pvoid);
	if(!pe->info){
		return NULL;
	}
	
	return pe;
}

/*Devuelve los datos de un EleList*/
void * elelist_getInfo(EleList *pe){
	if (!pe){
		return NULL;
	}
	return (void *)pe->info;
}

/*Copia un EleList, reservando memoria para la copia*/
EleList * elelist_copy(const EleList *pe1){
	EleList *pe2 = NULL;
	Point *info1 = NULL;
	if(!pe1 || !pe1->info){
		return NULL;
	}
	pe2 = elelist_ini();
    if(!pe2){
        return NULL;
    }
    info1 = (Point *)elelist_getInfo((EleList *)pe1);
    if(!info1){
    	elelist_free(pe2);
    	return NULL;
    }

    if(!elelist_setInfo(pe2, (void *)info1)){
    	elelist_free(pe2);
    	return NULL;
    }
	return pe2;
}
/*Compara dos EleList’s devolviendo un número negativo, cero o positivo según si pe1 es menor, igual o mayor que pe2, respectivamente*/
int elelist_cmp(const EleList *pe1, const EleList *pe2){
	if(!pe1 || !pe2 || !pe1->info || !pe2->info){
		return 0;
	}
	return point_cmp(pe1->info, pe2->info);
}
 /*Imprime el contenido de un EleList, devolviendo el número de caracteres escritos */
int elelist_print(FILE *f, const EleList *pe){
	if(!f || !pe || !pe->info){
		return -1;
	}
	return point_print(f, pe->info);
}