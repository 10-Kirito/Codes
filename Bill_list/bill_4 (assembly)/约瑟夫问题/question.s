	.file	"question.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "input the number of m:\0"
LC1:
	.ascii "%d\0"
LC2:
	.ascii "input the number of people n:\0"
LC3:
	.ascii "design the begin counter t:\0"
LC4:
	.ascii " %d \0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$1072, %esp
	call	___main
	movl	$LC0, (%esp)
	call	_printf
	leal	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_scanf
	movl	28(%esp), %eax
	testl	%eax, %eax
	jg	L2
	movl	$0, %eax
	jmp	L15
L2:
	movl	$LC2, (%esp)
	call	_printf
	leal	24(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_scanf
	movl	$0, 1068(%esp)
	jmp	L4
L5:
	leal	32(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_scanf
	movl	32(%esp), %edx
	movl	1068(%esp), %eax
	movl	%edx, 36(%esp,%eax,4)
	addl	$1, 1068(%esp)
L4:
	movl	24(%esp), %eax
	cmpl	%eax, 1068(%esp)
	jl	L5
	movl	$LC3, (%esp)
	call	_printf
	leal	20(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_scanf
	movl	$0, 1064(%esp)
	movl	20(%esp), %eax
	subl	$1, %eax
	movl	%eax, 1068(%esp)
	jmp	L6
L7:
	movl	1064(%esp), %eax
	leal	1(%eax), %edx
	movl	%edx, 1064(%esp)
	movl	1068(%esp), %edx
	movl	36(%esp,%edx,4), %edx
	movl	%edx, 548(%esp,%eax,4)
	addl	$1, 1068(%esp)
L6:
	movl	24(%esp), %eax
	cmpl	%eax, 1068(%esp)
	jl	L7
	movl	$0, 1068(%esp)
	jmp	L8
L9:
	movl	1064(%esp), %eax
	leal	1(%eax), %edx
	movl	%edx, 1064(%esp)
	movl	1068(%esp), %edx
	movl	36(%esp,%edx,4), %edx
	movl	%edx, 548(%esp,%eax,4)
	addl	$1, 1068(%esp)
L8:
	movl	20(%esp), %eax
	subl	$1, %eax
	cmpl	1068(%esp), %eax
	jg	L9
	movl	$0, 1064(%esp)
	jmp	L10
L14:
	movl	28(%esp), %eax
	movl	24(%esp), %ecx
	cltd
	idivl	%ecx
	movl	%edx, 1060(%esp)
	cmpl	$0, 1064(%esp)
	je	L11
	movl	1060(%esp), %edx
	movl	1064(%esp), %eax
	addl	%edx, %eax
	subl	$2, %eax
	movl	24(%esp), %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	addl	$1, %eax
	movl	%eax, 1060(%esp)
L11:
	movl	1060(%esp), %eax
	subl	$1, %eax
	movl	548(%esp,%eax,4), %eax
	movl	%eax, 4(%esp)
	movl	$LC4, (%esp)
	call	_printf
	movl	1060(%esp), %eax
	subl	$1, %eax
	movl	%eax, 1068(%esp)
	jmp	L12
L13:
	movl	1068(%esp), %eax
	addl	$1, %eax
	movl	548(%esp,%eax,4), %edx
	movl	1068(%esp), %eax
	movl	%edx, 548(%esp,%eax,4)
	addl	$1, 1068(%esp)
L12:
	movl	24(%esp), %eax
	subl	$1, %eax
	cmpl	1068(%esp), %eax
	jg	L13
	movl	1060(%esp), %eax
	movl	%eax, 1064(%esp)
	movl	24(%esp), %eax
	subl	$1, %eax
	movl	%eax, 24(%esp)
L10:
	movl	24(%esp), %eax
	cmpl	$1, %eax
	jne	L14
	movl	548(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC4, (%esp)
	call	_printf
	movl	$0, %eax
L15:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE10:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_scanf;	.scl	2;	.type	32;	.endef
