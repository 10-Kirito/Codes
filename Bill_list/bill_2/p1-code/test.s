    .section .data
msg:
    .ascii "hello world!%d\n"

    .section .text
    .global _start      # must be declared for linker
_start:
    movq $5, %rsi
    movq $msg, %rdi
    call printf

    movq $60, %rax     # 'exit' syscall number
    xor %rdi, %rdi      # set rdi to zero
    syscall

