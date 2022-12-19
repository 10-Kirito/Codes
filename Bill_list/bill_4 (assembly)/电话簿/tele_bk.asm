; �ó���ʵ���˵绰���Ļ������ܣ�
; ��ɾ���
; ��������绰��
assume ds:data,cs:code,ss:stacks
data segment
    sum dw 0        ;��¼��ǰ�绰�����ж�����ϵ��
    namemax db 20   ;�����洢��ʱ�������ϵ������
    _length db ?
    _name db 20 dup(' ')
    tel_tab db 80 dup(20,?,20 dup(' '),32,12,?,12 dup(0),32);�洢�����͵绰����
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

; ����꣬����˵�
show_menu macro 
    mov dx,offset menu
    mov ah,09h
    int 21H
endm 

;�����ָ�����������
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
;���ù���� (y��x)λ�ã����ù������λ��
post_c  macro y,x           
    mov bh,0       
	mov ah,2         
	mov dh,y       
	mov dl,x         
	int 10h         
endm

; ����꣬�س�
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
    clear 0,0,24,79 ; ����
    post_c 0,0
main_loop0:
    show_menu ; ����˵�
    mov ah,1 ;�Ӽ�����������ѡ��
    int 21H     
    push ax

    block_loop:
    mov     ah,0
    int     16h
    cmp     ah,1ch
    jne     block_loop

    CF                  ;����س�
    pop ax
    xor ah,ah
    cmp ax,0030h
    je return           ;����������0�����������
    cmp ax,0031h
    je loop1            ;����������1��2��3��4,5��������ӳ���
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

;���������ϵ��
show_book proc near
    mov dx,offset temp8
    mov ah,09h
    int 21h

    push sum
    cmp sum,0
    je show_empty  	;����绰��Ϊ�յĻ��������Ӧ��Ϣ
    mov cx,sum
    

    mov si,offset tel_tab
show_big:
    push cx			;���ѭ��������ÿһλ��ϵ��
    add si,1
    mov cl,ds:[si]
    xor ch,ch
    add si,1
    push si
show_name:			;�������
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
show_phonenum:		;����绰����
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

add_man proc near	;�����ϵ��
    lea dx,temp
    mov ah,09h  
    int 21H
    mov dx,offset tel_tab
    push sum
init:				;��ʼ������ϵ�˴�ŵ��ڴ�λ��
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
    
    inc sum			;��������һ
    ret
add_man endp

;ɾ����ϵ��
del_man proc near
    push sum;�ݴ���ϵ�˵�����
    
    mov dx,offset method_0
    mov ah,09h
    int 21H

    ;����Ҫɾ������ϵ��
    mov dx,offset namemax
    mov ah,0ah
    int 21H

    cmp sum,1
    je dele_brige2

    ;ȡ���ȽϵĴ���
    mov cl,_length
    xor ch,ch
    ;��ʼ���绰���ĵ�ַ
    mov si,offset tel_tab
    add si,2
    mov di,seg _name
    mov es,di
    mov di,offset _name
    mov bx,0		;����������¼����Ҫɾ������ϵ�˵�λ��
    cmp sum,0
    je dele_brige	;���sumһ��ʼ��Ϊ0����Ϊ�յģ��϶��Ҳ���
dele_loop4:
    cmp sum,0		;��ʱ�϶������������������Կ�ʼѰ��
    je dele_brige1	;������ת��λ�þ���˴�̫Զ������Ҫ����
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
;���ҳɹ�
;�ҵ�����ʼ������Ҫɾ������ϵ�˵�λ��
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
;��ʼ�����һλ��ϵ�˵�λ��
    pop cx;ȡ����ǰ��ϵ�˵�������
    push cx

    mov di,seg _name
    mov es,di
    mov di,offset tel_tab
    sub cx,1;�����ǰ������Ϊ1�Ļ����Ͳ���Ҫѭ����ʼ��
    cmp cx,0
    je _exchange
dele_loop:
    add di,38
    loop dele_loop
    push si
    push di
;�������һλ��ϵ�˺�����Ҫɾ������ϵ�˵�����λ��
_exchange:
    mov cx,22
_xchange:
    mov al,es:[di]
    mov byte ptr ds:[si],al
    inc di
    inc si
    loop _xchange
    ;������Ӧ��ϵ�˵绰����
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
;ɾ��һ����ϵ��֮������������
    sub sum,1
    ret
dele_only:
    mov dx,offset temp11
    mov ah,09h
    int 21H
    pop sum
    sub sum,1
    ret
;����ʧ��
dele_fail:
    mov dx,offset temp7
    mov ah,09h
    int 21H
    pop sum
    ret
;��Ϊ��
dele_empty:
    mov dx,offset temp6
    mov ah,09h
    int 21H
    pop sum
    ret
del_man endp

;Ѱ����ϵ��
sear_man proc near
    push sum;�ݴ���ϵ�˵�����
    mov dx,offset method
    mov ah,09h
    int 21H

    ;����ҪѰ�ҵ���ϵ��
    mov dx,offset namemax
    mov ah,0ah
    int 21H

    ;ȡ���ȽϵĴ���
    mov cl,_length
    xor ch,ch
    ;��ʼ���绰���ĵ�ַ
    mov si,offset tel_tab
    add si,2
    mov di,seg _name
    mov es,di
    mov di,offset _name
    mov bx,0
    cmp sum,0
    je sear_empty;���sumһ��ʼ��Ϊ0����Ϊ�յģ��϶��Ҳ���
sear_loop4:
    cmp sum,0;��ʱ�϶������������������Կ�ʼѰ��
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

;���ҳɹ�
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
;����ʧ��
sear_fail:
    mov dx,offset temp7
    mov ah,09h
    int 21H
    jmp sear_exit
;��Ϊ��
sear_empty:
    mov dx,offset temp6
    mov ah,09h
    int 21H
    jmp sear_exit
sear_man endp

;�޸���ϵ����Ϣ
change proc near
    push sum;�ݴ���ϵ�˵�����
    mov dx,offset temp9
    mov ah,09h
    int 21H

    ;����ҪѰ�ҵ���ϵ��
    mov dx,offset namemax
    mov ah,0ah
    int 21H

    ;ȡ���ȽϵĴ���
    mov cl,_length
    xor ch,ch
    ;��ʼ���绰���ĵ�ַ
    mov si,offset tel_tab
    add si,2
    mov di,seg _name
    mov es,di
    mov di,offset _name
    mov bx,0
    cmp sum,0
    je change_empty;���sumһ��ʼ��Ϊ0����Ϊ�յģ��϶��Ҳ���
change_loop4:
    cmp sum,0;��ʱ�϶������������������Կ�ʼѰ��
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
;���ҳɹ�
;�ҵ�����ʼ������Ҫ�޸ĵ���ϵ�˵�λ��
change_suce:
    mov cx,bx
    sub cx,1
    mov si,offset tel_tab
change_init:
    cmp cx,0
    je change_main
    add si,38
    loop change_init
    push si;si�����������Ҫ�޸ĵ���ϵ�˵��ڴ�λ��

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
;����ʧ��
change_fail:
    mov dx,offset temp7
    mov ah,09h
    int 21H
    jmp change_exit
;��Ϊ��
change_empty:
    mov dx,offset temp6
    mov ah,09h
    int 21H
    jmp change_exit

change endp
code ends
end start
