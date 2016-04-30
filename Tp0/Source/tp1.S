

# Función equivalente en C


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
.abicalls
.align 2
.globl matrix_multiply
.ent matrix_multiply

matrix_multiply:

.frame $fp,40,ra

#bloque de codigo para PIC
.set noreorder
.cpload t9
.set reorder


#creo el stack frame
subu sp, sp, 40  #alcanza ?

.cprestore 24 				#sw gp, sp(24) / lw gp, 24(sp).

#salvado de callee-saved regs en SRA
sw $fp, 28(sp)
sw ra, 32(sp)

move $fp, sp 				#uso fp en vez de sp.

#salvo los args fuera del stack frame.
sw a0, 40($fp)
sw a1, 44($fp)


#sw zero, 0($fp) 			 #En 0(sp) tengo int m1_index = 0
#sw zero, 4($fp)				 #En 4(sp) tengo int m2_index = 0
#sw zero, 8($fp) 			 #En 8(sp) tengo int m2_aux = 0
#sw zero, 12($fp)			 #En 12(sp) tengo int index = 0

#en a0 tengo m1 (0-4->row, 4-8 ->cols)
#add a1, a0, 4 #a1 = cols
#la t9, create_matrix
#jal ra, t9

#sw v0, 14($fp) #guardo el retorno de create_matrix

#lw a1, 44($fp) #recupero m2

#first_for:
#for (m1_index = 0; m1_index <= m1->rows * m1->cols;)
#lw t0, 0($fp) #m1_index
#lw t1, 4($fp) #m2_index
#lw t2, 8($fp) #m2_aux
#lw t3, 12($fp) #index

#mulo t4, a0, a1 # rows * cols

#bgt t0, t4, exit_first_for #si m1_index es mayor que (rows * cols) finalizo el loop

#divu t5, t3, a1  #m1_index = (index / m1->cols) * m1->rows;
#mulo t0, t5, a0

#lw t5, 14($fp) #result
#addi t5, t3, 8 # ¿? muy turbio
#li t5, zero  #result->array[index]=0;

#b second_for

#second_for:
#for (m2_aux = 0; m2_aux < m2->rows;) {
#addi t6, a1, 4 # t6 = m2->rows
#bge t2, t6, exit_second_for



#exit_second_for:
#addi t3, t3, 1 #index ++


#exit_first_for:
#destruyo el stack frame
lw gp, 24(sp)
lw $fp, 28(sp)
addu sp, sp, 40
lw ra, 32(sp)
j ra
.end matrix_multiply






