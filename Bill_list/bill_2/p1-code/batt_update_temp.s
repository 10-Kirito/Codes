	.file	"batt_update.c"
	.text

	.globl	p_bin
	.data
	.align 32
	.type	p_bin, @object
	.size	p_bin, 72
p_bin:
	.long	0
	.long	4
	.long	0
	.long	5
	.long	29
	.long	1
	.long	30
	.long	49
	.long	3
	.long	50
	.long	69
	.long	7
	.long	70
	.long	89
	.long	15
	.long	90
	.long	100
	.long	31

	.globl	v_bin
	.align 32
	.type	v_bin, @object
	.size	v_bin, 88
v_bin:
	.long	0
	.long	63
	.long	1
	.long	6
	.long	2
	.long	91
	.long	3
	.long	79
	.long	4
	.long	102
	.long	5
	.long	109
	.long	6
	.long	125
	.long	7
	.long	7
	.long	8
	.long	127
	.long	9
	.long	111
	.long	10
	.long	64
	
    .text
	.globl	find_p_bin_str
	.type	find_p_bin_str, @function
find_p_bin_str:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L5:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	p_bin(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L3
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	4+p_bin(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	%eax, -20(%rbp)
	jg	.L3
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+p_bin(%rip), %rax
	movl	(%rdx,%rax), %eax
	jmp	.L4
.L3:
	addl	$1, -4(%rbp)
.L2:
	cmpl	$5, -4(%rbp)
	jle	.L5
	movl	$0, %eax
.L4:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	find_p_bin_str, .-find_p_bin_str
	.globl	set_batt_from_ports
	.type	set_batt_from_ports, @function
set_batt_from_ports:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	movzbl	BATT_STATUS_PORT(%rip), %eax
	movzbl	%al, %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L7
	movq	-24(%rbp), %rax
	movb	$1, 3(%rax)
	jmp	.L8
.L7:
	movq	-24(%rbp), %rax
	movb	$2, 3(%rax)
.L8:
	movzwl	BATT_VOLTAGE_PORT(%rip), %eax
	testw	%ax, %ax
	je	.L9
	movzwl	BATT_VOLTAGE_PORT(%rip), %eax
	testw	%ax, %ax
	jle	.L10
	movzwl	BATT_VOLTAGE_PORT(%rip), %eax
	sarw	%ax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movw	%dx, (%rax)
	jmp	.L11
.L10:
	movq	-24(%rbp), %rax
	movw	$0, (%rax)
	movq	-24(%rbp), %rax
	movzbl	3(%rax), %eax
	cmpb	$2, %al
	jne	.L11
	movq	-24(%rbp), %rax
	movb	$0, 3(%rax)
	movl	$1, -4(%rbp)
.L11:
	movq	-24(%rbp), %rax
	movzwl	(%rax), %eax
	cmpw	$2999, %ax
	jle	.L12
	movq	-24(%rbp), %rax
	movzwl	(%rax), %eax
	cwtl
	subl	$3000, %eax
	leal	7(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$3, %eax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movb	%dl, 2(%rax)
	jmp	.L13
.L12:
	movq	-24(%rbp), %rax
	movb	$0, 2(%rax)
	movq	-24(%rbp), %rax
	movzbl	3(%rax), %eax
	cmpb	$1, %al
	jne	.L13
	movq	-24(%rbp), %rax
	movb	$0, 3(%rax)
	movl	$1, -4(%rbp)
.L13:
	movq	-24(%rbp), %rax
	movzbl	2(%rax), %eax
	cmpb	$100, %al
	jle	.L14
	movq	-24(%rbp), %rax
	movb	$100, 2(%rax)
	jmp	.L14
.L9:
	movq	-24(%rbp), %rax
	movw	$0, (%rax)
	movq	-24(%rbp), %rax
	movb	$0, 2(%rax)
.L14:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	set_batt_from_ports, .-set_batt_from_ports
	.section	.rodata
.LC0:
	.string	"batt.mode 0"
	.text
	.globl	set_display_from_batt
	.type	set_display_from_batt, @function
set_display_from_batt:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$0, -24(%rbp)
	movzbl	-33(%rbp), %eax
	testb	%al, %al
	jne	.L17
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-48(%rbp), %rax
	movl	-24(%rbp), %edx
	movl	%edx, (%rax)
	movl	$-1, %eax
	jmp	.L18
.L17:
	movzbl	-33(%rbp), %eax
	cmpb	$2, %al
	jne	.L19
	movzwl	-36(%rbp), %eax
	testw	%ax, %ax
	jne	.L19
	movq	-48(%rbp), %rax
	movl	$8322558, (%rax)
	movl	$0, %eax
	jmp	.L18
.L19:
	movzbl	-33(%rbp), %eax
	cmpb	$1, %al
	jne	.L20
	movzbl	-34(%rbp), %eax
	testb	%al, %al
	jne	.L20
	movq	-48(%rbp), %rax
	movl	$505, (%rax)
	movl	$0, %eax
	jmp	.L18
.L20:
	movzbl	-33(%rbp), %eax
	cmpb	$1, %al
	jne	.L21
	movzbl	-34(%rbp), %eax
	cmpb	$100, %al
	jne	.L21
	movq	-48(%rbp), %rax
	movl	$520945145, (%rax)
	movl	$0, %eax
	jmp	.L18
.L21:
	movzbl	-33(%rbp), %eax
	cmpb	$1, %al
	jne	.L22
	orl	$1, -24(%rbp)
	movl	$10, -16(%rbp)
	movzbl	-34(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, -8(%rbp)
	movl	$1, -20(%rbp)
	jmp	.L23
.L26:
	movl	-8(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%eax, -12(%rbp)
	cmpl	$0, -12(%rbp)
	jne	.L24
	cmpl	$0, -12(%rbp)
	jne	.L25
	cmpl	$0, -20(%rbp)
	jne	.L25
.L24:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	4+v_bin(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-20(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	addl	$3, %eax
	movl	-4(%rbp), %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	orl	%eax, -24(%rbp)
.L25:
	movl	-8(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%edx, -8(%rbp)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$1717986919, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$2, %edx
	sarl	$31, %eax
	movl	%eax, %ecx
	movl	%edx, %eax
	subl	%ecx, %eax
	movl	%eax, -16(%rbp)
	subl	$1, -20(%rbp)
.L23:
	cmpl	$0, -20(%rbp)
	jns	.L26
	jmp	.L27
.L22:
	orl	$6, -24(%rbp)
	movl	$1000, -16(%rbp)
	movzwl	-36(%rbp), %eax
	cwtl
	movl	%eax, -8(%rbp)
	movl	$2, -20(%rbp)
	jmp	.L28
.L30:
	movl	-8(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%eax, -12(%rbp)
	cmpl	$0, -20(%rbp)
	jne	.L29
	movl	-8(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%edx, %eax
	cmpl	$5, %eax
	jle	.L29
	addl	$1, -12(%rbp)
.L29:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	4+v_bin(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-20(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	subl	%edx, %eax
	addl	$3, %eax
	movl	-4(%rbp), %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	orl	%eax, -24(%rbp)
	movl	-8(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%edx, -8(%rbp)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$1717986919, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$2, %edx
	sarl	$31, %eax
	movl	%eax, %ecx
	movl	%edx, %eax
	subl	%ecx, %eax
	movl	%eax, -16(%rbp)
	subl	$1, -20(%rbp)
.L28:
	cmpl	$0, -20(%rbp)
	jns	.L30
.L27:
	movzbl	-34(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	find_p_bin_str
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	sall	$24, %eax
	orl	%eax, -24(%rbp)
	movq	-48(%rbp), %rax
	movl	-24(%rbp), %edx
	movl	%edx, (%rax)
	movl	$0, %eax
.L18:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	set_display_from_batt, .-set_display_from_batt
	.globl	batt_update
	.type	batt_update, @function
batt_update:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-12(%rbp), %rax
	movq	%rax, %rdi
	call	set_batt_from_ports
	movl	%eax, -16(%rbp)
	cmpl	$1, -16(%rbp)
	jne	.L32
	movl	-16(%rbp), %eax
	jmp	.L34
.L32:
	movl	-12(%rbp), %eax
	leaq	BATT_DISPLAY_PORT(%rip), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	set_display_from_batt
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
.L34:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L35
	call	__stack_chk_fail@PLT
.L35:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	batt_update, .-batt_update
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
