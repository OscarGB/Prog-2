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

#define ERRORCHAR 'E'

#define INPUT 'i'
#define OUTPUT 'o'
#define BARRIER '+'
#define SPACE ' '
/*----------------------------------------------------------------------------------------------------------------------
 * Inicializa un punto, reservando memoria y devolviendo el punto inicializado si lo ha hecho correctamente o NULL si no
 ----------------------------------------------------------------------------------------------------------------------*/
Point * point_ini();
/*---------------------------------------------------
 * Libera la memoria dinámica reservada para un punto
 ---------------------------------------------------*/
void point_free(Point *ppoint);
/*--------------------------------------------------------------------------
 * Devuelve la coordenada X de un punto dado, o -1 si se produce algún error 
 --------------------------------------------------------------------------*/
int point_getCoordinateX(const Point *ppoint);
/*--------------------------------------------------------------------------
 * Devuelve la coordenada Y de un punto dado, o -1 si se produce algún error
 --------------------------------------------------------------------------*/
int point_getCoordinateY(const Point *ppoint);
/*----------------------------------------------------------------------------
 * Devuelve el símbolo de un punto dado, o ERRORCHAR si se produce algún error
 ----------------------------------------------------------------------------*/
char point_getSymbol(const Point *ppoint);
/*----------------------------------------------------------------------------------
 * Modifica la coordenda X de un punto dado, devuelve NULL si se produce algún error
 ----------------------------------------------------------------------------------*/
Point * point_setCoordinateX(Point *ppoint, const int x);
/*----------------------------------------------------------------------------------
 * Modifica la coordenda Y de un punto dado, devuelve NULL si se produce algún error
 ----------------------------------------------------------------------------------*/
Point * point_setCoordinateY(Point *ppoint, const int y);
/*------------------------------------------------------------------------------
 * Modifica el símbolo de un punto dado, devuelve NULL si se produce algún error
 -------------------------------------------------------------------------------*/
Point * point_setSymbol(Point *ppoint, const char s);
/*--------------------------------------------------------------------------------------------------
 * Devuelve TRUE si los dos puntos pasados como argumentos son iguales (revisando todos sus campos).
 * Devuelve FALSE en otro caso.
 ---------------------------------------------------------------------------------------------------*/
Bool point_equals(const Point *ppoint1, const Point *ppoint2);
/*----------------------------------------------------------------------------------------------------------------
 * Copia los datos de un punto a otro devolviendo el punto copiado (incluyendo la reserva de la memoria necesaria)
 * si todo ha ido bien, o NULL en otro caso
 -----------------------------------------------------------------------------------------------------------------*/
Point * point_copy(const Point *ppoint);
/*---------------------------------------------------------------------------------------------------------------- 
 * Imprime en un fichero dado los datos de un punto con el siguiente formato: [(x,y): symbol]. Por ejemplo, un
 * punto con símbolo “*”, con coordenada X 3 e Y 7 se representará como [(3, 7): *]. Además devolverá el número de
 * caracteres que se han escrito con éxito (mirar documentación de fprintf)
 -----------------------------------------------------------------------------------------------------------------*/
int point_print(FILE *f, const Point *ppoint); 

#endif	/* POINT_H */