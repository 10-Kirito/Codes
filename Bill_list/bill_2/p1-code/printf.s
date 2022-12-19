.code32
.data
_format:
    .ascii "Hello,word!%d\0"
a:
    .long 42

.text
.global main

main:
    pushl %ebp
    movl %esp,%ebp

    pushl $42
    pushl $_format
    call printf

    movl $0,%eax

    leave#函数返回前的准备：（1） movl 5ebp,%esp (2) popl %ebp
    

    ret
