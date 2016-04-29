 /* 
 * File:   point.h
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 2 de febrero de 2016, 13:11
 */

#ifndef POINT_H
#define	POINT_H

#include "types.h"
#include <stdio.h>


typedef struct _Point Point;
/* Reserva memoria para un punto que tenga dim dimensiones */
Point * point_ini(int dim);

/* Libera el punto */
void point_free(Point *ppoint);

/* Obtiene la coordenada dim-ésima de p y la almacena en v, devolviendo OK si todo va bien */
Status point_getCoordinate(const Point * p, const int dim, float * v);

/* Devuelve el nombre almacenado en p */
const char* point_getName(const Point * p);

/* Devuelve el número de dimensiones de p */
int point_getDimensions(const Point * p);

/* Asigna el valor v a la coordenada dim-ésima al punto p */
Point * point_setCoordinate(Point * p, const int dim, const float v);

/* Asigna el nombre name al punto p */
Point * point_setName(Point *p, const char* name);

/* Copia un punto reservando memoria para dicho punto y todos sus atributos, copiando sus valores */
Point * point_copy(const Point * src);

/* Imprime un punto p en el fichero pf, devolviendo el número de caracteres impresos */
int point_print(FILE *pf, const Point *p);

/* Compara p1 con p2 devolviendo un número negativo, cero o positivo según si p1 es menor, igual o mayor
que p2 */
int point_cmp(const Point * p1, const Point * p2);

/***** Necesario a partir de P4_E4 *****/

/* Compara la coordenada dim-ésima de p1 y la de p2 devolviendo un número negativo, cero o positivo según
si p1 es menor, igual o mayor que p2 */
int point_cmpd(const Point * p1, const Point * p2, const int dim);

#endif	/* POINT_H */