/* 
 * File:   maze.h
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 2 de febrero de 2016, 13:11
 */

#ifndef MAZE_H
#define	MAZE_H

#include "point.h"
#include "types.h"

typedef struct _Maze Maze;
/* Movimientos posibles en un laberinto */
typedef enum {
RIGHT=0, 
UP=1, 
LEFT=2, 
DOWN=3, 
STAY=4
} Move; 
/*------------------------------------------------------------------------------------------------------------------------------
 * Inicializa un laberinto, reservando memoria y devolviendo el laberinto inicializado si lo ha hecho correctamente o NULL si no
-------------------------------------------------------------------------------------------------------------------------------*/
Maze * maze_ini();
/*-------------------------------------------------------
 * Libera la memoria dinámica reservada para un laberinto
 -------------------------------------------------------*/
void maze_free(Maze * );
/*--------------------------------------------------------------------------------
 * Devuelve el número de filas deun laberinto dado, o -1 si se produce algún error
 --------------------------------------------------------------------------------*/
int maze_getNrows(const Maze * );
/*------------------------------------------------------------------------------------
 * Devuelve el número de columnas de un laberinto dado, o -1 si se produce algún error 
 ------------------------------------------------------------------------------------*/
int maze_getNcols(const Maze * );
/*------------------------------------------------------------------------------------
 * Devuelve el punto de entrada en un laberinto dado, o NULL si se produce algún error 
 ------------------------------------------------------------------------------------*/
Point * maze_getInput(const Maze * );
/*-----------------------------------------------------------------------------------
 * Devuelve el punto de salida en un laberinto dado, o NULL si se produce algún error
 -----------------------------------------------------------------------------------*/
Point * maze_getOutput(const Maze * );
/*-----------------------------------------------------------------------------------------------------
 * Devuelve el punto de un laberinto situadoen unas coordenadas dadas, o NULL si se produce algún error
 ------------------------------------------------------------------------------------------------------*/
Point * maze_getPoint(const Maze * , const int x, const int y);
/*--------------------------------------------------------------------------------------------------------------------------------------
 * Devuelve el punto resultante al realizar un movimiento en un laberinto a partir de un punto inicial, o NULL si se produce algún error
 --------------------------------------------------------------------------------------------------------------------------------------*/
Point * maze_getNeighborPoint(const Maze * , const Point *, const Move mov);
/*--------------------------------------------------------------------------
 * Indica el tamaño de un laberinto, devuelve NULL si se produce algún error
 --------------------------------------------------------------------------*/
Maze* maze_setSize(Maze * , int nrow, int ncol);
/*-----------------------------------
 * Añade un punto a un laberinto dado
  ---------------------------------*/
Maze * maze_addPoint(Maze * , const Point* );
/*------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Imprime en un fichero dado los datos de un laberinto. Además devolverá el número de caracteres que se han escrito con éxito (mirar documentación de fprintf)
 ------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int maze_print(FILE *pf, const Maze *pl);
/*--------------------------------------------------------------------------------
 * Lee un laberinto desde fichero localizado en la misma carpeta que el ejecutable
 -------------------------------------------------------------------------------*/
Maze * maze_read(FILE *, Maze * );

#endif	/* MAZE_H */