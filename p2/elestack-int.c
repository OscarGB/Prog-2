/* 
 * File:   elestack-int.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 19 de febrero de 2016, 17:48
 */


#include <stdio.h>
#include <stdlib.h>
#include "elestack.h"

struct _EleStack { 
	int *info; 
};
/*Inicializa un elemento de pila.*/
EleStack * elestack_ini(){
	EleStack *pint = NULL;
	pint = (EleStack *)malloc(sizeof(EleStack));
	if(!pint){
		return NULL;
	}
	pint->info = NULL;
	return pint;
}

/*libera un elemento*/
void elestack_free(EleStack *pint){
	if(!pint){
		return;
	}
	free(pint->info);
	free(pint);
	return;
}

/*Modifica los datos de un elemento*/
EleStack * elestack_setInfo(EleStack *pint, void *pvoid){
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
void * elestack_getInfo(EleStack *pint){
	if (!pint){
		return NULL;
	}
	return (void *)pint->info;
}

/*Copia un elemento en otro, reservando memoria*/
EleStack * elestack_copy(const EleStack *pint1){
	EleStack *pint2 = NULL;
	if(!pint1 || !pint1->info){
		return NULL;
	}
	pint2 = elestack_ini();
        if(!pint2){
            return NULL;
        }
	pint2->info = (int *)malloc(sizeof(int));
	if(!pint2->info){
		elestack_free(pint2);
		return NULL;
	}
	*(pint2->info) = *(pint1->info);
	return pint2;
}
/*Compara dos elementos*/
Bool elestack_equals(const EleStack *pint1, const EleStack *pint2){
	if(!pint1 || !pint2 || !pint1->info || !pint2->info){
		return FALSE;
	}
	if(*(pint1->info)==*(pint2->info)){
		return TRUE;
	}
	return FALSE;
}

int elestack_print(FILE *f, const EleStack *pint){
	if(!f || !pint){
		return -1;
	}
	return fprintf(f, "[%d]", pint->info[0]);
}