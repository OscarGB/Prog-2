#define _GNU_SOURCE /* Temporal, necesario para qsort_r */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

#include "tree.h"
#include "eletree.h"
#include "point.h"
#include "types.h"

#define MAX_LINE 150

Point* read_point_from_file(FILE* f_in){
	Point* point;
	int j, dim;
	float aux;
	char name[MAX_LINE];

	fscanf(f_in, "%d", &dim);
	point = point_ini(dim);
	for (j=0; j<dim; j++){
		fscanf(f_in, "%f", &aux);
		point_setCoordinate(point, j, aux);
	}
	fscanf(f_in, "%s\n", name);
	point_setName(point, name);
	
	return point;
}

int compare(const void* a, const void* b) {
    Point **e1, **e2;
    e1 = (Point **) a;
    e2 = (Point **) b;
    return point_cmp(*e1, *e2);
}

int compare_d(const void* a, const void* b, void* d) {
    Point **e1, **e2;
    int dim;
    e1 = (Point **) a;
    e2 = (Point **) b;
    dim = *(int*)d;
    return point_cmpd(*e1, *e2, dim);
}

int getNumberLines(FILE* pf) {
    char line[MAX_LINE];
    int n = 0;
    while (fgets(line, MAX_LINE, pf) != NULL) {
        n++;
    }
    return n;
}

void loadDataFromFile(FILE* pf, Point*** pdata) {
    Point** paux = *pdata;
    Point* p;

	while(!feof(pf)){
		p = read_point_from_file(pf);
		*paux = point_copy(p);
		paux++;
		point_free(p);
	}
}

void balance(Point** data, Tree *t, int first, int last) {
    int middle = (first + last) / 2;
    Point* p;
    EleTree* e;

    if (first <= last) {
        p = *(&(data[0]) + middle);
		e = eletree_ini();
		eletree_setInfo(e, p);
		if (tree_insert(t, e) == ERROR){
			fprintf(stdout, "Point ");			
			point_print(stdout, p);
			fprintf(stdout, " not inserted!\n");			
		}
		eletree_free(e);

        balance(data, t, first, middle - 1);
        balance(data, t, middle + 1, last);
    }
}

Tree* loadBalancedTreeFromData(Point** data, int n) {
	Tree* t;
	
	t = tree_ini();
	
    balance(data, t, 0, n - 1);
    
    return t;
}

void sort_d(Point** data, int first, int last, int ndim, int curdim) {
    int middle = (first + last) / 2;
    int d = curdim % ndim;
    if (first <= last) {
        qsort_r(data + first, last - first, sizeof(Point*), &compare_d, &d);
        sort_d(data, first, middle - 1, ndim, curdim + 1);
        sort_d(data, middle + 1, last, ndim, curdim + 1);
    }
}

Tree* loadTreeFromData(Point** data, int n) {
	Tree* t;
	Point* point;
    EleTree* pe;
	int i;
	
	t = tree_ini();
	    
	for (i=0; i<n; i++){
		point = data[i];
		pe = eletree_ini();
		eletree_setInfo(pe, point);
		if (tree_insert(t, pe) == ERROR){
			fprintf(stdout, "Point ");			
			point_print(stdout, point);
			fprintf(stdout, " not inserted!\n");			
		}
		eletree_free(pe);
	}

    return t;
}

int main(int argc, char const *argv[]){
	FILE *f_in = NULL, *f_out = NULL;
	Tree* pa = NULL;
    EleTree* pe;
	Point **data, *point;
	int i,n,ndim;
    time_t time;
    double time_in_secs;


	if(argc < 2){
		printf("Falta el fichero con puntos (un punto por línea).\n");
		return -1;
	}

	f_in = fopen(argv[1], "r");

	if (!f_in){
		return 1;
	}

	f_out = stdout;

    n = getNumberLines(f_in);
    fclose(f_in);
    fprintf(f_out, "%d líneas leídas\n", n);
    data = (Point**) malloc(n * sizeof (Point*));
    f_in = fopen(argv[1], "r");
    loadDataFromFile(f_in, &data);
    fclose(f_in);

	if ((strcmp("./p4_e2", argv[0]) == 0) || (strcmp("./p4_e4", argv[0]) == 0)) {
		time = clock();
		pa = loadTreeFromData(data, n);
		time = clock() - time;
		time_in_secs = ((float) time) / CLOCKS_PER_SEC;
	} else if (strcmp("./p4_e2_bal", argv[0]) == 0) {
		qsort(data, n, sizeof(Point*), &compare);
		fprintf(f_out, "Datos ordenados\n");
		time = clock();
		pa = loadBalancedTreeFromData(data, n);
		time = clock() - time;
		time_in_secs = ((float) time) / CLOCKS_PER_SEC;
	} else if (strcmp("./p4_e4_bal", argv[0]) == 0) {
		/* Este orden se tiene que hacer según la dimensión */
		ndim = point_getDimensions(data[0]);
	    sort_d(data, 0, n-1, ndim, 0);
		fprintf(f_out, "Datos ordenados\n");
		time = clock();
		pa = loadBalancedTreeFromData(data, n);
		time = clock() - time;
		time_in_secs = ((float) time) / CLOCKS_PER_SEC;
	}

    for (i=0; i<n; i++){
    	point_free(data[i]);
    }
    free(data);
	
    fprintf(f_out, "\nTiempo de creación del árbol: %ld ticks (%f segundos)\n", (long) time, time_in_secs);
	fprintf(f_out, "Numero de nodos: %d\nProfundidad: %d\n", tree_numNodes(pa), tree_depth(pa));
	tree_inOrder(stdout, pa);

	/*tree_inOrder(f_out, pa);fprintf(f_out, "\n");*/
	
	fprintf(stdout, "Introduce un punto para buscar en el árbol (siguiendo el mismo formato que en el fichero de entrada):\n");
	point = read_point_from_file(stdin);
	pe = eletree_ini();
	eletree_setInfo(pe, point);
	time = clock();
	if (tree_findEleTree(pa, pe) == TRUE){
		fprintf(stdout, "Elemento encontrado!\n");
	}else{
		fprintf(stdout, "Elemento NO encontrado!\n");
	}
	time = clock() - time;
	time_in_secs = ((float) time) / CLOCKS_PER_SEC;
	eletree_free(pe);
	point_free(point);
    fprintf(f_out, "\nTiempo de búsqueda en el árbol: %ld ticks (%f segundos)\n", (long) time, time_in_secs);

	tree_free(pa);

	return 0;
}
