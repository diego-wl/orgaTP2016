
/**
 * Función equivalente en C
 */

#matrix_t* matrix_multiply(matrix_t* m1, matrix_t* m2) {
#	int m1_index = 0;
#	int m2_index = 0;
#	int m2_aux = 0;
#	int index = 0;
#	matrix_t* result = create_matrix(m1->rows, m1->cols);
#
#	for (m1_index = 0; m1_index <= m1->rows * m1->cols;) {
#		m1_index = (index / m1->cols) * m1->rows;
#		result->array[index]=0;
#		for (m2_aux = 0; m2_aux < m2->rows;) {
#			result->array[index] += m1->array[m1_index] * m2->array[m2_index];
#			m2_aux++;
#			m1_index++;
#			m2_index += m2->rows;
#		}
#		index++;
#		m2_index = index % m2->cols;
#		m2_aux = 0;
#	}
#	return result;
#}

#include <mips/regdef.h>

.text
.globl matrix_multiply

#bloque de codigo para PIC
.set noreorder
.cpload t9
.set reorder


#creo el stack frame
subu sp, sp, 40  //alcanza ?

.cprestore 24 //sw gp, sp(24) / lw gp, 24(sp).

sw $fp, 28(sp)
sw $ra, 32(sp)

move $fp, sp //uso fp en vez de sp.

#salvo los args
sw a0, 40($fp)
sw a1, 44($fp)




















