    .text
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

.text
.global set_batt_from_ports
set_batt_from_ports:
    pushq   %rbp
    movq    %rsp,%rbp

    subq    $24,%rsp            ## the stack is 24 bytes
    movq    %rdi,-24(%rbp)      ## move the pointer into memory,the size is 8 Bytes
    movl    $0,-4(%rbp)         ## move param 1 to the stack
    movzbl  BATT_STATUS_PORT(%rip),%eax
    movzbl  %al,%eax
    andl    $16,%eax
    cmpl   $0,%eax
    jle      .setV

.setP: # set the mode to 1
    movq -24(%rbp),%rax 
    movb $1,3(%rax)    
    jmp .setbatt_t
.setV:# set the mode to 2
    movq -24(%rbp),%rax
    movb $2,3(%rax)

.setbatt_t:
    movzwl BATT_VOLTAGE_PORT(%rip),%eax 
    cmpl $0,%eax
    je .setZero # if BATT_VOLTAGE_PORT == 0


    movw BATT_VOLTAGE_PORT(%rip),%ax
    cmpw $0,%ax
    jl .voltagezero # if BATT_VOLTAGE_PORT < 0
    # movzwl BATT_VOLTAGE_PORT(%rip),%eax
    sarw %ax
    movl %eax,%edx
    movq -24(%rbp),%rax
    movw %dx,(%rax)
    jmp .setpercent

.voltagezero: # if BATT_VOLTAGE_PORT <0
    movq -24(%rbp),%rax
    movw $0,(%rax)
    movq -24(%rbp),%rax
    movb 3(%rax),%al
    cmpb $2,%al
    jne .setpercent
    movq -24(%rbp),%rax
    movb $0,3(%rax)
    movl $1,-4(%rbp)
.setpercent: # calculate (batt->mlvolts - 3000) / 8;
    movq -24(%rbp),%rax
    movw (%rax),%ax
    cmpw $3000,%ax
    jl .setpercentzero
    # if (batt->mlvolts >= 3000)
    movq -24(%rbp),%rax
    movzwq (%rax),%rax
    subq $3000,%rax 
    movq $8,%rbx
    pushq %rdx
    xorq %rdx,%rdx
    idivq %rbx
    popq %rdx
    movq %rax,%rbx
    movq -24(%rbp),%rax
    movb %bl,2(%rax)

    jmp .setfull
.setfull:
    # modified
    movq -24(%rbp),%rax
    movb 2(%rax),%al
    cmpb $100,%al
    jle .end
    movq -24(%rbp),%rax
    movb $100,2(%rax)
    jmp .end
.setpercentzero:
    movq -24(%rbp),%rax
    movb $0,2(%rax)
    movq -24(%rbp),%rax 
    movb 3(%rax),%al  
    cmpb $1,%al
    je .setmodezero
    jmp .setfull
.setmodezero:
    movq -24(%rbp),%rax
    movb $0,3(%rax)
    movl $1,-4(%rbp)
    jmp .setfull
.setZero: # set mlvolts and percent to zero
    movq -24(%rbp),%rax
    movw $0,(%rax)
    movq -24(%rbp),%rax
    movb $0,2(%rax)
    movl $0,-4(%rbp)
.end:
    movl -4(%rbp),%eax
    leave
    ret

.data
.batt_mode_info:
    .string "batt.mode 0"
.text
.global set_display_from_batt
set_display_from_batt:
    # save last function frame
    pushq   %rbp
    movq    %rsp, %rbp
    # create memory
    # 6 int -> 24 Bytes
    # 1 int* -> 8 Bytes
    # 1 batt_t -> 4 bytes
    subq    $36, %rsp

    # +------------+  rbp
    # |   tmp_bin  |  rbp - 4 
    # |     tmp    |  rbp - 8
    # |    value   |  rbp - 12
    # |    mode    |  rbp - 16
    # |      i     |  rbp - 20
    # |  fmt_bits  |  rbp - 24      | char  mode    | -33
    # |   display  |  rbp - 32      | char  percent | -34
    # |    batt    |  rbp - 36  --> | short mlvolts | -36
    # +------------+
    movl    %edi, -36(%rbp)
    movq    %rsi, -32(%rbp)
    movl    $0, -24(%rbp)

.is_batt_mode_0:
    movb    -33(%rbp), %al
    cmpb    $0, %al
    jne     .is_batt_mode_2_and_batt_mlvolts_0
    # # printf
	# ================= WARNING ================
    #  SINCE WE ARE NOT LINKING /lib64/ld-linux-x86-64.so.2
	#  INTO OUT PROGRAM, WE CAN NOT CALL PRINTF HERE
	#  OR AN ERROR OF "Undefined reference" WILL BE REPORTED HERE
	# ==========================================
    # leaq    .batt_mode_info(%rip), %rax
    # movq    %rax, %rdi
    # # call printf
    # # move the pointer display into rax
    movq    %rsi, %rax
    movq    -32(%rbp), %rax
    # set *display as 0
    movl    -24(%rbp),%edx
    movl    %edx, (%rax)
    # return -1
    movl    $-1, %eax
    jmp     .set_display_from_batt_ret
.is_batt_mode_2_and_batt_mlvolts_0:
    # if (batt.mode == 2 && batt.mlvolts == 0)
    movb    -33(%rbp), %al
    cmpb    $2, %al
    jne     .is_batt_mode_1_and_batt_percent_0
    movw    -36(%rbp), %ax
    cmpw    $0, %ax
    jne     .is_batt_mode_1_and_batt_percent_0
    # *display = 0b00000000011111101111110111111110;
    movq    -32(%rbp), %rax
    movl    $0b00000000011111101111110111111110, (%rax)
    # return 0;
    movl    $0, %eax
    jmp     .set_display_from_batt_ret
.is_batt_mode_1_and_batt_percent_0:
    # if (batt.mode == 1 && batt.percent == 0)
    movb    -33(%rbp), %al
    cmpb    $1, %al
    jne     .is_batt_mode_1_and_batt_percent_100
    movb    -34(%rbp), %al
    cmpb    $0, %al
    jne     .is_batt_mode_1_and_batt_percent_100
    # *display = 0b00000000000000000000000111111001;
    movq    -32(%rbp), %rax
    movl    $0b00000000000000000000000111111001, (%rax)
    # return 0;
    movl    $0, %eax
    jmp     .set_display_from_batt_ret
.is_batt_mode_1_and_batt_percent_100:
    # if (batt.mode == 1 && batt.percent == 100)
    movb    -33(%rbp), %al
    cmpb    $1, %al
    jne     .is_batt_mode_p
    movb    -34(%rbp), %al
    cmpb    $100, %al
    jne     .is_batt_mode_p
    # *display = 0b00011111000011001111110111111001;
    movq    -32(%rbp), %rax
    movl    $0b00011111000011001111110111111001, (%rax)
    # return 0;
    movl    $0, %eax
    jmp     .set_display_from_batt_ret


.is_batt_mode_p:
    # if (batt.mode == 1) {//p
    movb    -33(%rbp), %al
    cmpb    $1, %al
    jne     .is_batt_mode_v
    # fmt_bits |= 0x01; // bit0 --> 0001
    orl	    $1, -24(%rbp)
    # mode = 10;
    movl    $10, -16(%rbp)
    #     tmp = batt.percent;
	xorq    %rax, %rax
    movb    -34(%rbp), %al
    movl    %eax, -8(%rbp)

    # init i 
    movl    $1, -20(%rbp)
.is_batt_mode_p_loop:
    # for (i = 1; i >= 0; i--) {
    # value = tmp / mode;
    movl    -8(%rbp), %eax
    cltd 
    idivl   -16(%rbp)
    movl    %eax, -12(%rbp) 
    # if (value != 0 || (value == 0 && i == 0)) {
    cmpl    $0, -12(%rbp)
    jne     .is_batt_mode_p_loop_if_trigger
    cmpl    $0, -12(%rbp)
    jne     .is_batt_mode_p_loop_if_not_trigger
    cmpl    $0, -20(%rbp)
    jne     .is_batt_mode_p_loop_if_not_trigger
.is_batt_mode_p_loop_if_trigger:
# -------------------------------------------------------------------
    # tmp_bin = v_bin[value].bin_str;    
# -------------------------------------------------------------------
		xorq    %r8, %r8
		xorq    %r9, %r9
		movl    -12(%rbp), %r9d
		leaq    v_bin(%rip), %r8
		movq    (%r8, %r9, 8), %rax    # move { num, bin_str } into rax
		shrq    $32, %rax              # bit shift, we only need the higher 32bit
		movl    %eax, -4(%rbp)         # save the result in tmp_bin

	    # (i * 7 + 3)
	    movl	-20(%rbp), %eax
		movl    $7, %edx
		mul     %edx                    # the result will be stored in dx and ax 
		addl    $3, %eax                # since the product is very small 
										# we just need eax	
		movb 	%al, %cl 				# move bit shift count to cl
	    movl	-4(%rbp), %edx 			# save tmp_bin to edx
	    sall	%cl, %edx 				# bit shift
	    movl	%edx, %eax
	    orl	%eax, -24(%rbp)

.is_batt_mode_p_loop_if_not_trigger:
        # tmp = tmp % mode;
        movl    -8(%rbp),%eax
        cltd    
        idivl   -16(%rbp)
        movl    %edx,-8(%rbp)
# -------------------------------------------
        # mode /= 10;
#--------------------------------------------
		xorq 	%rdx, %rdx
		movl 	-16(%rbp), %eax
		movl 	$10, %ebx
		idivl 	%ebx
		movl 	%eax, -16(%rbp)
        
        subl    $1,-20(%rbp)
        cmpl    $0,-20(%rbp)
        jl     .set_display_from_batt_finished  # jump out of the loop
        jmp     .is_batt_mode_p_loop            # return to the loop 
# ------------------------ for loop ends here --------------------------
.is_batt_mode_v:
        movl    -24(%rbp),%eax
        orl     $6,%eax
        movl    %eax,-24(%rbp)

        movl    $1000,-16(%rbp)
        movzwl  -36(%rbp),%eax
        movl    %eax,-8(%rbp)
        movl    $2,-20(%rbp)

.is_batt_mode_v_loop:
        movl    -8(%rbp),%eax
        cltd    
        idivl   -16(%rbp)
        movl    %eax,-12(%rbp)
        cmpl    $0,-20(%rbp)
        jne     .other
        movl    -8(%rbp),%eax
        cltd
        idivl   -16(%rbp)
        movl    %edx,%eax
        cmpl    $5,%eax
        jle     .other
        addl    $1,-12(%rbp)        
.other:
        # tmp_bin = v_bin[value].bin_str;
        # fmt_bits |= (tmp_bin << (i * 7 + 3));
		xorq    %r8, %r8
		xorq    %r9, %r9
		movl    -12(%rbp), %r9d
		leaq    v_bin(%rip), %r8
		movq    (%r8, %r9, 8), %rax     # move { num, bin_str } into rax
		shrq    $32, %rax               # bit shift, we only need the higher 32bit
		movl    %eax, -4(%rbp)          # save the result in tmp_bin
	    # (i * 7 + 3)
	    movl	-20(%rbp), %eax
		movl    $7, %edx
		mul     %edx                    # the result will be stored in dx and ax 
		addl    $3, %eax                # since the product is very small 
										# we just need eax	
		movb 	%al, %cl 				# move bit shift count to cl
	    movl	-4(%rbp), %edx 			# save tmp_bin to edx
	    sall	%cl, %edx 				# bit shift
	    movl	%edx, %eax
	    orl	%eax, -24(%rbp)

        # tmp = tmp % mode
		xorq 	%rdx, %rdx
        movl    -8(%rbp),%eax
        idivl   -16(%rbp)
        movl    %edx,-8(%rbp)

        # mode /= 10
		xorq 	%rdx, %rdx
		movl 	-16(%rbp), %eax
		movl 	$10, %ebx
		idivl 	%ebx
		movl 	%eax, -16(%rbp)

		# loop variable judge
        subl    $1,-20(%rbp)
        cmpl    $0,-20(%rbp)
        jl      .set_display_from_batt_finished
        jmp     .is_batt_mode_v_loop

.set_display_from_batt_finished:
        movzbl  -34(%rbp),%eax
        movsbl  %al,%eax
        movl    %eax,%edi
        call    find_p_bin_str  
        movl    %eax,-4(%rbp)

        movl	-4(%rbp), %eax
	    sall	$24, %eax
	    orl	    %eax, -24(%rbp)
        
	    movq	-32(%rbp), %rax
	    movl	-24(%rbp), %edx
	    movl	%edx, (%rax)
	    movl	$0, %eax
.set_display_from_batt_ret:
        leave
        ret
