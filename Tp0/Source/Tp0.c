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
	matrix->array = (double*)malloc(rows * cols * sizeof(double));
	return matrix;
}

// Destructor de matrix_t
void destroy_matrix(matrix_t* m){
	printf("init destroy \n");
	free(m->array);
	printf("destroy array \n");
	free(m);
	printf("destroy matrix \n");
}

// Imprime matrix_t sobre el file pointer fp en el formato solicitado
// por el enunciado
int print_matrix(FILE* fp, matrix_t* m){
	int i = 0;
	fprintf(fp,"%d ",(int)(m->cols));
	while (i<(m->cols)*(m->cols)){
		fprintf(fp,"%f ",m->array[i]);
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

int leerTamanio(int* cont){
	int n;
	int resp;
	resp = scanf("%d", &n);
	if (resp == EOF){
		*cont=0;
		return 0;
	};
	return n;
}

char* readString(){
    char c;
    char *string;
    int x;
    int continuar = 1;
    c = getchar();
    while (c == 32){
    	c = getchar();
    }
    if(c != 10){
    	x = (strlen(&c)+1);
    	char aux[1];
    	aux[0] = c;
    	aux[1] = '\0';
    	string = (char*) malloc((strlen(aux)+1)*sizeof(char));
    	strcpy(string, aux);
    	//putchar(c);
    }else{
    	return NULL;
    }
    do{
        c = getchar();
        if((c != 32)&&(c != 10)){//space
            x++;
        	char aux[1];
        	aux[0] = c;
        	aux[1] = '\0';
            string = (char*)realloc(string, (strlen(string)+strlen(aux)+1)*sizeof(char));
            strcat(string, aux);
            //putchar(c);
        }else{
        	continuar = 0;
        };
    }while(continuar);
    //printf("string: %s \n", string );
    return string;

};

void fillMatrix(int tam, matrix_t *matrix){

		   char *token;

		   int i = 0;
			   token = readString();
			   while ((token != NULL) && (i < (tam*tam))){
				   //printf("token: %s \n", token );
				   float d;
				   sscanf(token, "%g", &d);

				   matrix->array[i]=d;
				   //printf("index: %d, value: %g\n",i, d );
				   i++;
				   free(token);
				   if (i != (tam*tam)){
					   token = readString();
				   }
			   }
}

int main(int argc, char **argv) {

	if (argc>1){
		if ((strcmp(argv[1],"-h") == 0) || (strcmp(argv[1],"--help") == 0)){
			show_help();
			return 0;
		}else if ((strcmp(argv[1],"-V") == 0) || (strcmp(argv[1],"--version") == 0)){
			show_version();
			return 0;
		}
	}

	matrix_t* matrix_a;
	matrix_t* matrix_b;
	matrix_t* matrix_c;
	int continuar = 1;
	size_t n = leerTamanio(&continuar);
	while(continuar){

		//printf("carga matrix A \n");
		//printf("tamanio matrix: %d \n", (int)n );
		matrix_a = create_matrix(n,n);

		//printf("carga matrix B \n");
		//printf("tamanio matrix: %d \n", (int)n );
		matrix_b = create_matrix(n,n);

		//printf("llenar matriz A \n");
		fillMatrix(n,matrix_a);

		//printf("llenar matriz B \n");
		fillMatrix(n,matrix_b);

		//printf("mostrar matriz A \n");
		print_matrix(stdout, matrix_a);
		//printf("mostrar matriz B \n");
		print_matrix(stdout, matrix_b);
		//printf("mostrar matriz C \n");
		matrix_c = matrix_multiply(matrix_a,matrix_b);
		print_matrix(stdout, matrix_c);
		printf("limpia A \n");
		destroy_matrix(matrix_a);
		printf("limpia B \n");
		destroy_matrix(matrix_b);
		printf("limpia C \n");
		destroy_matrix(matrix_c);

		n = leerTamanio(&continuar);
	}


	return EXIT_SUCCESS;
}


