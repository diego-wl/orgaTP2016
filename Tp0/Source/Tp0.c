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

typedef struct matrix {
	size_t rows;
	size_t cols;
	double* array;
} matrix_t;

// Constructor de matrix_t
matrix_t* create_matrix(size_t rows, size_t cols){
	matrix_t* matrix = (matrix_t*)malloc(sizeof(matrix_t));
	matrix->rows = 3;
	matrix->cols = 3;
	matrix->array = (double*)malloc(sizeof(rows*cols));
	return matrix;
}

// Destructor de matrix_t
void destroy_matrix(matrix_t* m){

}

// Imprime matrix_t sobre el file pointer fp en el formato solicitado
// por el enunciado
int print_matrix(FILE* fp, matrix_t* m){

}

// Multiplica las matrices en m1 y m2
matrix_t* matrix_multiply(matrix_t* m1, matrix_t* m2){
	int m1_index = 0;
	int m2_index = 0;
	int m2_aux = 0;
	int index = 0;
	matrix_t* result = create_matrix(m1->rows,m1->cols);

	for( m1_index = 0; m1_index < m1->cols * m1->rows; ){
		for( m2_aux = 0; m2_aux < m2->rows; ){
			result->array[index] += m1->array[m1_index] * m2->array[m2_index];
			m2_aux++;
			m1_index++;
			m2_index += m2->rows;
		}
		index++;
		m1_index = index / m1->cols;
		m2_aux = 0;
	}
	return result;
}

int main(void) {
	size_t n = 3;
	matrix_t* matrix = create_matrix(n,n);
	matrix->array[0]=1;
	matrix->array[1]=2;
	matrix->array[2]=3;

	matrix->array[3]=4;
	matrix->array[4]=5;
	matrix->array[5]=6;

	matrix->array[6]=7;
	matrix->array[7]=8;
	matrix->array[8]=9;

	puts("tp---taller"); /* prints tp---taller */
	return EXIT_SUCCESS;
}
