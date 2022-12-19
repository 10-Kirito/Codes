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
    # printf
    leaq    .batt_mode_info(%rip), %rax
    movq    %rax, %rdi
    call    printf
    # move the pointer display into rax
    movq    %rsi, %rax
    # set *display as 0
    movl    $0, (%rax)
    # return -1
    movq    $-1, %rax
    jmp     .set_display_from_batt_finished
.is_batt_mode_2_and_batt_mlvolts_0:
    # if (batt.mode == 2 && batt.mlvolts == 0)
    movb    -33(%rbp), %al
    cmpb    $2, %al
    jne     .is_batt_mode_1_and_batt_percent_0
    movw    -36(%rbp), %ax
    cmpw    $0, %ax
    jne     .is_batt_mode_1_and_batt_percent_0
    # *display = 0b00000000011111101111110111111110;
    movw    -32(%rbp), %ax
    movl    $0b00000000011111101111110111111110, (%ax)
    # return 0;
    movq    $0, %rax
    jmp     .set_display_from_batt_finished
.is_batt_mode_1_and_batt_percent_0:
    # if (batt.mode == 1 && batt.percent == 0)
    movb    -33(%rbp), %al
    cmpb    $1, %al
    jne     .is_batt_mode_1_and_batt_percent_100
    movb    -34(%rbp), %al
    cmpb    $0, %al
    jne     .is_batt_mode_1_and_batt_percent_100
    # *display = 0b00000000000000000000000111111001;
    movw    -32(%rbp), %ax
    movl    $0b00000000000000000000000111111001, (%ax)
    # return 0;
    movq    $0, %rax
    jmp     .set_display_from_batt_finished
.is_batt_mode_1_and_batt_percent_100:
    # if (batt.mode == 1 && batt.percent == 100)
    movb    -33(%rbp), %al
    cmpb    $1, %al
    jne     .is_batt_mode_1
    movb    -34(%rbp), %al
    cmpb    $100, %al
    jne     .is_batt_mode_1
    # *display = 0b00011111000011001111110111111001;
    movw    -32(%rbp), %ax
    movl    $0b00011111000011001111110111111001, (%ax)
    # return 0;
    movq    $0, %rax
    jmp     .set_display_from_batt_finished
.is_batt_mode_p:
    # if (batt.mode == 1) {//p
    movb    -33(%rbp), %al
    cmpb    $1, %al
    jne     .not_batt_mode_v
    #     fmt_bits |= 0x01; // bit0 --> 0001
    orl	    $1, -24(%rbp)
    #     mode = 10;
    movl    $10, -16(%rbp)
    #     tmp = batt.percent;
    movl    -34(%rbp), %eax
    movl    %eax, -8(%rbp)

    # init i 
    movl    $1, -20(%rbp)
    movq    $1, %rcx            # also save i in cx
.is_batt_mode_p_loop:
    #     for (i = 1; i >= 0; i--) {
    #         value = tmp / mode;
    # clear rdx
    xorq    %rdx, %rdx
    movl    -8(%rbp), %rax
    movl    -16(%rbp), %rbx
    idivq   %rbx
    # save result
    movl    %eax, -12(%rbp) 
    #         if (value != 0 || (value == 0 && i == 0)) {
    cmpl    $0, %eax
    jne     .is_batt_mode_p_loop_if_trigger
    cmpl    $0, %eax
    jne     .is_batt_mode_p_loop_if_not_trigger
    cmpl    $0, %ecx
    jne     .is_batt_mode_p_loop_if_not_trigger
    .is_batt_mode_p_loop_if_trigger:
    #             tmp_bin = v_bin[value].bin_str;
        # move `value`  into rax
        xorq    %rax, %rax
        movl    -12(%rbp), %eax
        leaq	0(,%rax,8), %rdx
        # 4+v_bin[%rip]: v_bin[INDEX].bin_str
        # INDEX will be specified by rdx
	    leaq	4+v_bin(%rip), %rax
        # copy the value of v_bin[value].bin_str to eax
	    movl	(%rdx,%rax), %eax
        # save the value into tmp_bin
        movl    %eax, -4(%rbp)
    #             fmt_bits |= (tmp_bin << (i * 7 + 3));
        # we have save the value of i into cx
        # handle the first factor
        movb    $7, %ah
        # handle the second factor
        movb    %cl, %al
        # multiple, the resultl will be in AX
        mul     %ah
        addw    $3, %ax
        # move the shift count into CX
        movw    %ax, %cx
        # load the value of tmp_bin into eax
        movl    -4(%rbp), %eax
        # bit shift
        shl     %eax, %cl
        # or
        orl	%eax, -24(%rbp)
    # ------------------------ for loop ends here --------------------------

    .is_batt_mode_p_loop_if_not_trigger:
    #         tmp = tmp % mode;
        # clear rax
        xorq    %rax, %rax
        # move the value of tmp into eax
        movl    -8(%rbp), %eax
        # divide mode and the mod will be restored in edx
        idivl   -16(%rbp)
        # save the mod value into tmp
        movl	%edx, -8(%rbp)
    #         mode /= 10;
        # load mode into register eax
        movl    -16(%rbp), %eax
        movl    $10, %ebx
        idivl   %ebx
        

    #     }
    # }
.is_batt_mode_v:

.set_display_from_batt_finished:
    leave
    ret

    ## two useful techniques for this problem
    # movl my_int(%rip),%eax
    # leaq my_array(%rip),%rdx  #load pointer to beginning of my_array into rdx
