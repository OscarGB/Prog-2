/* 
 * File:   elequeue.h
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 8 de marzo de 2016, 13:11
 */
#ifndef ELEQUEUE_H
#define	ELEQUEUE_H

 #include <stdio.h>
typedef struct _EleQueue EleQueue;

/* ------------------------------------------------------------------------------
 * Inicializa un EleQueue reservando memoria e inicializando todos sus elementos.
 ------------------------------------------------------------------------------ */
EleQueue* elequeue_ini();
/* ----------------------------------------
 * Libera un EleQueue y todos sus elementos.
 ----------------------------------------- */
void elequeue_free(EleQueue * pele);
/* ---------------------------------
 * Modifica los datos de un EleQueue.
 ---------------------------------- */
EleQueue* elequeue_setInfo(EleQueue * pele, void* pvoid);
/* ------------------------------------
 * Devuelve el contenido de un EleQueue. 
 ------------------------------------ */
void* elequeue_getInfo(EleQueue * pele);
/* -------------------------------------
 * Copia reservando memoria un EleQueue.
 ------------------------------------- */
EleQueue* elequeue_copy(const EleQueue * pele1);
/* --------------------------------------------------------------------------------------------
 * Devuelve un número positivo, negativo o cero según si pele1 es mayor, menor o igual que pele2.
 -------------------------------------------------------------------------------------------- */
int elequeue_cmp(const EleQueue * pele1, const EleQueue * pele2);
/* -----------------------------------------------------------------
 * Imprime un EleQueue devolviendo el número de caracteres escritos.
 ----------------------------------------------------------------- */
int elequeue_print(FILE* f, const EleQueue * pele);

#endif /*ELEQUEUE_H*/