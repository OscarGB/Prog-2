/* 
 * File:   solve_mazes.h
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 01 de abril de 2016, 13:15
 */

#ifndef SOLVES_MAZES_H
#define SOLVES_MAZES_H

 #include "maze.h"
 #include <stdio.h>

/*Resuelve el laberinto con una pila y devuelve el número de pasos que ha realizado*/
int mazesolver_stack(const char* maze_file, const Move strat[4]);

/*Resuelve el laberinto con una cola y devuelve el número de pasos que ha realizado*/
int mazesolver_queue(const char* maze_file, const Move strat[4]);

/*Función que resuelve el laberinto con varias estrategias*/
void mazesolver_run(const char* maze_file, const Move strat[][4], const int num_strategies);

/*Resuelve y guarda en listas las soluciones*/
void mazesolver_runSolution(const char* maze_file, const Move strat[][4], const int num_strategies);

#endif /*SOLVES_MAZES_H*/