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
	movl	-8(%rbp), %eax;取出tmp的值
	cltd	;清空edx
	idivl	-16(%rbp);除于mode
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
	# (i * 7 + 3)
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
	movl	%edx, %eax;edx存储的是余数，所以说我们可以使用tmp除以mode然后将余数取出来即可
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
