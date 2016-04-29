/* 
 * File:   solution.h
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 15 de abril de 2016, 22:48
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include "maze.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _Solution Solution;

typedef enum {
	COLA = 0, PILA = 1, NADA = 2
} Tipo;

Solution* solution_ini();

void solution_free(Solution *sol);

int solution_print(FILE *f, const Solution *sol);

Solution* solution_copy(Solution *sol);

Solution* solution_setType(Solution *sol, const Tipo type);

Solution* solution_setStrat(Solution *sol, const Move strat[4]);

Solution* solution_setPasos(Solution *sol, const int pasos);

int solution_getPasos(Solution *sol);

#endif /*SOLUTION_H*/