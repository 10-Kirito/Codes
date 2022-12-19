.section .data
output:
        .ascii "The processor Vendor ID is 'xxxxxxxxxxxx'\n"
 
.section .text
.globl _start
_start:
        movl $0, %eax
        cpuid
 
        # 创建一个指针，处理内存中声明的 output 变量时会使用这个指针
        # output 标签的内存位置被加载到 EDI 寄存器中
        # 包含厂商 ID 字符串片段的三个寄存器的内容被放到数据内存的正确位置
        # 括号外的数字表示相对于 output 标签的放置数据的位置
        movl $output, %edi
        movl %ebx, 28( %edi )
        movl %edx, 32( %edi )
        movl %ecx, 36( %edi )
 
        # Linux 的 write 系统调用参数：
        # EAX 包含系统调用值
        # EBX 包含要写入的文件描述符
        # ECX 包含字符串的开头
        # EDX 包含字符串的长度
        movl $4, %eax
        movl $1, %ebx
        movl $output, %ecx
        movl $42, %edx
        int $0x80
 
        # 通过使用系统调用 1 （ 退出函数 ）
        # 程序被正确终止，并且返回到命令提示符
        # EBX 寄存器包含程序返回给 shell 的退出代码值
        movl $1, %eax
        movl $0, %ebx
        int $0x80