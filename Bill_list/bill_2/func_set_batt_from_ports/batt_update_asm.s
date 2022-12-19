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
    movq -24(%rbp),%rax # 将寄存器指向的内存地址给寄存器rax
    movb $1,3(%rax)     # 将数据放在指定内存
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
