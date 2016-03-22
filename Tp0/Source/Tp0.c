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

int leerTamanio(){
	int n;
	scanf("%d", &n);
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
		   /* get the first token */

		   int i = 0;
		   /* walk through other tokens */
			   token = readString();
			   while ((token != NULL) && (i < (tam*tam))){
				   //printf("token: %s \n", token );
				   float d;
				   sscanf(token, "%g", &d);

				   matrix->array[i]=d;
				   printf("index: %d, value: %g\n",i, d );
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
	int i = 0;
	while(i!=1){
		size_t n = leerTamanio();
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
		print_matrix(stdin, matrix_a);
		//printf("mostrar matriz B \n");
		print_matrix(stdin, matrix_b);
		//printf("mostrar matriz C \n");
		matrix_t* matrix_c = matrix_multiply(matrix_a,matrix_b);
		print_matrix(stdin, matrix_c);
		i++;
	}


	return EXIT_SUCCESS;
}


