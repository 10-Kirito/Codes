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
	movl	$0, -4(%rbp) #;设置参数ret = 0
	movzbl	BATT_STATUS_PORT(%rip), %eax #;取参数BATT_STATUS_PORT到eax寄存器，因为BATT_STATUS是8位的，该步骤将BATT_STATUS扩展成32位的数值，然后放在eax寄存器中
	movzbl	%al, %eax  #;取al寄存器的内容也就是那8位的数据，并进行零扩展，将其扩展为32位的值
	andl	$16, %eax  #;这里进行与运算，对应函数中第一个括号里面执行的内容
	testl	%eax, %eax #;这里进行与运算，如果等于0说明，BATT_STATUS_PORT = VOLTAGE_FLAG 0b01101111，即执行else后面的语句
	je	.L7			   #;如果不等于0，说明BATT_STATUS_PORT = PERCENT_FLAG 0b10010001，即执行if后面的语句
	movq	-24(%rbp), %rax
	movb	$1, 3(%rax)
	jmp	.L8
.L7:
	movq	-24(%rbp), %rax
	movb	$2, 3(%rax)
.L8:
	movzwl	BATT_VOLTAGE_PORT(%rip), %eax #;此处是作0扩展的2字节复制到4字节，因为在定义该变量的时候，我们定义其类型是short类型，为2个字节
	testw	%ax, %ax					  #;如果BATT_VOLTAGE_PORT = 0的话（测试的时候，传入的参数是7578），就直接执行
										  #;else {
        								  #;batt->mlvolts = 0;
    									  #;batt->percent = 0;
	je	.L9
	movzwl	BATT_VOLTAGE_PORT(%rip), %eax
	testw	%ax, %ax					  #;testw，说明操作符是双字节的
	jle	.L10							  #;
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
	movb	$0, 2(%rax)     			 #;.L9
										 #;else {
        								 #;batt->mlvolts = 0;
    									 #;batt->percent = 0;
.L14:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	set_batt_from_ports, .-set_batt_from_ports
