/* 
 * File:   p1_e2.c
 * Author: Óscar Gómez y Víctor García (G2101_P08)
 *
 * Created on 10 de febrero de 2016, 13:11
 */

#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "types.h"

int main() {
    /*Declarar dos puntos*/
    Point* point1 = NULL;
    Point* point2 = NULL;
    point1 = point_ini();
    if (!point1) {
        printf("Error al reservar la memoria del punto 1");
        return EXIT_FAILURE;
    }   
    point2 = point_ini();
    if (!point2) {
        printf("Error al reservar la memoria del punto 2");
        return EXIT_FAILURE;
    } 
   
    /*Inicializar valores*/
    if (!point_setSymbol(point1, BARRIER)){
        point_free(point2);
        printf("Error en la inicialización del punto 1");
        return EXIT_FAILURE;
    }
    if (!point_setCoordinateX(point1, 1)){
        point_free(point2);
        printf("Error en la inicialización del punto 1");
        return EXIT_FAILURE;
    }
    if (!point_setCoordinateY(point1, 2)){
        point_free(point2);
        printf("Error en la inicialización del punto 1");
        return EXIT_FAILURE;
    }
    if (!point_setSymbol(point2, OUTPUT)){
        point_free(point1);
        printf("Error en la inicialización del punto 2");
        return EXIT_FAILURE;
    }
    if (!point_setCoordinateX(point2, 3)){
        point_free(point1);
        printf("Error en la inicialización del punto 2");
        return EXIT_FAILURE;
    }
    if (!point_setCoordinateY(point2, 4)){
        point_free(point1);
        printf("Error en la inicialización del punto 2");
        return EXIT_FAILURE;
    }
    
    /*Imprimir ambos puntos y un salto de línea*/
    if (point_print(stdout, point1)<0){
        point_free(point1);
        point_free(point2);
        printf("Error en la escritura del punto 1");
        return EXIT_FAILURE;
    }
    if(point_print(stdout, point2)<0){
        point_free(point1);
        point_free(point2);
        printf("Error en la escritura del punto 2");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "\n");
    
    /*Comprobar si los dos puntos son iguales*/
    fprintf(stdout, "Son iguales? ");
    if (point_equals(point1, point2)==TRUE){
        fprintf(stdout, "Sí\n");
    }else{
        fprintf(stdout, "No\n");
    }
    
    /*Imprimir símbolo del primer punto*/
    fprintf(stdout, "El símbolo del primer punto es: %c\n", point_getSymbol(point1));
    
    /*Imprimir la coordenada x del segundo punto*/
    fprintf(stdout, "La coordenada X del segundo punto es: %d\n", point_getCoordinateX(point2));
    
    /*Copiar el primer punto en el segundo*/
    point_free(point2);
    point2 = point_copy(point1);
    
    /*Imprimir ambos puntos*/
    if (point_print(stdout, point1)<0){
        point_free(point1);
        point_free(point2);
        printf("Error en la escritura del punto 1");
        return EXIT_FAILURE;
    }
    if(point_print(stdout, point2)<0){
        point_free(point1);
        point_free(point2);
        printf("Error en la escritura del punto 2");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "\n");
    
    /*Comprobar si los dos puntos son iguales*/
    fprintf(stdout, "Son iguales? ");
    if (point_equals(point1, point2)==TRUE){
        fprintf(stdout, "Sí\n");
    }else{
        fprintf(stdout, "No\n");
    }
    
    /*Liberar memoria*/
    point_free(point1);
    point_free(point2);
    
    
    return EXIT_SUCCESS;
}