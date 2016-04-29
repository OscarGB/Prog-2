/* 
 * File:   cadena.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 29 de abril de 2016, 11:23
 */

#include <stdio.h>
#include <string.h>
#include "cadena.h"
#include <stdlib.h>

struct _Cadena {
    char *info;
};

/* Reserva memoria para una cadena */
Cadena * cadena_ini(){
	Cadena *cad;
	cad = (Cadena *)malloc(sizeof(Cadena));
	if(!cad){
		return NULL;
	}
	cad->info = NULL;
	return cad;
}

/* Libera la cadena */
void cadena_free(Cadena *pcadena){
	if(pcadena){
		if(pcadena->info){
			free(pcadena->info);
		}
		free(pcadena);
	}
	return;
}

/* Obtiene la cadena guardada como char* */
char* cadena_getInfo(Cadena *pcadena){
	if(!pcadena || !pcadena->info){
		return NULL;
	}
	return pcadena->info;
}

/* Asigna la cadena info al TAD cadena */
Cadena * cadena_setInfo(Cadena * pcadena, char* info){
	char *setinfo;
	int len;
	if(!pcadena || !info){
		return NULL;
	}
	len = strlen(info);
	setinfo = (char *)malloc((len + 1)*sizeof(char));
	if(!setinfo){
		return NULL;
	}
	if(!strcpy (setinfo, info)){
		free(setinfo);
		return NULL;
	}
	if(pcadena->info){
		free(pcadena->info);
	}
	pcadena->info = setinfo;
	return pcadena;
}

/* Copia una cadena, reservando memoria */
Cadena * cadena_copy(const Cadena *src){
	Cadena* cad = NULL;
	if(!src){
		return NULL;
	}
	cad = cadena_ini();
	if(!cad){
		return NULL;
	}
	if(!cadena_setInfo(cad, cadena_getInfo((Cadena*)src))){
		cadena_free(cad);
		return NULL;
	}
	return cad;

}

/* Imprime una cadena p en el fichero pf, devolviendo el número de caracteres impresos */
int cadena_print(FILE *pf, const Cadena *p){
	if(!pf || !p || !p->info){
		return -1;
	}
	return fprintf(pf, "%s\n", p->info);
}

/* Compara p1 con p2 devolviendo un número negativo, cero o positivo según si p1 es menor, igual o mayor
que p2 */
int cadena_cmp(const Cadena * p1, const Cadena * p2){
	if(!p1 || !p1->info || !p2 || !p2->info){
		return -31416;
	}
	return strcmp(p1->info, p2->info);
}
