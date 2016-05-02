
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LONG 20

extern int print_matrix(int fp, char* s);

int cantProcesos = 1;

typedef struct matrix {
	size_t rows;
	size_t cols;
	float *array;
} matrix_t;

// Constructor de matrix_t
matrix_t* create_matrix(size_t rows, size_t cols) {
	matrix_t* matrix = malloc(sizeof(matrix_t));
	matrix->rows = rows;
	matrix->cols = cols;
	matrix->array = (float*)calloc(rows * cols, sizeof(float));
	if (matrix->array == NULL){
		return NULL;
	}
	return matrix;
}

// Destructor de matrix_t
void destroy_matrix(matrix_t* m) {
	free(m->array);
	m->array = NULL;
	free(m);
	m=NULL;
}




// Imprime matrix_t sobre el file pointer fp en el formato solicitado
// por el enunciado
int print_matrix(FILE* fp, matrix_t* m) {
	int i = 0;
	char strNum [MAX_LONG];
	char spc = " ";

	int intCol = (int) (m->cols);
	sprintf(strNum, "%d", intCol);
	print_string(fileno(fp),strNum);
	print_string(fileno(fp),&spc);
	//fprintf(fp, "%d ", (int) (m->cols));
	while (i < (m->cols) * (m->cols)) {
		//fprintf(fp, "%f ", m->array[i]);
		//
		float flNum = m->array[i];
		//fprintf(fp, "numero float: %f\n",flNum);
		sprintf(strNum, "%f", flNum);
		//fprintf(fp, "numero string: %s\n",strNum);
		print_string(fileno(fp),strNum);
		print_string(fileno(fp),&spc);
		//
		i++;
	}
	fprintf(fp, "\n");
	return 0;
}


// Multiplica las matrices en m1 y m2
matrix_t* matrix_multiply(matrix_t* m1, matrix_t* m2) {
	int m1_index = 0;
	int m2_index = 0;
	int m2_aux = 0;
	int index = 0;
	matrix_t* result = create_matrix(m1->rows, m1->cols);

	for (m1_index = 0; m1_index <= m1->rows * m1->cols;) {
		m1_index = (index / m1->cols) * m1->rows;
		result->array[index]=0;
		for (m2_aux = 0; m2_aux < m2->rows;) {
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


int leerTamanio(int* cont, int* err) {
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

char* readString(int* errRead) {
    char c;
    char *string;
    int continuar = 1;
    c = getchar();
    while (c == 32){ // blank
    	c = getchar();
    }
    if ((c>=48 && c<=57) || (c>=45 && c<=46) || (c==43) || (c==101)){ //numeros | - | . | + | e |
    	char aux[1];
    	aux[0] = c;
    	aux[1] = '\0';
    	string = (char*) malloc((strlen(aux)+1)*sizeof(char));
    	strcpy(string, aux);
    }else if(c == 10){ // newline
    	return NULL;
    }else{
    	*errRead = 1;
    	fprintf(stderr,"Lectura de caracter no valido. Linea: %d\n",cantProcesos);
    	return NULL;
    };
    do{
        c = getchar();
        if ((c>=48 && c<=57) || (c>=45 && c<=46) || (c==43) || (c==101)){
        	char aux[1];
        	aux[0] = c;
        	aux[1] = '\0';
            string = (char*)realloc(string, (strlen(string)+strlen(aux)+1)*sizeof(char));
            strcat(string, aux);
        }else if ((c == 32) || (c == 10)){
        	continuar = 0;
        }else{
        	*errRead = 1;
        	fprintf(stderr,"Lectura de caracter no valido. Linea: %d\n",cantProcesos);
        	free(string);
        	return NULL;
        };
    }while(continuar);
    return string;
}


void fillMatrix(int tam, matrix_t *matrix, int* err) {
		   char *token;
		   int i = 0;
		   int validNumber = 0;
		   int errFill = 0;
			   token = readString(&errFill);
			   while ((token != NULL) && (i < (tam*tam)) && !errFill){
				   float d;
				   validNumber = 0;
				   validNumber = sscanf(token, "%g", &d);
				   if (validNumber > 0 ) {
					   matrix->array[i]=d;
					   i++;
				   }else{
					   fprintf(stderr,"Numero con formato incorrecto. Linea: %d\n", cantProcesos);
					   errFill = 1;
				   }
				   free(token);
				   if (i != (tam*tam)){
					   token = readString(&errFill);
				   }
			   }
			   if ((token == NULL) && (i < (tam*tam))) {
				   fprintf(stderr,"Cantidad incorrecta de parametros para matriz de dimension %d. Linea: %d\n", tam, cantProcesos);
				   errFill = 1;
			   }
			   if (errFill){ *err = errFill; };
}

int main(int argc, char **argv) {

	if (argc > 1) {
		if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
			show_help();
			return 0;
		} else if ((strcmp(argv[1], "-V") == 0)
				|| (strcmp(argv[1], "--version") == 0)) {
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
		matrix_a = create_matrix(n,n);
		matrix_b = create_matrix(n,n);
		fillMatrix(n,matrix_a, &err);
		if (!err){
			fillMatrix(n,matrix_b, &err);
		}
		if (!err){
			matrix_c = matrix_multiply(matrix_a,matrix_b);
			print_matrix(stdout, matrix_c);
			if (matrix_c != NULL) { destroy_matrix(matrix_c); };
		}
		if (matrix_a != NULL) { destroy_matrix(matrix_a); };
		if (matrix_b != NULL) { destroy_matrix(matrix_b); };

		cantProcesos++;
		if (!err){
			n = leerTamanio(&continuar, &err);
		}
	}
	return EXIT_SUCCESS;
}


