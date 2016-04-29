/* 
 * File:   p3_e3.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 01 de abril de 2016, 22:23
 */
#include <stdio.h>
#include "solve_mazes.h"
#include "maze.h"

int main(int argc, char *argv[]){
	
	const Move strats[][4]={{RIGHT, LEFT, UP, DOWN},
						   {DOWN, RIGHT, LEFT, UP},
						   {UP, DOWN, RIGHT, LEFT},
						   {LEFT, UP, DOWN, RIGHT}};
	int num_strategies = 4;

	if(argc != 2){
		printf("Faltan argumentos\n");
		return -1;
	}
	
	mazesolver_run(argv[1], strats, num_strategies);
	return 0;
}