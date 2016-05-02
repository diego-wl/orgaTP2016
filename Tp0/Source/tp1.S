

# Función equivalente en C


#matrix_t* matrix_multiply(matrix_t* m1, matrix_t* m2, matrix_t* result) {
#	int m1_index = 0;
#	int m2_index = 0;
#	int m2_aux = 0;
#	int index = 0;
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
subu sp, sp, 40

.cprestore 24 				#sw gp, sp(24) / lw gp, 24(sp).

#salvado de callee-saved regs en SRA
sw $fp, 28(sp)
sw ra, 32(sp)

move $fp, sp 				#uso fp en vez de sp.

#salvo los args fuera del stack frame.
sw a0, 40($fp)
sw a1, 44($fp)
sw a2, 48($fp)

sw zero, 0($fp) 			 #En 0(sp) tengo int m1_index = 0
sw zero, 4($fp)				 #En 4(sp) tengo int m2_index = 0
sw zero, 8($fp) 			 #En 8(sp) tengo int m2_aux = 0
sw zero, 12($fp)			 #En 12(sp) tengo int index = 0

#en a0 tengo m1 (0-4->row, 4-8 ->cols)
add a1, a0, 4 #a1 = cols

first_for:
#for (m1_index = 0; m1_index <= m1->rows * m1->cols;)
lw t0, 0($fp) 				#m1_index
lw t1, 4($fp) 				#m2_index
lw t2, 8($fp) 				#m2_aux
lw t3, 12($fp) 				#index

mulo t4, a0, a1				#rows * cols

bgt t0,t4, exit_first_for #si m1_index es mayor que (rows * cols) finalizo el loop

#m1_index = (index / m1->cols) * m1->rows;
divu t5, t3, a1  			#m1_index = (index / m1->cols) * m1->rows;
mulo t0, t5, a0
sw t1, 0($fp) 				#guardo m1_index

#result->array[index]=0;
lw t5, 48($fp) 				#result
sll t0, t3, 2
addi t0, 8
add t5, t5, t0

b second_for

second_for:
#for (m2_aux = 0; m2_aux < m2->rows;) {
lw a1, 44($fp) 				#recupero m2
addi t6, a1, 4 				# t6 = m2->rows
bge t2, t6, exit_second_for
b multiply

multiply:
#result->array[index] += m1->array[m1_index] * m2->array[m2_index];
lw t0, 0($fp) 				#m1_index
lw t1, 4($fp) 				#m2_index
lw t2, 8($fp) 				#m2_aux
lw t3, 12($fp) 				#index

sll t4, t0, 2
addi t4, 8
add t4, a0, t4  			#m1->array[m1_index]
l.s $f12, 0(t4)

sll t6, t1, 2
addi t6, 8
add t6, a1, t6  			#m2->array[m2_index]
l.s $f14, 0(t6)

mul.s $f2, $f12, $f14 		#m1->array[m1_index] * m2->array[m2_index]
s.s $f2, 0(t5)

addi t2, t2, 1 				#m2_aux++
sw t2, 8($fp)
addi t0, t0, 1 				#m1_index++
sw t0, 0($fp)

lw t0, 18($fp) 				#m2->rows
add t1, t1, t0 				#m2_index += m2->rows;
sw t1, 4($fp)


exit_second_for:
lw t3, 12($fp) 				#index
addi t3, 1
sw t3, 12($fp)

#div $rs, $rt R 0/26 Lo = $rs / $rt, Hi = $rs mod $rt
#mfhi $rd R 0/16 $rd = Hi Get value of Hi
#m2_index = index % m2->cols;
lw t1, 18($fp)
addi t1, t1, 4 				#m2->cols;
div t0, t3, t1
mfhi t0
sw t0, 4($fp) 				#piso el valor de m2_index
sw zero, 8($fp) 			#m2_aux=0

exit_first_for:
#guardo el valor de retorno
lw t0, 48($fp) 				#result
add v0, zero, t0
#destruyo el stack frame
lw gp, 24(sp)
lw $fp, 28(sp)
addu sp, sp, 40
lw ra, 32(sp)
j ra
.end matrix_multiply
