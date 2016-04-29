
/* 
 * File:   elequeue-point.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 8 de marzo de 2016, 13:11
 */

#include <stdio.h>
#include <stdlib.h>
#include "elequeue.h"
#include "point.h"

struct _EleQueue { 
	Point *point; 
};
/*Inicializa un elemento de la cola y todos sus elementos*/
EleQueue * elequeue_ini(){
	EleQueue *pele = NULL;
	pele = (EleQueue *)malloc(sizeof(EleQueue));
	if(!pele){
		return NULL;
	}
	pele->point = point_ini();
	if (!pele->point){
		free (pele);
		return NULL;
	}
	return pele;
}

/*Libera un elemento y todos sus elementos*/
void elequeue_free(EleQueue *pele){
	if(!pele){
		return;
	}
	point_free(pele->point);
	free(pele);
	return;
}

/*Modifica los datos de un elemento*/
EleQueue * elequeue_setInfo(EleQueue *pele, void *pvoid){
	if(!pele || !pvoid){
		return NULL;
	}
	if(pele->point){
		point_free(pele->point);
	}
	pele->point = point_copy((Point *)pvoid);
	if(!pele->point){
		return NULL;
	}
	return pele;
}

/*Devuelve el puntero a punto almacenado en la estructura*/
void * elequeue_getInfo(EleQueue *pele){
	if (!pele){
		return NULL;
	}
	return (void *)pele->point;
}

/*Copia un elemento en otro, reservando memoria*/
EleQueue * elequeue_copy(const EleQueue *pele1){
	EleQueue *pele2 = NULL;
	if(!pele1){
		return NULL;
	}
	pele2 = elequeue_ini();
    if(!pele2){
        return NULL;
    }
	if(!elequeue_setInfo(pele2, pele1->point)){
		elequeue_free(pele2);
	}
	return pele2;
}

/*Devuelve un número positivo, negativo o cero según si pele1 es mayor, menor o igual que pele2 (respectivamente)*/
int elequeue_cmp(const EleQueue * pele1, const EleQueue * pele2){
	int aux;
	EleQueue *copia1 = NULL;
	EleQueue *copia2 = NULL;
	if (!pele1 || !pele2){
		return -1;
	}
	copia1 = elequeue_copy (pele1);
	if (!copia1){
		return -1;
	}
	copia2 = elequeue_copy (pele2);
	if (!copia2){
		elequeue_free (copia1);
		return -1;
	}


	aux = point_getCoordinateX ((Point *)elequeue_getInfo(copia1)) - point_getCoordinateX ((Point *)elequeue_getInfo(copia2));
	if (aux != 0){
		return aux;
	}
	aux = point_getCoordinateY ((Point *)elequeue_getInfo(copia1)) - point_getCoordinateY ((Point *)elequeue_getInfo(copia2));
	if (aux != 0){
		return aux;
	}
	aux = point_getSymbol ((Point *)elequeue_getInfo(copia1)) - point_getSymbol ((Point *)elequeue_getInfo(copia2));
	return aux;

}

/*Imprime un elemento y devuelve el número de caractéres escritos*/
int elequeue_print(FILE *f, const EleQueue *pele){
	if(!f || !pele){
		return -1;
	}
	return point_print (f, pele->point);
}