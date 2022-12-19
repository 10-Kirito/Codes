    .globl	batt_update
batt_update:
    # save the last function frame
	pushq	%rbp
	movq	%rsp, %rbp
    # create memory for ret and batt
    # ret is an `int`, which needs 4 bytes
    # batt is a struct of `batt_t`, which also needs 4 bytes
    # thus, we need 8 bytes
	subq	$8, %rsp
    
    # get the address of `ret`, save it in rax
	leaq	-4(%rbp), %rax
    # copy the address of `ret` to `rdi`, 
    # for it is where the first argument stores
	movq	%rax, %rdi
    # call set_batt_from_ports
	call	set_batt_from_ports
    # save the return value of set_batt_from_ports to `ret`
	movl	%eax, -8(%rbp)

    # compare the value of return number
    # it is one, just return the value
    # it is not, we need farther proccess
	cmpl	$1, -8(%rbp)
	jne	.batt_update_ret_not_1
    # copy the return value to `eax` for it is where the return value stores
	movl	-8(%rbp), %eax
	jmp	.batt_update_end 

    # if the return value is not 1
.batt_update_ret_not_1:
	movl	-4(%rbp), %eax
    # load the address of BATT_DISPLAY_PORT to `rdx`
	leaq	BATT_DISPLAY_PORT(%rip), %rdx
    # set the second argument
	movq	%rdx, %rsi
    # set the first argument
	movl	%eax, %edi
	call	set_display_from_batt
    # the return value of current function is the return value of set_display_from_batt
    # so we don't to do further work, just return is fine

.batt_update_end:
    # restore the stack pointers
	leave
	ret
