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

int cantProcesos = 1;

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
	//printf("init destroy \n");
	free(m->array);
	m->array = NULL;
	//printf("destroy array \n");
	free(m);
	m=NULL;
	//printf("destroy matrix \n");
}

// Imprime matrix_t sobre el file pointer fp en el formato solicitado
// por el enunciado
int print_matrix(FILE* fp, matrix_t* m){
	int i = 0;
	fprintf(fp,"%d ",(int)(m->cols));
	while (i<(m->cols)*(m->cols)){
		double value;
		value = m->array[i];
		fprintf(fp,"%f ",value);
		i++;
	}
	fprintf(fp,"\n");
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
		result->array[index]=0;
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


int leerTamanio(int* cont, int* err){
	int n=0;
	int resp;
	resp = scanf("%d", &n);

	if (resp == EOF){
		*cont=0;
		return 0;
	}else if (n <= 0){
		*err = 1;
		fprintf(stderr, "no se pudo obtener tamañio de matrix. Fila: %d\n",cantProcesos);
		return 0;
	};
	return n;
}

char* readString(int* errRead){
    char c;
    char *string;
    int continuar = 1;
    c = getchar();
    while (c == 32){
    	c = getchar();
    }
    if ((c>=48 && c<=57) || (c>=45 && c<=46)){
    	char aux[1];
    	aux[0] = c;
    	aux[1] = '\0';
    	string = (char*) malloc((strlen(aux)+1)*sizeof(char));
    	strcpy(string, aux);
    }else if(c == 10){
    	return NULL;
    }else{
    	*errRead = 1;
    	fprintf(stderr,"Lectura de varacter no valido. Linea: %d\n",cantProcesos);
    	return NULL;
    };
    do{
        c = getchar();
        if ((c>=48 && c<=57) || (c>=45 && c<=46)){
        	char aux[1];
        	aux[0] = c;
        	aux[1] = '\0';
            string = (char*)realloc(string, (strlen(string)+strlen(aux)+1)*sizeof(char));
            strcat(string, aux);
        }else if ((c == 32) || (c == 10)){
        	continuar = 0;
        }else{
        	*errRead = 1;
        	fprintf(stderr,"Lectura de varacter no valido. Linea: %d\n",cantProcesos);
        	free(string);
        	return NULL;
        };
    }while(continuar);
    return string;
}


void fillMatrix(int tam, matrix_t *matrix, int* err){
		   char *token;
		   int i = 0;
		   int errFill = 0;
			   token = readString(&errFill);
			   while ((token != NULL) && (i < (tam*tam)) && !errFill){
				   float d;
				   sscanf(token, "%g", &d);

				   matrix->array[i]=d;
				   i++;
				   free(token);
				   if (i != (tam*tam)){
					   token = readString(&errFill);
				   }
			   }
			   if (errFill){ *err = errFill; };

}

int main(int argc, char **argv) {

	if (argc>1){
		if ((strcmp(argv[1],"-h") == 0) || (strcmp(argv[1],"--help") == 0)){
			show_help();
			return 0;
		}else if ((strcmp(argv[1],"-V") == 0) || (strcmp(argv[1],"--version") == 0)){
			show_version();
			return 0;
		}else{
			printf("Paramatro incorrecto. Ingrese -h para ayuda.\n");
			return 0;
		};
	}

	matrix_t* matrix_a=NULL;
	matrix_t* matrix_b=NULL;
	matrix_t* matrix_c=NULL;
	int continuar = 1;
	int err = 0;
	size_t n = leerTamanio(&continuar,&err);
	while(continuar && !err){

		//printf("carga matrix A \n");
		//printf("tamanio matrix: %d \n", (int)n );
		matrix_a = create_matrix(n,n);

		//printf("carga matrix B \n");
		//printf("tamanio matrix: %d \n", (int)n );
		matrix_b = create_matrix(n,n);
		//printf("paso 1 \n");
		//printf("llenar matriz A \n");
		fillMatrix(n,matrix_a, &err);
		//printf("paso 2 \n");
		if (!err){
			//printf("paso 3 \n");
			//printf("llenar matriz B \n");
			fillMatrix(n,matrix_b, &err);
		}
		//printf("mostrar matriz A \n");
		//print_matrix(stdout, matrix_a);
		//printf("mostrar matriz B \n");
		//print_matrix(stdout, matrix_b);
		//printf("mostrar matriz C \n");
		if (!err){
			//printf("paso 4 \n");
			//printf("puntero c: %p \n", matrix_c);
			//printf("puntero array c: %p \n", matrix_c->array);
			matrix_c = matrix_multiply(matrix_a,matrix_b);
			//printf("paso 5 \n");
			//printf("puntero c: %p \n", matrix_c);
			//printf("puntero array c: %p \n", matrix_c->array);
			print_matrix(stdout, matrix_c);
			//printf("paso 6 \n");
			//printf("limpia C \n");
			if (matrix_c != NULL) { destroy_matrix(matrix_c); };
		}
		//printf("paso 7 \n");
		//printf("limpia A \n");
		if (matrix_a != NULL) { destroy_matrix(matrix_a); };
		//printf("paso 8 \n");
		//printf("limpia B \n");
		if (matrix_b != NULL) { destroy_matrix(matrix_b); };

		if (!err){
			n = leerTamanio(&continuar, &err);
		}
	}

//	m1->array[3] = 4;
//	m1->array[4] = 5;
//	m1->array[5] = 6;
//
//	m1->array[6] = 7;
//	m1->array[7] = 8;
//	m1->array[8] = 9;
//
//	//set m2 data
//	m2->array[0]= 5;
//	m2->array[1]= 6;
//	m2->array[2]= 7;
//
//	m2->array[3]= 8;
//	m2->array[4]= 9;
//	m2->array[5]= 10;
//
//	m2->array[6]= 11;
//	m2->array[7]= 12;
//	m2->array[8]= 13;
//
//	matrix_t* m3 = matrix_multiply(m1,m2);
//	print_matrix(pf,m3);
//	destroy_matrix(m1);
//	destroy_matrix(m2);
//	destroy_matrix(m3);

	return EXIT_SUCCESS;
}


