/* 
 * File:   cadena.h
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 29 de abril de 2016, 11:23
 */

#ifndef POINT_H
#define	POINT_H

#include "types.h"
#include <stdio.h>


typedef struct _Cadena Cadena;

/* Reserva memoria para una cadena */
Cadena * cadena_ini();

/* Libera la cadena */
void cadena_free(Cadena *pcadena);

/* Obtiene la cadena guardada como char* */
char* cadena_getInfo(Cadena *pcadena);

/* Asigna la cadena info al TAD cadena */
Cadena * cadena_setInfo(Cadena * pcadena, char* info);

/* Copia una cadena, reservando memoria */
Cadena * cadena_copy(const Cadena * src);

/* Imprime una cadena p en el fichero pf, devolviendo el número de caracteres impresos */
int cadena_print(FILE *pf, const Cadena *p);

/* Compara p1 con p2 devolviendo un número negativo, cero o positivo según si p1 es menor, igual o mayor
que p2 */
int cadena_cmp(const Cadena * p1, const Cadena * p2);

#endif	/* POINT_H */