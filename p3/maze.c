/* 
 * File:   maze.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 10 de febrero de 2016, 13:11
 */

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

#define MAX 4096


struct _Maze{
	Point ***ppoint;
	int ncol;
	int nrow;
};

/*Inicializa un laberinto, pero no inicializa los puntos ni define su tamaño*/
Maze * maze_ini(){
	Maze *pmaze=NULL;
	pmaze=(Maze*)malloc(sizeof(Maze));
	if(!pmaze){
		return NULL;
	}
	pmaze->ncol = -1;
	pmaze->nrow = -1;
	pmaze->ppoint = NULL;
	return pmaze;
}


/*Establece el tamaño del laberinto y reserva la memoria para el mismo*/
Maze* maze_setSize(Maze *pmaze, int nrow, int ncol){

	int i, j;

	if(!pmaze){
		return NULL;
	}
	if(pmaze->ppoint){
		return NULL;
	}
	if((nrow*ncol)>MAX){
		free(pmaze);
		return NULL;	
	}
	pmaze->ncol = ncol;
	pmaze->nrow = nrow;
	
	pmaze->ppoint = (Point***)malloc(nrow*sizeof(Point**));
	if(!pmaze->ppoint){
		free(pmaze);
		return NULL;
	}
	for (i=0; i<nrow; i++){
		pmaze->ppoint[i] = (Point**)malloc(ncol*sizeof(Point*));
		if(!pmaze->ppoint[i]){
			for (j=0; j<i; j++){
				free(pmaze->ppoint[j]);
			}
			free(pmaze->ppoint);
			free(pmaze);
			return NULL;
		}
	}
	for(i=0;i<(pmaze->nrow);i++){
		for(j=0;j<(pmaze->ncol);j++){
			pmaze->ppoint[i][j] = NULL;
		}
	}
	return pmaze;
}


/* Añade un punto a un laberinto dado*/
Maze *maze_addPoint(Maze *pmaze, const Point *ppoint){
	Point *aux;
	if(!pmaze){
		return NULL;
	}
	if(!ppoint){
		return NULL;
	}
	if(point_getSymbol(ppoint) == ERRORCHAR||(point_getCoordinateX(ppoint)) > pmaze->ncol||(point_getCoordinateX(ppoint)) < 0||(point_getCoordinateY(ppoint)) < 0||(point_getCoordinateY(ppoint)) > pmaze->nrow){
		return NULL;
	}
	aux = point_copy(ppoint);
	if(!aux){
		return NULL;
	}
	pmaze->ppoint[point_getCoordinateY(ppoint)][point_getCoordinateX(ppoint)] = aux;
	return pmaze;
}
 /*libera la memoria de un maze completo, así como de los puntos que tiene en su interior*/
void maze_free(Maze *pmaze){
	int i,j;
	for(i=0;i<(pmaze->nrow);i++){
		for(j=0;j<(pmaze->ncol);j++){
			point_free(pmaze->ppoint[i][j]);
		}
	}
	for(i=0;i<(pmaze->nrow);i++){
		free(pmaze->ppoint[i]);
	}
	free(pmaze->ppoint);
	free(pmaze);
	return;
}

/* Devuelve el número de filas de
un laberinto dado, o -1 si se produce algún error */
int maze_getNrows(const Maze *pmaze){
	if(!pmaze){
		return -1;
	}
	if(!pmaze->ppoint){
		return -1;
	}
	return pmaze->nrow;
}

/* Devuelve el número de columnas de un laberinto dado, o -1 si se produce algún error */
int maze_getNcols(const Maze *pmaze){
	if(!pmaze){
		return -1;
	}
	if(!pmaze->ppoint){
		return -1;
	}
	return pmaze->ncol;
}

Point * maze_getInput(const Maze *pmaze){
	int i, j;
	if(!pmaze){
		return NULL;
	}
	if(!pmaze->ppoint){
		return NULL;
	}
	for(i=0;i<(pmaze->nrow);i++){
		for(j=0;j<(pmaze->ncol);j++){
			if(point_getSymbol(pmaze->ppoint[i][j]) == INPUT){
				return pmaze->ppoint[i][j];
			}
		}
	}
	return NULL;
}

Point * maze_getOutput (const Maze *pmaze){
	int i, j;
	if(!pmaze){
		return NULL;
	}
	if(!pmaze->ppoint){
		return NULL;
	}
	for(i=0;i<(pmaze->nrow);i++){
		for(j=0;j<(pmaze->ncol);j++){
			if(point_getSymbol(pmaze->ppoint[i][j]) == OUTPUT){
				return pmaze->ppoint[i][j];
			}
		}
	}
	return NULL;
}

/* Devuelve el punto de un laberinto situado
en unas coordenadas dadas, o NULL si se produce algún error */
Point * maze_getPoint(const Maze *pmaze, const int x, const int y){
	if(!pmaze){
		return NULL;
	}
	if(!pmaze->ppoint){
		return NULL;
	}
	if(x >= 0 && x < pmaze->ncol && y >= 0 && y < pmaze->nrow){
		return pmaze->ppoint[y][x];
	}
	return NULL;
}

/* Devuelve el punto resultante al realizar un movimiento en un laberinto a partir de un punto inicial, o NULL si se 
produce algún error */
Point * maze_getNeighborPoint(const Maze *pmaze, const Point *ppoint, const Move mov){
	
	if(!pmaze||!ppoint){
		return NULL;
	}
	if(!pmaze->ppoint){
		return NULL;
	}
	if(mov<0||mov>4){
		return NULL;
	}
	if(point_getCoordinateX(ppoint) < 0||point_getCoordinateX(ppoint) >= pmaze->ncol||point_getCoordinateY(ppoint) < 0||point_getCoordinateY(ppoint) >= pmaze->nrow){
		return NULL;
	}
	if(mov == RIGHT){
		if(point_getCoordinateX(ppoint) == ((pmaze->ncol))){
			return NULL;
		}
		return pmaze->ppoint[point_getCoordinateY(ppoint)][(point_getCoordinateX(ppoint))+1];
	}
	if(mov == UP){
		if(point_getCoordinateY(ppoint) == 0){
			return NULL;
		}
		return pmaze->ppoint[(point_getCoordinateY(ppoint))-1][point_getCoordinateX(ppoint)];
	}
	if(mov == LEFT){
		if(point_getCoordinateX(ppoint) == 0){
			return NULL;
		}
		return pmaze->ppoint[point_getCoordinateY(ppoint)][(point_getCoordinateX(ppoint))-1];
	}
	if(mov == DOWN){
		if(point_getCoordinateY(ppoint) == ((pmaze->nrow))){
			return NULL;
		}
		return pmaze->ppoint[(point_getCoordinateY(ppoint))+1][point_getCoordinateX(ppoint)];
	}
	if(mov == STAY){
		return pmaze->ppoint[point_getCoordinateY(ppoint)][point_getCoordinateX(ppoint)];
	}
        return NULL;
}

/* Imprime en un fichero dado los datos de un laberinto. Además devolverá el número de caracteres que se han 
escrito con éxito (mirar documentación de fprintf) */
int maze_print(FILE *f, const Maze * pmaze){
	int numpalabras = 0, i, j;
	if(!f || !pmaze){
		return -1;
	}
	if(!pmaze->ppoint){
		return -1;
	}
	fprintf(f, "%d %d\r\n", pmaze->nrow, pmaze->ncol);
	for(i=0;i<(pmaze->nrow);i++){
		for(j=0;j<(pmaze->ncol);j++){
			numpalabras = numpalabras + fprintf(f, "%c", point_getSymbol(pmaze->ppoint[i][j]));
		}
		fprintf(f,"\r\n");
	}
	return numpalabras;
}

/*Lee un laberinto desde fichero localizado en la misma carpeta que el ejecutable*/
Maze * maze_read(FILE *pf, Maze *pl) {
	char buff[MAX];
	int i, j, nrows, ncols;
	Point *temp;  
	if (pl==NULL || pf==NULL) return NULL;
	/*creamos punto que se utiliza como buffer*/
	temp = point_ini(); 
	if (temp==NULL) return NULL;   
	/* asignamos dimensión al laberinto */
	fgets(buff, MAX, pf);
	sscanf(buff, "%d %d", &nrows, &ncols);
	pl = maze_setSize (pl, nrows, ncols);
	if (pl==NULL) return NULL;    
	/* leemos el fichero linea a linea */
	for(i=0; i < nrows;i++) {
		fgets(buff, MAX, pf);
		for (j=0; j < ncols; j++) {
	/* ajustamos los atributos del punto leído */
			if(!point_setCoordinateX(temp, j)){
				return NULL;
			}
			if(!point_setCoordinateY(temp, i)){
				return NULL;
			}
			if(!point_setSymbol(temp, buff[j])){
				return NULL;
			}
	/* insertamos el punto en el laberinto */
			if(!maze_addPoint(pl, temp)){
				return NULL;
			}
		}
	}
	/* libera recursos */
	point_free(temp);
	/* no cerramos el fichero ya que lo han abierto fuera */
	return pl;
}