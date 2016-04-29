/* 
 * File:   point.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 19 de abril de 2016, 22:52
 */

#include "point.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Point {
    char* name;
    float* coord;
    int dim;
};

/* Reserva memoria para un punto que tenga dim dimensiones */
Point * point_ini(int dim){
    Point *ppoint = NULL;
    int i;
    ppoint = (Point *)malloc(sizeof(Point));
    if(!ppoint){
        return NULL;
    }
    ppoint->dim = dim;
    ppoint->coord = (float *)malloc(dim * sizeof(float));
    if(!ppoint->coord){
        free(ppoint);
        return NULL;
    }
    for(i=0; i<dim; i++){
        ppoint->coord[i] = 0;
    }
    ppoint->name = NULL;
    return ppoint;
}

/* Libera el punto */
void point_free(Point *ppoint){
    if(ppoint){
        free(ppoint->name);
        free(ppoint->coord);
        free(ppoint);
    }
    return;
}

/* Obtiene la coordenada dim-ésima de p y la almacena en v, devolviendo OK si todo va bien */
Status point_getCoordinate(const Point * p, const int dim, float * v){
    if(!p || dim < 0 || dim >= p->dim){
        return ERROR;
    }
    if(!v){
        v = (float *)malloc(sizeof(int));
        if(!v){
            return ERROR;
        }
    }
    *v = p->coord[dim];
    return OK;
}

/* Devuelve el nombre almacenado en p */
const char* point_getName(const Point * p){
    if(!p || !p->name){
        return NULL;
    }
    return p->name;
}

/* Devuelve el número de dimensiones de p */
int point_getDimensions(const Point * p){
    if(!p){
        return -1;
    }
    return p->dim;
}

/* Asigna el valor v a la coordenada dim-ésima al punto p */
Point * point_setCoordinate(Point * p, const int dim, const float v){
     if(!p || dim < 0 || dim >= p->dim){
        return NULL;
    }
    p->coord[dim] = v;
    return p;
}

/* Asigna el nombre name al punto p */
Point * point_setName(Point *p, const char* name){
    if(!p || !name){
        return NULL;
    }
    p->name = (char *)malloc((strlen(name) + 1) * sizeof(char));
    if(!p->name){
        return NULL;
    }
    strcpy(p->name, name);
    return p;
}

/* Copia un punto reservando memoria para dicho punto y todos sus atributos, copiando sus valores */
Point * point_copy(const Point * src){
    Point *copia = NULL;
    float v;
    int dim, i;
    if(!src){
        return NULL;
    }
    dim = point_getDimensions(src);
    copia = point_ini(dim);
    if(!copia){
        return NULL;
    }
    if(!point_setName(copia, point_getName(src))){
        point_free(copia);
        return NULL;
    }
    for(i=0; i < dim; i++){
        if(point_getCoordinate(src, i, &v) == ERROR){
            point_free(copia);
            return NULL;
        }
        if(!point_setCoordinate(copia, i, v)){
            point_free(copia);
            return NULL;
        }
    }
    return copia;
}

/* Imprime un punto p en el fichero pf, devolviendo el número de caracteres impresos */
int point_print(FILE *pf, const Point *p){
    int dim, i, contador = 0;
    float v;
    if(!pf || !p){
        return -1;
    }
    dim = point_getDimensions(p);
    contador += fprintf(pf, "%d " , dim);
    for(i=0; i < dim; i++){
        if(point_getCoordinate(p, i, &v) == ERROR){
            return -1;
        }
        contador += fprintf(pf, "%f ", v);
    }
    contador += fprintf(pf, "%s\n", point_getName(p));
    return contador;
}

/* Compara p1 con p2 devolviendo un número negativo, cero o positivo según si p1 es menor, igual o mayor
que p2 */
int point_cmp(const Point * p1, const Point * p2){
    int i;
    if(!p1 || !p2){
        return -31416; /* Número de error*/
    }

    if (p1->dim != p2->dim){ /*Si los puntos no tienen la misma dimension*/
        return ((p1->dim)-(p2->dim)); /*El que tenga mayor dimensión será mayor*/
    }

    for(i=0; i<p1->dim; i++){
        if(p1->coord[i] < p2->coord[i]){ /* Si p1 es menor */
            return -1;
        }
        else if(p1->coord[i] > p2->coord[i]){ /* Si p1 es mayor */
            return 1;
        }
    } 
    return strcmp(p1->name, p2->name);
}

/***** Necesario a partir de P4_E4 *****/

/* Compara la coordenada dim-ésima de p1 y la de p2 devolviendo un número negativo, cero o positivo según
si p1 es menor, igual o mayor que p2 */
int point_cmpd(const Point * p1, const Point * p2, const int dim){
    if (!p1 || !p2 || dim < 0){
        return -31416; /*Número de error*/
    }
    if (p1->dim > p2->dim){ /*Si los puntos no tienen la misma dimension*/
        return 1;
    }else if(p1->dim < p2->dim){
        return -1;
    }
    else{
        if(p1->coord[dim] > p2->coord[dim]){
            return 1;
        }else if(p1->coord[dim] < p2->coord[dim]){
            return -1;
        }else{
            return 0;
        }
    }
} 