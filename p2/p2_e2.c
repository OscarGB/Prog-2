/* 
 * File:   p2_e2.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 23 de febrero de 2016, 12:56
 */

 #include "stack.h"
 #include "elestack.h"
 #include "maze.h"
 #include "point.h"
 #include "types.h"
 #include <stdio.h>
 #include <stdlib.h>

 int main(int argc, char *argv[]){
 	Maze *pmaze = NULL;
 	FILE *f = NULL;
 	Stack *pila = NULL;
 	EleStack *pele = NULL;
 	Point *ppoint = NULL;
 	int nrow, ncol, i, j;
 	f = fopen(argv[1], "r");
 	if(!f){
 		printf("Error de apertura de fichero");
 		return -1;
 	}
 	pmaze = maze_ini();
 	if(!pmaze){
 		printf("Error reserva pmaze");
 		fclose(f);
 		return -1;
 	}
 	if(!maze_read(f, pmaze)){ /*leemos el laberinto del fichero que se introduce por consola*/
 		fclose(f);
 		printf("Error lectura maze");
 		maze_free(pmaze);
 		return -1;
 	}
 	nrow = maze_getNrows(pmaze);
 	ncol = maze_getNcols(pmaze);
 	if(nrow<0||ncol<0){
 		fclose(f);
 		printf("Error de tamaño");
 		maze_free(pmaze);
 		return -1;
 	}
 	pila = stack_ini();
 	if(!pila){
 		printf("Error reserva pila");
 		fclose(f);
 		maze_free(pmaze);
 		return -1;
 	}
 	pele = elestack_ini();
 	if(!pele){
 		printf("Error reserva elestack");
 		fclose(f);
 		maze_free(pmaze);
 		stack_free(pila);
 		return -1;
 	}
 	for(j=0; j< nrow; j++){
 		for(i=0; i < ncol; i++){
 			ppoint = maze_getPoint(pmaze, i, j);
 			if(!ppoint){
 				printf("Error get point");
 				fclose(f);
		 		maze_free(pmaze);
		 		stack_free(pila);
		 		elestack_free(pele);
		 		return -1;
 			}
 			if(!elestack_setInfo(pele, (void *)ppoint)){
 				fclose(f);
 				printf("Error set info");
		 		maze_free(pmaze);
		 		stack_free(pila);
		 		elestack_free(pele);
		 		return -1;
 			}
 			if(!stack_push(pila, pele)){
 				printf("Eror push");
 				fclose(f);
		 		maze_free(pmaze);
		 		stack_free(pila);
		 		elestack_free(pele);
		 		return -1;
 			}
 		}
 	}
 	stack_print(stdout, pila);
 	fclose(f);
	maze_free(pmaze);
	stack_free(pila);
	elestack_free(pele);
	return 0;
 }