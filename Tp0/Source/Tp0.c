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
	matrix->rows = rows;
	matrix->cols = cols;
	matrix->array = (double*)malloc(sizeof(rows)*sizeof(cols));
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
