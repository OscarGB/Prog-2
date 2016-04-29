/* 
 * File:  p2_e1.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 23 de febrero de 2016, 12:35
 */

#include "elestack.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void imprime_valores(FILE *f, Stack *pila){ /*Imprime los valores (no) lleno, (no) vacio*/
    if(stack_isFull(pila)){
        fprintf(f, "(llena, ");
    }
    else{
        fprintf(f, "(no llena, ");
    }
     if(stack_isEmpty(pila)){
        fprintf(f, "vacia)");
    }
    else{
        fprintf(f, "no vacia)");
    }
    return;
}

int main(int argc, char *argv[]){
    Stack *pila = NULL;
    Stack *ppares = NULL; /*Pila de números pares*/
    Stack *pimpares = NULL; /*Pila de números impares*/
    EleStack *pele = NULL;
    int i, tamano;
    int *a = NULL;
    int *aux = NULL;
    
    tamano = atoi(argv[1]);
    pila = stack_ini();
    if(!pila){
        return -1;
    }
    
    fprintf(stdout, "Pila total ");
    imprime_valores(stdout, pila);
    fprintf(stdout, ":\n\n");
    
    for(i=0; i < tamano; i++){
        pele = elestack_ini();
        if(!pele){
            stack_free(pila);
            return -1;
        }
        a = (int *)malloc(sizeof(int));
        if(!a){
            elestack_free(pele);
            stack_free(pila);
            return -1;
        }
        fprintf(stdout, "Introduce número: ");
        scanf("%d", a);
        elestack_setInfo(pele, a); /*Guardamos en pele el valor de a*/
        if(!stack_push(pila, pele)){
            elestack_free(pele);
            stack_free(pila);
            return -1;
        }
        elestack_free(pele);
    }
    
    fprintf(stdout, "\nPila total (");
    imprime_valores(stdout, pila);
    fprintf(stdout, ":\n");
    stack_print(stdout, pila);
    
    ppares = stack_ini();
    if(!ppares){
        stack_free(pila);
        return -1;
    }
    
    pimpares = stack_ini();
    if(!pimpares){
        stack_free(ppares);
        stack_free(pila);
        return -1;
    }
    
    for(i=0; i<tamano; i++){
        pele = stack_pop(pila);
        aux = elestack_getInfo(pele);
        if((*aux)%2 == 1){
            stack_push(pimpares, pele); /*Si el número es impar lo mete en la pila correspondiente*/
        }
        else{
            stack_push(ppares, pele); /*Si el número es par lo mete en la pila correspondiente*/
        }
        elestack_free(pele);
    }
    
    fprintf(stdout, "\nImprimiendo la pila ");
    imprime_valores(stdout, ppares);
    fprintf(stdout, " con números pares:\n");
    if(stack_print(stdout, ppares) < 0){
        stack_free(pimpares);
        stack_free(ppares);
        stack_free(pila);
    }
    
    fprintf(stdout, "Imprimiendo la pila ");
    imprime_valores(stdout, pimpares);
    fprintf(stdout, " con números impares:\n");
    if(stack_print(stdout, pimpares) < 0){
        stack_free(pimpares);
        stack_free(ppares);
        stack_free(pila);
    }
    
    fprintf(stdout, "\nPila total ");
    imprime_valores(stdout, pila);
    fprintf(stdout, ":\n");
    stack_print(stdout, pila);
     /*Liberamos toda la memoria reservada*/
    stack_free(pimpares);
    stack_free(ppares);
    stack_free(pila);
    return 0;
}
