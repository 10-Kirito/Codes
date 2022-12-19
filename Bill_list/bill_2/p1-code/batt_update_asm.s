    .globl	batt_update
batt_update:
	pushq	%rbp
	movq	%rsp, %rbp
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
	ret
