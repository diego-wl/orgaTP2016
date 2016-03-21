/*
 ============================================================================
 Name        : Tp0.c
 Author      : Jorge
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"


int main(int argc, char **argv) {

	if ((strcmp(argv[1],"-h") == 0) || (strcmp(argv[1],"--help") == 0)){
		show_help();
		return 0;
	}else if ((strcmp(argv[1],"-V") == 0) || (strcmp(argv[1],"--version") == 0)){
		show_version();
		return 0;
	}

	size_t n = 3;
	matrix_t* matrix_a = create_matrix(n,n);
	matrix_t* matrix_b = create_matrix(n,n);

	//initialize matrix a
	matrix_a->array[0]=1;
	matrix_a->array[1]=2;
	matrix_a->array[2]=3;

	matrix_a->array[3]=4;
	matrix_a->array[4]=5;
	matrix_a->array[5]=6;

	matrix_a->array[6]=7;
	matrix_a->array[7]=8;
	matrix_a->array[8]=9;

	//initialize matrix b
	matrix_b->array[0]=10;
	matrix_b->array[1]=11;
	matrix_b->array[2]=12;

	matrix_b->array[3]=13;
	matrix_b->array[4]=14;
	matrix_b->array[5]=15;

	matrix_b->array[6]=16;
	matrix_b->array[7]=17;
	matrix_b->array[8]=18;

	//a * b
	matrix_t* matrix_c = create_matrix(matrix_a,matrix_b);

	puts("tp---taller"); /* prints tp---taller */
	return EXIT_SUCCESS;
}


void show_help(){
	printf("Usage:\n");
	printf("\t tp0 -h \n");
	printf("\t tp0 -V \n");
	printf("\t tp0 < in_file > out_file \n");
	printf("Options:\n");
	printf("\t -V, --version \t Print version and quit. \n");
	printf("\t -h, --help \t Print this information and quit. \n");
	printf("Examples:\n");
	printf("\t tp0 < in.txt > out.txt \n");
	printf("\t cat in.txt | tp0 > out.txt \n");

}

void show_version(){
	printf("version xx \n");
}
