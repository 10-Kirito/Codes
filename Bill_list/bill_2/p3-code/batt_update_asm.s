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
    # leaq    .batt_mode_info(%rip), %rax
    # movq    %rax, %rdi
    # # call printf
    # # move the pointer display into rax
    # movq    %rsi, %rax
    # movq    -32(%rbp), %rax
    # # set *display as 0
    # movl    -24(%rbp),%edx
    # movl    %edx, (%rax)
    # # return -1
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
    # movl    $0b00000000011111101111110111111110, (%rax)
    movl    $8322558, (%rax)
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
    # movl    $0b00000000000000000000000111111001, (%rax)
    movl    $505, (%rax)
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
    # movl    $0b00011111000011001111110111111001, (%rax)
    movl    $520945145, (%rax)
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
    movl    -34(%rbp), %eax
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
	    orl	    %eax, -24(%rbp)

.is_batt_mode_p_loop_if_not_trigger:
        # tmp = tmp % mode;
        movl    -8(%rbp),%eax
        cltd    
        idivl   -16(%rbp)
        movl    %edx,-8(%rbp)
# -------------------------------------------
        # mode /= 10;
#--------------------------------------------
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
        # copy-----copy 
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
        # copy-----copy
        # tmp = tmp % mode
        movl    -8(%rbp),%eax
        cltd    
        idivl   -16(%rbp)
        movl    %edx,-8(%rbp)
        # 该处为copy,实现mode /= 10
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
