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
	matrix->array = (double*)malloc(rows*cols*sizeof(double));
	return matrix;
}

// Destructor de matrix_t
void destroy_matrix(matrix_t* m){
	free(m->array);
	free(m);
}

// Imprime matrix_t sobre el file pointer fp en el formato solicitado
// por el enunciado
int print_matrix(FILE* fp, matrix_t* m){
	fp = fopen("result.txt","w");
	if( fp == NULL ){
		return 1;
	}
	int index = 0;
	for(index = 0; index < (m->cols * m->rows); index++){
		fprintf(fp,"%f ",m->array[index]);
	}
	fclose(fp);
	return 0;
}

// Multiplica las matrices en m1 y m2
matrix_t* matrix_multiply(matrix_t* m1, matrix_t* m2){
	int m1_index = 0;
	int m2_index = 0;
	int m2_aux = 0;
	int index = 0;
	matrix_t* result = create_matrix(m1->rows,m1->cols);

	for( m1_index = 0; m1_index <= m1->rows * m1->cols; ){
		m1_index = (index / m1->cols) * m1->rows;
		for( m2_aux = 0; m2_aux < m2->rows; ){
			result->array[index] += m1->array[m1_index] * m2->array[m2_index];
			m2_aux++;
			m1_index++;
			m2_index += m2->rows;
		}
		index++;
		m2_index = index % m2->cols;
		m2_aux = 0;
	}
	return result;
}

double* tokenize(char* buf){
	char* token = strtok(buf," ");
	int dimension = atoi(token);
	int index = 0;
	double* values = (double*)malloc(dimension*dimension*sizeof(double));

	while( (token = strtok(NULL," ")) ){
		values[index] = atof(token);
		index++;
	}
	return values;
}

void loadData(matrix_t* m1,matrix_t* m2, double* values){

}

int main(int argc, char* argv[]) {
	matrix_t* m1 = create_matrix(3,3);
	matrix_t* m2 = create_matrix(3,3);
	FILE* pf;
	char buf[] ="2 1 2 3 4 5 6 7 8";

	double* matrixData = tokenize(buf);


	//set m1 data
	m1->array[0] = 1;
	m1->array[1] = 2;
	m1->array[2] = 3;

	m1->array[3] = 4;
	m1->array[4] = 5;
	m1->array[5] = 6;

	m1->array[6] = 7;
	m1->array[7] = 8;
	m1->array[8] = 9;

	//set m2 data
	m2->array[0]= 5;
	m2->array[1]= 6;
	m2->array[2]= 7;

	m2->array[3]= 8;
	m2->array[4]= 9;
	m2->array[5]= 10;

	m2->array[6]= 11;
	m2->array[7]= 12;
	m2->array[8]= 13;

	matrix_t* m3 = matrix_multiply(m1,m2);
	print_matrix(pf,m3);
	destroy_matrix(m1);
	destroy_matrix(m2);
	destroy_matrix(m3);

	return EXIT_SUCCESS;
}
