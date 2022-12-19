; 该程序实现了电话簿的基本功能：
; 增删查改
; 输出整个电话簿
assume ds:data,cs:code,ss:stacks
data segment
    sum dw 0        ;记录当前电话簿中有多少联系人
    namemax db 20   ;用来存储临时输入的联系人姓名
    _length db ?
    _name db 20 dup(' ')
    tel_tab db 80 dup(20,?,20 dup(' '),32,12,?,12 dup(0),32);存储人名和电话号码
    menu db 13,10,"---------------menu-----------------",13,10
    menu1 db "--Add a people to the table--------1",13,10   
    menu2 db "--Delete a people from table-------2",13,10   
    menu3 db "--Search a people from table-------3",13,10   
    menu6 db "--Change detail of the people------4",13,10   
    menu7 db "--Show all detail of the book------5",13,10   
    menu4 db "--exit-----------------------------0",13,10   
    menu5 db "Please input num to choose (0-5): ",'$'
    temp db "Please input name: ","$"
    tel_num db 13,10,"Please input the phone_num(11-digit): ","$"
    CRLF db 13,10,'$'
    method db "Please input name:",'$'
    method_0 db "Please input the name to delete:",'$'
    temp6 db 13,10,"The table is empty!",'$'
    temp7 db 13,10,"Failed to find the people!",'$'
    temp8 db 13,10,"The telephone book is below:",13,10,'$'
    temp9 db 13,10,"Please input the name you want to change:",'$'
    temp10 db 13,10,"Please input the number you want:",'$'
    temp11 db 13,10,"Change the detail of the man successfully!",13,10,'$'

data ends
stacks segment stack
    dw 20 dup(?)
stacks ends

; 定义宏，输出菜单
show_menu macro 
    mov dx,offset menu
    mov ah,09h
    int 21H
endm 

;定义宏指令，用来清屏用
clear   macro a,b,c,d
    mov     al,0
    mov     bh,7
    mov     ch,a
    mov     cl,b
    mov     dh,c
    mov     dl,d
    mov     ah,6
    int     10h
endm
;设置光标在 (y，x)位置，设置光标行列位置
post_c  macro y,x           
    mov bh,0       
	mov ah,2         
	mov dh,y       
	mov dl,x         
	int 10h         
endm

; 定义宏，回车
CF macro
    mov dx,offset CRLF
    mov ah,09h
    int 21H
endm

code segment
start:
    mov ax,data
    mov ds,ax
    mov ax,stacks
    mov ss,ax
main_loop:
    clear 0,0,24,79 ; 清屏
    post_c 0,0
main_loop0:
    show_menu ; 输出菜单
    mov ah,1 ;从键盘输入数字选择
    int 21H     
    push ax

    block_loop:
    mov     ah,0
    int     16h
    cmp     ah,1ch
    jne     block_loop

    CF                  ;输出回车
    pop ax
    xor ah,ah
    cmp ax,0030h
    je return           ;如果输入的是0，则结束程序
    cmp ax,0031h
    je loop1            ;如果输入的是1，2，3，4,5，则进入子程序
    cmp ax,0032h
    je loop2
    cmp ax,0033h
    je loop3
    cmp ax,0034h
    je loop4
    cmp ax,0035h
    je loop5
    jmp main_loop

return: 
    mov ah,4CH
    int 21H
loop1:
    call add_man
    jmp main_loop
loop2:
    call del_man
    jmp main_loop0
loop3:
    call sear_man
    jmp main_loop0
loop4:
    call change
    jmp main_loop0
loop5:
    call show_book
    jmp main_loop0

;输出所有联系人
show_book proc near
    mov dx,offset temp8
    mov ah,09h
    int 21h

    push sum
    cmp sum,0
    je show_empty  	;如果电话簿为空的话，输出相应信息
    mov cx,sum
    

    mov si,offset tel_tab
show_big:
    push cx			;外层循环，遍历每一位联系人
    add si,1
    mov cl,ds:[si]
    xor ch,ch
    add si,1
    push si
show_name:			;输出姓名
    mov dl,ds:[si]
    mov ah,02h
    int 21H
    inc si
    loop show_name

    pop si
    add si,22
    mov cl,ds:[si]
    xor ch,ch
    add si,1
    push si
    
    mov dl,' '
    mov ah,02h
    int 21H
show_phonenum:		;输出电话号码
    mov dl,ds:[si]
    mov ah,02h
    int 21H
    inc si
    loop show_phonenum
    CF

    pop si
    add si,13
    pop cx
    loop show_big
    jmp show_ret

show_empty:
    mov dx,offset temp6
    mov ah,09h
    int 21h
show_ret:
    pop sum
    ret
show_book endp

add_man proc near	;添加联系人
    lea dx,temp
    mov ah,09h  
    int 21H
    mov dx,offset tel_tab
    push sum
init:				;初始化该联系人存放的内存位置
    cmp sum,0
    je add_loop
    add dx,38
    sub sum,1
    jmp init
add_loop:
    pop sum
    mov ah,0ah
    int 21H
    push dx

    mov dx,offset tel_num
    mov ah,09h
    int 21H

    pop dx
    add dx,23
    mov ah,0ah
    int 21h
    
    inc sum			;计数器加一
    ret
add_man endp

;删除联系人
del_man proc near
    push sum;暂存联系人的人数
    
    mov dx,offset method_0
    mov ah,09h
    int 21H

    ;输入要删除的联系人
    mov dx,offset namemax
    mov ah,0ah
    int 21H

    cmp sum,1
    je dele_brige2

    ;取出比较的次数
    mov cl,_length
    xor ch,ch
    ;初始化电话簿的地址
    mov si,offset tel_tab
    add si,2
    mov di,seg _name
    mov es,di
    mov di,offset _name
    mov bx,0		;计数器，记录我们要删除的联系人的位置
    cmp sum,0
    je dele_brige	;如果sum一开始就为0，即为空的，肯定找不到
dele_loop4:
    cmp sum,0		;此时肯定不会满足条件，所以开始寻找
    je dele_brige1	;由于跳转的位置距离此处太远所以需要跳板
    inc bx
dele_cmp:
    push bx
    mov al,ds:[si]
    mov bl,es:[di]
    cmp al,bl
    pop bx
    jne dele_nomatch
    inc si
    inc di
    loop dele_cmp
    jmp dele_suce
dele_nomatch:
    add si,38
    mov di,offset _name
    sub sum,1
    jmp dele_loop4
dele_brige:
    jmp dele_empty
dele_brige1:
    jmp dele_fail
dele_brige2:
    jmp dele_only
;查找成功
;找到并初始化我们要删除的联系人的位置
dele_suce:
    mov cx,bx
    sub cx,1
    mov si,offset tel_tab
dele_init:
    cmp cx,0
    je dele_init_
    add si,38
    loop dele_init

dele_init_:
;初始化最后一位联系人的位置
    pop cx;取出当前联系人的总人数
    push cx

    mov di,seg _name
    mov es,di
    mov di,offset tel_tab
    sub cx,1;如果当前总人数为1的话，就不需要循环初始化
    cmp cx,0
    je _exchange
dele_loop:
    add di,38
    loop dele_loop
    push si
    push di
;交换最后一位联系人和我们要删除的联系人的姓名位置
_exchange:
    mov cx,22
_xchange:
    mov al,es:[di]
    mov byte ptr ds:[si],al
    inc di
    inc si
    loop _xchange
    ;交换相应联系人电话号码
    pop di
    pop si
    add si,23
    add di,23
    mov cx,14
_xchange_num:
    mov al,es:[di]
    mov byte ptr ds:[si],al
    inc di
    inc si
    loop _xchange_num
dele_exit:
    pop sum
;删除一个联系人之后，总人数减少
    sub sum,1
    ret
dele_only:
    mov dx,offset temp11
    mov ah,09h
    int 21H
    pop sum
    sub sum,1
    ret
;查找失败
dele_fail:
    mov dx,offset temp7
    mov ah,09h
    int 21H
    pop sum
    ret
;表为空
dele_empty:
    mov dx,offset temp6
    mov ah,09h
    int 21H
    pop sum
    ret
del_man endp

;寻找联系人
sear_man proc near
    push sum;暂存联系人的人数
    mov dx,offset method
    mov ah,09h
    int 21H

    ;输入要寻找的联系人
    mov dx,offset namemax
    mov ah,0ah
    int 21H

    ;取出比较的次数
    mov cl,_length
    xor ch,ch
    ;初始化电话簿的地址
    mov si,offset tel_tab
    add si,2
    mov di,seg _name
    mov es,di
    mov di,offset _name
    mov bx,0
    cmp sum,0
    je sear_empty;如果sum一开始就为0，即为空的，肯定找不到
sear_loop4:
    cmp sum,0;此时肯定不会满足条件，所以开始寻找
    je sear_fail
    inc bx
sear_cmp:
    push bx
    mov al,ds:[si]
    mov bl,es:[di]
    cmp al,bl
    pop bx
    jne nomatch
    inc si
    inc di
    loop sear_cmp
    jmp sear_suce
nomatch:
    add si,38
    mov di,offset _name
    sub sum,1
    jmp sear_loop4

;查找成功
sear_suce:
    mov cx,bx
    sub cx,1
    mov si,offset tel_tab
_init:
    cmp cx,0
    je _output
    add si,38
    loop _init


_output: 
    add si,25
    push si
    mov si,offset _name
    mov cl,_length
    xor ch,ch
    CF
_out_name:
    mov dl,ds:[si]
    mov ah,02h
    int 21H
    inc si
    loop _out_name

    pop si
    mov cx,11
    mov dl,' '
    mov ah,02h
    int 21H
_out_number:
    mov dl,ds:[si]
    mov ah,02h
    int 21H
    inc si
    loop _out_number
sear_exit:
    pop sum
    ret
;查找失败
sear_fail:
    mov dx,offset temp7
    mov ah,09h
    int 21H
    jmp sear_exit
;表为空
sear_empty:
    mov dx,offset temp6
    mov ah,09h
    int 21H
    jmp sear_exit
sear_man endp

;修改联系人信息
change proc near
    push sum;暂存联系人的人数
    mov dx,offset temp9
    mov ah,09h
    int 21H

    ;输入要寻找的联系人
    mov dx,offset namemax
    mov ah,0ah
    int 21H

    ;取出比较的次数
    mov cl,_length
    xor ch,ch
    ;初始化电话簿的地址
    mov si,offset tel_tab
    add si,2
    mov di,seg _name
    mov es,di
    mov di,offset _name
    mov bx,0
    cmp sum,0
    je change_empty;如果sum一开始就为0，即为空的，肯定找不到
change_loop4:
    cmp sum,0;此时肯定不会满足条件，所以开始寻找
    je change_fail
    inc bx
change_cmp:
    push bx
    mov al,ds:[si]
    mov bl,es:[di]
    cmp al,bl
    pop bx
    jne change_nomatch
    inc si
    inc di
    loop change_cmp
    jmp change_suce
change_nomatch:
    add si,38
    mov di,offset _name
    sub sum,1
    jmp change_loop4
;查找成功
;找到并初始化我们要修改的联系人的位置
change_suce:
    mov cx,bx
    sub cx,1
    mov si,offset tel_tab
change_init:
    cmp cx,0
    je change_main
    add si,38
    loop change_init
    push si;si保存的是我们要修改的联系人的内存位置

change_main: 
    mov dx,offset temp10
    mov ah,09h  
    int 21H

    mov dx,si
    add dx,23
    mov ah,0ah
    int 21H
    
    mov dx,offset temp11
    mov ah,09h
    int 21H

change_exit:
    pop sum
    ret
;查找失败
change_fail:
    mov dx,offset temp7
    mov ah,09h
    int 21H
    jmp change_exit
;表为空
change_empty:
    mov dx,offset temp6
    mov ah,09h
    int 21H
    jmp change_exit

change endp
code ends
end start
