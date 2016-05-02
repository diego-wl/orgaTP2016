#include <mips/regdef.h>
#include <sys/syscall.h>

	.text			# segmento de texto del programa

	.abicalls
	.align 2		# alineacion 2^2

	.globl	print_string
	.ent	print_string
print_string:
	# debugging info: descripcion del stack frame
	.frame	$fp, 40, ra	# $fp: registro usado como frame pointer
				# 40: tamañodel stack frame
				# ra: registro que almacena el return address
	# bloque para codigo PIC
	.set	noreorder	# apaga reordenamiento de instrucciones
	.cpload t9		# directiva usada para codigo PIC
	.set	reorder		# enciende reordenamiento de instrucciones

	# creo stack frame
	subu	sp, sp, 40	# 4 (SRA) + 2 (LTA) + 4 (ABA)

	# directiva para codigo PIC
	.cprestore 24		# inserta aqui "sw gp, 24(sp)",
				# mas "lw gp, 24(sp)" luego de cada jal.
	# salvado de callee-saved regs en SRA
	sw	$fp, 28(sp)
	sw	ra, 32(sp)

	# de aqui al fin de la funcion uso $fp en lugar de sp.
	move	$fp, sp

	# salvo 1er arg (siempre)
	sw	a0, 40($fp)	#file descriptor
	sw	a1, 44($fp)	#char* a string
	move t0, a0 #t0 -> file descriptor
	move t1, a1 # t1 -> char*

	move a0, t1	# traigo char* a a0 para entrada de mystrlen
	#obtengo largo del string mystrlen
	la	t9, mystrlen	# mystrlen(name[r])
	jal	ra, t9
	#guardo resultado e LRA
	sw 	v0, 16($fp)

bpsc:
	# cargo argumentos y nro de syscall
	lw      a2, 16($fp) # t2 -> cantidad de caracteres a imprimir
	lw	    a1, 44($fp)
	lw  	a0, 40($fp)
	li	v0, SYS_write
	syscall

	# return;
	# restauro callee-saved regs
	lw	gp, 24(sp)
	lw	$fp, 28(sp)
	lw	ra, 32(sp)
	# destruyo stack frame
	addu	sp, sp, 40
	# vuelvo a funcion llamante
	jr	ra

	.end	print_string
	.size	print_string,.-print_string

	.ent	mystrlen

mystrlen:
	.frame	$fp, 16, ra
	.set	noreorder
	.cpload t9
	.set	reorder

	# creo stack frame
	subu	sp, sp, 16	# 2 (SRA) + 2 (LTA)
	.cprestore 8		# sw gp, 8(sp)
	sw	$fp, 12(sp)
	move	$fp, sp

	# salvo 1er arg (siempre)
	sw	a0, 16($fp)			## redundante

	# for (i=0; s[i] != 0; i++)
	move	t0, zero	# i=0: t0, fp+0
	sw	t0, 0($fp)	# i: t0
_for_loop:
	# condicion de corte: s[i] != 0
	lw	a0, 16($fp)			## redundante
	lw	t0, 0($fp)			## redundante
	addu	t1, a0, t0	# s[i]: t1
	lb	t1, 0(t1)			## lb, NO lw!
	beq	t1, zero, _end_for

	lw	t0, 0($fp)	# i++		## redundante
	addu	t0, t0, 1
	sw	t0, 0($fp)			## redundante
	j	_for_loop

_end_for:
	lw	v0, 0($fp)			## podria ser un move v0, t0
	lw	gp, 8(sp)
	lw	$fp, 12(sp)
	addu	sp, sp, 16
	jr	ra

	.end	mystrlen
	.size	mystrlen,.-mystrlen
