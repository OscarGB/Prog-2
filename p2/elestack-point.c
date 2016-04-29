/* 
 * File:  elesatck-point.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 23 de febrero de 2016, 12:35
 */

#include <stdio.h>
#include <stdlib.h>
#include "elestack.h"
#include "point.h"

struct _EleStack { 
	Point *point; 
};
/*Inicializa un elemento de pila.*/
EleStack * elestack_ini(){
	EleStack *ppoint = NULL;
	ppoint = (EleStack *)malloc(sizeof(EleStack));
	if(!ppoint){
		return NULL;
	}
	ppoint->point = NULL;
	return ppoint;
}

/*libera un elemento*/
void elestack_free(EleStack *ppoint){
	if(!ppoint){
		return;
	}
	point_free(ppoint->point);
	free(ppoint);
	return;
}

/*Modifica los datos de un elemento*/
EleStack * elestack_setInfo(EleStack *ppoint, void *pvoid){
	if(!ppoint || !pvoid){
		return NULL;
	}
	if(ppoint->point){
		point_free(ppoint->point);
	}
	ppoint->point = point_copy((Point *)pvoid);
	if(!ppoint->point){
		return NULL;
	}
	return ppoint;
}

/*Devuelve el puntero a punto almacenado en la estructura*/
void * elestack_getInfo(EleStack *ppoint){
	if (!ppoint){
		return NULL;
	}
	return (void *)ppoint->point;
}

/*Copia un elemento en otro, reservando memoria*/
EleStack * elestack_copy(const EleStack *ppoint1){
	EleStack *ppoint2 = NULL;
	if(!ppoint1 || !ppoint1->point){
		return NULL;
	}
	ppoint2 = elestack_ini();
        if(!ppoint2){
            return NULL;
        }
        ppoint2->point = point_copy (ppoint1->point);
	if(!ppoint2->point){
		elestack_free(ppoint2);
		return NULL;
	}
	return ppoint2;
}
/*Compara dos elementos*/
Bool elestack_equals(const EleStack *ppoint1, const EleStack *ppoint2){
	if(!ppoint1 || !ppoint2 || !ppoint1->point || !ppoint2->point){
		return FALSE;
	}
	if(point_equals (ppoint1->point, ppoint2->point)){
		return TRUE;
	}
	return FALSE;
}

int elestack_print(FILE *f, const EleStack *ppoint){
	if(!f || !ppoint){
		return -1;
	}
	return point_print (f, ppoint->point);
}