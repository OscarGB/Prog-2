/* 
 * File:   point.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 2 de febrero de 2016, 13:11
 */

#include "point.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

struct _Point{
    char symbol;
    int x;
    int y;
}/*Point*/;
/*Asigna coordenada X y devuelve NULL en caso de fallo*/
Point * point_setCoordinateX(Point *ppoint, const int x){
    if(!ppoint){
        return NULL;
    }
    ppoint->x = x;
    return ppoint;
}
/*Asigna coordenada Y y devuelve NULL en caso de fallo*/
Point * point_setCoordinateY(Point *ppoint, const int y){
    if(!ppoint){
        return NULL;
    }
    ppoint->y = y;
    return ppoint;
}
/*Asigna el simbolo y devuelve NULL en caso de fallo*/
Point * point_setSymbol(Point *ppoint, const char s){
    if(!ppoint){
        return NULL;
    }
    ppoint->symbol = s;
    return ppoint;
}
/*Inicializa un punto*/
Point * point_ini() {
    Point *ppoint = NULL;
    ppoint = (Point *) malloc(sizeof (Point));/*Reserva memoria*/
    if (!ppoint) {
        return NULL;
    }
    /*inicializa los valores [(-1,-1):E]*/
    if(!point_setCoordinateX(ppoint, -1)){
        point_free(ppoint);
        return NULL;
    }
    if(!point_setCoordinateY(ppoint, -1)){
        point_free(ppoint);
        return NULL;
    }
    if(!point_setSymbol(ppoint, ERRORCHAR)){
        point_free(ppoint);
        return NULL;
    }
    return ppoint;
}
/*Libera memoria de point*/
void point_free(Point *ppoint){
    free(ppoint);
    return;
}
/*Devuelve la coordenada X*/
int point_getCoordinateX(const Point *ppoint){
    if(!ppoint){
        return -1;
    }
    return ppoint->x;
}
/*Devuelve la coordenada Y*/
int point_getCoordinateY(const Point *ppoint){
    if(!ppoint){
        return -1;
    }
    return ppoint->y;
}
/*Devuelve el símbolo*/
char point_getSymbol(const Point *ppoint){
    if(!ppoint){
        return -1;
    }
    return ppoint->symbol;
}
/*Comprueba que dos puntos son iguales y devuelve TRUE en caso afirmativo y
  FALSE en caso de error o que no lo sean*/
Bool point_equals(const Point *ppoint1, const Point *ppoint2){
    if(!ppoint1||!ppoint2){
        return FALSE;
    }
    if((ppoint1->x==ppoint2->x)&&(ppoint1->y==ppoint2->y)&&(ppoint1->symbol==ppoint2->symbol)){
        return TRUE;
    }
    return FALSE;
}
/*Copia un punto a un puntero que se inicializa dentro de la función, retorna NULL en caso de error*/
Point * point_copy(const Point *ppoint){
    Point *copyPoint=NULL;
    if(!ppoint){
        return NULL;
    }
    copyPoint = point_ini();/*Reserva memoria de la copia y lo inicializa por defecto*/
    if(!copyPoint){
        return NULL;
    }
    if(!point_setCoordinateX(copyPoint, point_getCoordinateX(ppoint))){
        return NULL;
    }
    if(!point_setCoordinateY(copyPoint, point_getCoordinateY(ppoint))){
        return NULL;
    }
    if(!point_setSymbol(copyPoint, point_getSymbol(ppoint))){
        return NULL;
    }
    return copyPoint;    
}

/*Imprime en fichero los datos de un punto. Decidimos que si ocurre algún error,
  la función devolverá un número negativo*/
int point_print(FILE *f, const Point *ppoint){
    if(!f || !ppoint){
        return -1;
    }
    return fprintf(f, "[(%d,%d):%c]", 
    point_getCoordinateX(ppoint), point_getCoordinateY(ppoint), point_getSymbol(ppoint));
}