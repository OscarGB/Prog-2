/* 
 * File:   elelist.h
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 3 de abril de 2016, 18:38
 */

#ifndef ELELIST_H
#define ELELIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _EleList EleList;

/* Inicializa un EleList reservando memoria e inicializando todos sus elementos. */
EleList* elelist_ini();

/* Libera un EleList y todos sus elementos. */
void elelist_free(EleList * ele);

/* Modifica los datos de un EleList . */
EleList* elelist_setInfo(EleList * e, void* p);

/* Devuelve el contenido de un EleList . */
void* elelist_getInfo(EleList * e);

/* Copia reservando memoria un EleList . */
EleList* elelist_copy(const EleList * src);

/* Devuelve un número positivo, negativo o cero según si ele1 es mayor, menor o igual que ele2. */
int elelist_cmp(const EleList * ele1, const EleList * ele2);

/* Imprime un EleList devolviendo el número de caracteres escritos. */
int elelist_print(FILE* pf, const EleList * ele);

#endif /*ELELIST_H*/