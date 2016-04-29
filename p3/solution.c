/* 
 * File:   solution.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 15 de abril de 2016, 22:43
 */

#include <stdio.h>
#include <stdlib.h>
#include "solution.h"
#include "maze.h"

struct _Solution{
	Tipo type;
	Move strat[4];
	int pasos;
};

Solution* solution_ini(){
	Solution *sol = NULL;
	int i;
	sol = (Solution *)malloc(sizeof(Solution));
	if(!sol){
		return NULL;
	}
	sol->type = NADA;
	for(i=0; i<4; i++){
		sol->strat[i] = STAY;
	}
	sol->pasos = -1;
	return sol;
}

void solution_free(Solution *sol){
	if(sol){
		free(sol);
	}
	return;
}

int solution_print(FILE *f, const Solution *sol){
	int contador = 0;
	if(!sol){
		return -1;
	}
	contador = fprintf(f, "[%d%d%d%d, ", sol->strat[0], sol->strat[1], sol->strat[2], sol->strat[3]);
	if(sol->type == PILA){
		contador += fprintf(f, "pila, ");
	}else if(sol->type == COLA){
		contador += fprintf(f, "cola, ");
	}else{ 
		contador += fprintf(f, "nada, ");
	}
	contador += fprintf(f, "%d]\n", sol->pasos);
	return contador;
}

Solution* solution_copy(Solution *sol){
	int i;
	Solution *copy = NULL;
	if(!sol){
		return NULL;
	}
	copy = solution_ini();
	if(!copy){
		return NULL;
	}
	copy->type = sol->type;
	for(i=0; i<4; i++){
		copy->strat[i] = sol->strat[i];
	}
	copy->pasos = sol->pasos;
	return copy;
}

Solution* solution_setType(Solution *sol, const Tipo type){
	if(!sol){
		return NULL;
	}
	if(type != COLA && type != PILA){
		return NULL;
	}
	sol->type = type;
	return sol;
}

Solution* solution_setStrat(Solution *sol, const Move strat[4]){
	int i;
	if(!sol){
		return NULL;
	}
	for(i=0; i<4; i++){
		if(strat[i] == STAY){
			return NULL;
		}
	}
	for(i=0; i<4; i++){
		sol->strat[i] = strat[i];
	}
	return sol;
}

Solution* solution_setPasos(Solution *sol, const int pasos){
	if(!sol || pasos < 0){
		return NULL;
	}
	sol->pasos = pasos;
	return sol;
}

int solution_getPasos(Solution *sol){
	if(!sol){
		return -1;
	}
	return sol->pasos;
}