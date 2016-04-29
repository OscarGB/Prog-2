/* 
 * File:   p3_e4.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 12 de abril de 2016, 12:22
 */

#include <stdio.h>
#include "types.h"
#include "elelist.h"
#include "list.h"
#include <stdlib.h>

 int main(int argc, char *argv[]){
 	int it;
 	int *copia;
 	int numElementos, i;
 	FILE *f = NULL;
 	List *list = NULL;
 	List *laux = NULL;
 	EleList *pele = NULL;
 	if(argc != 2){
		printf("Faltan argumentos\n");
		return -1;
	}
	f = fopen(argv[1], "r");
	if (!f){
		return -1;
	}
	list = list_ini();
	if(!list){
		fclose(f);
		return -1;
	}
	while(feof(f) == 0){ /*Bucle que inserta dependiendo de si es par o impar*/
		copia = (int *)malloc(sizeof(int));
		if(!copia){
			list_free(list);
			fclose(f);
			return -1;
		}
		fscanf(f, "%d", &it);
		pele = elelist_ini();
		if(!pele){
			free(copia);
			list_free(list);
			fclose(f);
			return -1;
		}
		*copia = it;
		if(!elelist_setInfo(pele, copia)){
			list_free(list);
			fclose(f);
			free(copia);
			elelist_free(pele);
			return -1;
		}
		if((it)%2){
			if(!list_insertLast(list, pele)){
				list_free(list);
				fclose(f);
				elelist_free(pele);
				return -1;
			}
			if(list_print(stdout, list) < 0){
				list_free(list);
				fclose(f);
				elelist_free(pele);
				return -1;
			}
			fprintf(stdout, "\n");
		}else{
			if(!list_insertFirst(list, pele)){
				list_free(list);
				fclose(f);
				elelist_free(pele);
				return -1;
			}
			if(list_print(stdout, list)<0){
				list_free(list);
				fclose(f);
				elelist_free(pele);
				return -1;
			}
			fprintf(stdout, "\n");
		}
		elelist_free(pele);
	}
	fclose(f);
	numElementos = list_size(list);
	printf("Lista con %d elementos: \n", numElementos);
	if(list_print(stdout, list)<0){
		list_free(list);
		return -1;
	}
	fprintf(stdout, "\n");

	laux = list_ini();
	if(!laux){
		list_free(list);
		return -1;
	}
	for(i=0; i< (numElementos/2); i++){
		pele = list_extractFirst(list);
		printf("Elemento extraido: ");
		elelist_print(stdout, pele);
		fprintf(stdout, "\n");
		list_print(stdout, list);
		fprintf(stdout, "\n");
		if(!pele){
			list_free(list);
			list_free(laux);
			return -1;
		}
		if(!list_insertInOrder(laux, pele)){
			list_free(list);
			list_free(laux);
			elelist_free(pele);
			return -1;
		}
		list_print(stdout, laux);
		fprintf(stdout, "\n");
		elelist_free(pele);
	}
	while(list_isEmpty(list) == FALSE){
		pele = list_extractLast(list);
		if(!pele){
			list_free(list);
			list_free(laux);
			return -1;
		}
		printf("Elemento extraido: ");
		elelist_print(stdout, pele);
		fprintf(stdout, "\n");
		list_print(stdout, list);
		fprintf(stdout, "\n");
		if(!list_insertInOrder(laux, pele)){
			list_free(list);
			list_free(laux);
			elelist_free(pele);
			return -1;
		}
		list_print(stdout, laux);
		fprintf(stdout, "\n");
		elelist_free(pele);
	}

	printf("Lista con %d elementos: \n", list_size(laux));
	if(list_print(stdout, laux)<0){
		list_free(laux);
		return -1;
	}
	fprintf(stdout, "\n");
	list_free(laux);
	list_free(list);
 	return 0;
 }