; throw the dice three times,and sort by the number of the dice

assume ds:data,cs:code,ss:stacks

data segment
	sum dw 0
	message0 db "Please input the number of people :" ,'$'
	message1 db "The first people throw the dice, the number is:",'$'
	message2 db "The second people throw the dice, the number is:",'$'
	message3 db "The third people throw the dice, the number is:",'$'
	CRLF db 13,10,'$'
data ends

stacks segment stack
	dw 20 dup(?)
stacks ends

; define macro : enter
CF macro
    mov 	dx,offset CRLF
    mov 	ah,09h
    int 	21H
endm

randget macro
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
	mov 	dl,al
	mov 	ah,2
	int 	21h
endm

code segment
start:
	mov 	ax,data
	mov 	ds,ax
	mov 	ax,stacks
	mov 	ss,ax
main:
	mov 	dx,offset message0
	mov 	ah,09h
	int 	21H
	; input the number of the people
	xor 	bx,bx
	call 	input
	; store the num into the member
	mov 	si,offset sum
	mov 	ds:[si],bx
    mov 	cx,bx
    
    mov 	dx,offset message1
    mov 	ah,09h
    int 	21h
    randget
    call delay
    CF
    
    mov 	dx,offset message2
    mov 	ah,09h
    int 	21h
    randget
    call delay
    CF
    
    mov 	dx,offset message3
    mov 	ah,09h
    int 	21h
    randget
    call delay
    CF
    
    
	mov 	ah,4ch
	int 	21h




; delay the time 
delay proc near 
    mov 	dx,0010h
    mov 	ax,0
s1:
    sub 	ax,1
    sbb 	dx,0
    cmp 	ax,0
    jne 	s1
    cmp 	dx,0
    jne 	s1
    ret
delay endp
	

;�����ӳ���bxΪ���ڲ���
input proc
    push 	ax;��ջ
    push 	cx
    push	dx
    xor 	cx,cx
    mov 	bx,0
L2:
    mov 	ah,01h
    int 	21h
    cmp 	al,30h	; judge the number if belong 0~9
    jb 	L1
    cmp 	al,39h
    ja 	L1
    sub 	al,48	; convert to base 10
    mov 	cl,al	
    mov 	al,bl	
    mov 	dh,10
    mul 	dh
    add 	ax,cx
    mov 	bx,ax	; bx store the input number 
    jmp L2
L1:
    pop 	dx
    pop 	cx
    pop 	ax    
    ret
input endp

;out put the num (base 10)
output proc
	; preserve the scence
	push 	ax
	push 	cx
	push 	dx
		
	; init
	mov 	ax,bx
	mov 	cl,10
	mov 	ch,0
	
divagain:
	cmp 	ax,0
	je 	divover
	inc 	ch 		; count++
	div 	cl
	push 	ax 		; stack protection,use al when using the data
	mov 	ah,0	; init ax 
	jmp divagain;�ٴγ�����������
		
divover:
	cmp 	ch,0
	je 	outputover
	pop 	ax
	mov 	dl,ah
	add 	dl,48
	mov 	ah,2
	int 	21h
	dec 	ch
	jmp divover 
		
		
outputover:
	pop 	dx
	pop 	cx
	pop 	ax
	ret
output endp

code ends
end start



