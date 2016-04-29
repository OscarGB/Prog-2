
/* 
 * File:   p1_e2.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 10 de febrero de 2016, 13:11
 */

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "point.h"
#include "types.h"


int main(){
	FILE *f=NULL;
	Maze *pmaze = NULL;
    pmaze = maze_ini();
	f=fopen("maze.txt", "r");
	if(!f){
		printf("Error en la apertura de fichero maze");
		return -1;
	}
	if(!maze_read(f, pmaze)){
		maze_free(pmaze);
		printf("Error en la lectura del fichero maze");
		return -1;
	}
	fclose(f);
	f=fopen("maze2.txt", "w");
	if(!f){
		maze_free(pmaze);
		printf("Error en la apertura de fichero maze2");
		return -1;
	}
	if((maze_print(f, pmaze))<0){
		printf("Error en la escritura de fichero maze2");
		maze_free(pmaze);
		return -1;
	}
        maze_free(pmaze);
	fclose(f);
	return 0;
}