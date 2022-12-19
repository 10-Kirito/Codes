; throw the dice three times,and sort by the number of the dice

assume ds:data,cs:code,ss:stacks

data segment
	sum dw 0
    value1 dw 0
    db '$'
    value2 dw 0
    db '$'
    value3 dw 0
    db '$'
	menu0 db "---------------Throw the dice-----------------",13,10
    menu1 db "---------1. The first people throw.-----------",13,10
    menu2 db "---------2. The second people throw.----------",13,10
    menu3 db "---------3. The third people throw.-----------",13,10
    menu4 db "---------4. Sort.-----------------------------",13,10
    menu5 db "---------0. Exit.-----------------------------",13,10
    menu6 db "Please input number (0~4) : ",'$'
	message1 db "The first people throw the dice, the number is:",'$'
	message2 db "The second people throw the dice, the number is:",'$'
	message3 db "The third people throw the dice, the number is:",'$'
	CRLF db 13,10,'$'
data ends

stacks segment stack
	dw 20 dup(?)
stacks ends

; define macro : enter
output_CRLF macro
    mov 	dx,offset CRLF
    mov 	ah,09h
    int 	21H
endm

; define macro : message 
output_message macro x
    mov     dx,offset x
    mov     ah,09h
    int     21h
endm

; define macro: output the menu
display_menu macro
    mov     dx,offset menu0
    mov     ah,09h
    int     21H
endm

; define block : until input enter
block macro
    block_loop:
    mov     ah,0
    int     16h
    cmp     ah,1ch
    jne     block_loop
endm

code segment
start:
	mov 	ax,data
	mov 	ds,ax
	mov 	ax,stacks
	mov 	ss,ax
main:
    display_menu
    mov     ah,1
    int     21H
    push    ax
    block
    output_CRLF
    pop     ax

    xor     ah,ah  
    cmp     ax,0030h
    je      main_return 
    cmp     ax,0031h
    je      loop_1      ;1. The first people throw.
    cmp     ax,0032h
    je      loop_2      ;2. The second people throw.
    cmp     ax,0033h
    je      loop_3      ;3. The third people throw.
    cmp     ax,0034h
    je      loop_4      ;4. Sort.
    jmp     main

loop_1:
    call    randget
    mov     di,offset value1
    mov     ds:[di],bx
    output_CRLF
    output_message message1
    mov     dl,bl
    mov     ah,2
    int     21h
    output_CRLF
    output_CRLF
    jmp     main
loop_2:
    call    randget
    mov     di,offset value2
    mov     ds:[di],bx
    output_CRLF
    output_message message2
    mov     dl,bl
    mov     ah,2
    int     21h
    output_CRLF
    output_CRLF
    jmp     main
loop_3:
    call    randget
    mov     di,offset value3
    mov     ds:[di],bx
    output_CRLF
    output_message message3
    mov     dl,bl
    mov     ah,2
    int     21h
    output_CRLF
    output_CRLF
    jmp     main
loop_4:
    call    sort
    output_CRLF
    jmp     main




main_return:
	mov 	ah,4ch
	int 	21H

; sort the number of dices
sort proc near
    push    ax
    push    bx
    push    cx
    mov     ax,value1;4
    mov     bx,value2;6
    mov     cx,value3;4
    
    cmp     ax,bx
    jl      b_a
    cmp     bx,cx
    jl      c_b
    output_message message1
    output_message value1
    output_CRLF
    output_message message2
    output_message value2
    output_CRLF
    output_message message3
    output_message value3
    output_CRLF
    jmp     sort_ret
c_b:
    cmp     ax,cx
    jl      c_a_b
    output_message message1
    output_message value1
    output_CRLF
    output_message message3
    output_message value3
    output_CRLF
    output_message message2
    output_message value2
    output_CRLF
    jmp     sort_ret
c_a_b:
    output_message message3
    output_message value3
    output_CRLF
    output_message message1
    output_message value1
    output_CRLF
    output_message message2
    output_message value2
    output_CRLF
    jmp     sort_ret
b_a:
    cmp     ax,cx
    jl      c_a
    output_message message2
    output_message value2
    output_CRLF
    output_message message1
    output_message value1
    output_CRLF
    output_message message3
    output_message value3
    output_CRLF
    jmp     sort_ret
c_a:
    cmp     bx,cx
    jl      c_b_a
    output_message message2
    output_message value2
    output_CRLF
    output_message message3
    output_message value3
    output_CRLF
    output_message message1
    output_message value1
    output_CRLF
    jmp     sort_ret
c_b_a:
    output_message message3
    output_message value3
    output_CRLF
    output_message message2
    output_message value2
    output_CRLF
    output_message message1
    output_message value1
    output_CRLF
    jmp     sort_ret

    ; if a >= b
    ;   if b >= c
    ;       cout << a << b << c;
    ;   else                            // c_b
    ;       if a >= c
    ;           cout << a << c << b;
    ;       else
    ;           cout << c << a << b;
    ; else                              // b_a
    ;   if a >= c
    ;       cout << b << a << c;
    ;   else                            // c_a
    ;       if b >= c
    ;           cout << b << c << a;
    ;       else // b < c
    ;           cout << c << b << a;
    
sort_ret:
    pop     cx
    pop     bx
    pop     ax
    ret
sort endp

; generate the random
; return value is in bx
randget proc near
    call    delay
    push    ax
    push    dx
	mov 	ah,00h
	int 	1ah
	
	mov 	ax,dx	
	and 	ah,3
	mov 	dl,6
	div 	dl
	mov 	al,ah
	xor 	ah,ah
	inc 	ax
	add 	ax,'0'
    mov     bx,ax
    pop     dx
    pop     ax
    ret

randget endp


; delay the time 
delay proc near 
    push    dx
    push    ax
    mov 	dx,0010h
    mov 	ax,0
s1:
    sub 	ax,1
    sbb 	dx,0
    cmp 	ax,0
    jne 	s1
    cmp 	dx,0
    jne 	s1
    pop     ax
    pop     dx
    ret
delay endp
	
code ends
end start

