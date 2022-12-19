.text
.global set_batt_from_ports
set_batt_from_ports:
    pushq %rbp
    movq %rsp,%rbp
    subq $24,%rsp  ## the stack is 36 bytes
    movq %rdi,-24(%rbp) ## move battr_t(short char char) to the stack
    movl $0,-4(%rbp)   ## move param 1 to the stack
    movzbl BATT_STATUS_PORT(%rip),%eax
    movzbl %al,%eax
    andl $16,%eax
    testl %eax,%eax
    je .setV
.setP: # set the mode to 1
    movq -24(%rbp),%rax
    movb $1,3(%rax)
    jmp .setbatt_t
.setV:# set the mode to 2
    movq -24(%rbp),%rax
    movb $2,3(%rax)

.setbatt_t:
    movzwl BATT_VOLTAGE_PORT(%rip),%eax
    testl %eax,%eax
    je .setZero

    movzwl BATT_VOLTAGE_PORT(%rip),%eax
    cmpl $0,%eax
    jle .voltagezero
    movzwl BATT_VOLTAGE_PORT(%rip),%eax
    sarw %ax
    movl %eax,%edx
    movq -24(%rbp),%rax
    movw %dx,(%rax)
    jmp .setpercent

.voltagezero: # if BATT_VOLTAGE_PORT <= 0
    movw $0,-24(%rbp)
    movq -24(%rbp),%rax
    movzbl 3(%rax),%eax
    cmpl $2,%eax
    jne .setpercent
    movq -24(%rbp),%rax
    movb $0,3(%rax)
    movl -4(%rbp),%eax
    movl $1,%eax
.setpercent: # calculate (batt->mlvolts - 3000) / 8;
    movq -24(%rbp),%rax
    movzwq (%rax),%rax
    cmpw $3000,%ax
    jl .setpercentzero
    movq -24(%rbp),%rax
    movzwq (%rax),%rax
    subq $3000,%rax 
    movq $8,%rbx
    pushq %rdx
    xorq %rdx,%rdx
    idivq %rbx
    popq %rdx
    movb %al,-22(%rbp)
    jmp .setfull
.setfull:
    movb -21(%rbp),%al
    cmpb $100,%al
    jne .end
    movb $100,-21(%rbp)
    jmp .end
.setpercentzero:
    movb $0,-22(%rbp)
    movb -21(%rbp),%al   
    cmpb $1,%al
    je .setmodezero
    jmp .setfull
.setmodezero:
    movb $0,-21(%rbp)
    movl $1,-4(%rbp)
    jmp .setfull
.setZero: # set mlvolts and percent to zero
    movq -24(%rbp),%rax
    movw $0,(%rax)
    movq -24(%rbp),%rax
    movb $0,2(%rax)
    ## a useful technique for this problem
    # movX some_global_var(%rip),%reg
.end:
    movl -4(%rbp),%eax
    popq %rbp
    ret
#.data
# my_int:
#    .int 1234
#
# other_int:
#    .int 0b0101
#
# my_array:
#    .int 10
#    .int 0x00014
#    .int 0b11110
#
#.text
#.global set_display_from_batt
# set_display_from_batt:
#    ## assembly instructions here
#
#    ## two useful techniques for this problem
#    # movl my_int(%rip),%eax
#    # leaq my_array(%rip),%rdx  #load pointer to beginning of my_array into rdx
#
#.text
#.global batt_update
# batt_update:
#    ## assembly instructions here
