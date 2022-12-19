; The purpose of this program is to implement a simple tic-tac-toe!

assume ds:data,cs:code,ss:stacks

data segment
	num db 9 dup(0)
    ; The purpose of the parameter flag is to transfer the right of chess
   	; if flag == 0 , it's red's turn to play chess
	; if flag == 1 , it's blue's turn to play chess
    flag db 0
    sum  db 0
    menu db "-----------------------------------------------",13,10
         db "----------------Tictactoe Game!----------------",13,10
         db "----------------1.Start the game.--------------",13,10
         db "----------------0.Quit.------------------------",13,10
         db "-----------------------------------------------",13,10,'$'
    game db "---------HAPPY TIME------------",13,10
         db "+---------+---------+---------+",13,10
         db "|         |         |         |",13,10
         db "|    1    |    2    |    3    |",13,10
         db "|         |         |         |",13,10
         db "+---------+---------+---------+",13,10
         db "|         |         |         |",13,10
         db "|    4    |    5    |    6    |",13,10
         db "|         |         |         |",13,10
         db "+---------+---------+---------+",13,10
         db "|         |         |         |",13,10
         db "|    7    |    8    |    9    |",13,10
         db "|         |         |         |",13,10
         db "+---------+---------+---------+",13,10
    message db "Please input the number you choose: ",'$'
    error db "Input Error,the location has no space!",'$'
    red db "Congratulations to the red team!",'$'
    blue db "Congratulations to the blue team!",'$'
    _no_ db "Come out even!",'$'
     
    CRLF db 13,10,'$'
data ends   

; define macro,output carriage return
_output_CRLF macro
    mov     dx,offset CRLF
    mov     ah,09h  
    int     21h
endm

; define macro, output the game menu
show_menu macro 
    mov 	dx,offset menu
    mov 	ah,09h
    int 	21H
endm 
; define macro, switch the right of chess
change macro
	push 	ax
	mov 	di,offset flag
	mov 	al,ds:[di]
	xor 	ah,ah
	cmp 	ax,0
	je 		set_blue
	mov 	al,0
	mov 	ds:[di],al
	jmp 	change_ret
set_blue:
	mov 	al,1
	mov 	ds:[di],al
change_ret:
	pop 	ax
endm



; define macro, place the cursor at the specified position
post_c  macro y,x           
    mov bh,0       
	mov ah,2         
	mov dh,y       
	mov dl,x         
	int 10h         
endm

; define macro, Clear the screen of the specified range
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

; change the square corresponding to the coordinate to corresponding color
set_color macro a,b,c,d,e
    push    ax
    push    bx
    push    cx
    push    dx
    mov     al,0
    ; 16 is blue 
    ; 64 is red
    mov     bh,e
    mov     ch,b
    mov     cl,a
    mov     dh,d
    mov     dl,c
    mov     ah,6
    int     10h
    pop     dx
    pop     cx
    pop     bx
    pop     ax
endm

; define macro, blocking input program
block macro 
	push 	ax
	push 	dx
block_loop:
	mov     ah,0
    int     16h
    cmp     ah,1ch
    jne     block_loop
    _output_CRLF
    pop  	dx	
    pop 	ax	
endm

block0 macro 
	push 	ax
	push 	dx
block0_loop:
	mov     ah,0
    int     16h
    cmp     ah,1ch
    jne     block0_loop
    _output_CRLF
    pop  	dx	
    pop 	ax	
endm

stacks segment stack
    dw 20 dup(?)
stacks ends

code segment 
start: 
    mov     ax,data
    mov     ds,ax
    mov     ax,stacks
    mov     ss,ax
main_loop:
	xor 	si,si
    clear   0,0,24,79
    post_c  0,0
    _output_CRLF
	show_menu

    mov 	ah,1
    int 	21h	
    ; input
    block
    xor	 	ah,ah	
    cmp 	ax,0030h
    je 		main_return
    cmp 	ax,0031h
    je 		_game_loop
    jmp 	main_loop
    
    ; into the game 
_game_loop:
	; clear the screen
	clear   0,0,24,79
	; place the cursor at (0,0)
    post_c  0,0
	; display the game-menu
    call show_map
_game_ing:
    call input_number
	call update_map
	change
	call judge_game
	cmp 	bx,1
	je	 _red_suc
	cmp	  	bx,2
	je 	 _blue_suc
	
	mov 	di,offset sum
	mov 	al,ds:[di]
	xor 	ah,ah
	cmp 	si,9
	je 		_no_team
	jmp  	_game_ing
_red_suc:
	post_c 	15,0
	mov 	dx,offset red
	mov 	ah,09h
	int 	21h
	jmp 	main_return
_no_team:
	post_c 	15,0
	mov 	dx,offset _no_
	mov 	ah,09h
	int 	21h
	jmp 	main_return 
_blue_suc:
	post_c 	15,0
	mov 	dx,offset blue
	mov 	ah,09h
	int 	21h
    ; The coordinates corresponding to the 9 squares
    ; 1: 2,2,8,4
    ; 2: 12,2,18,4
    ; 3: 22,2,28,4
    ; 4: 2,6,8,8
    ; 5: 12,6,18,8
    ; 6: 22,6,28,8
    ; 7: 2,10,8,12
    ; 8: 12,10,18,12
    ; 9: 22,10,28,12
    
main_return:
    mov     ah,4CH
    int     21H

; show game menu
show_map proc near	
	push 	dx
	push 	ax
	mov     dx,offset game
    mov     ah,09h
    int     21H
     
    pop 	ax	
    pop 	dx	
	ret
show_map endp	

; flag : num db 9 dup(0)
; input characters and change the corresponding flag bit
; if the red side is playing chess,the flag position is 1
; if the blue side is playing chess, the flag position is 2
; if there is nothing in the position, it will be 0
; if the position is already occipied by someone else ,an error message will be displayed,and the input should be re-entered
input_number proc near
	push 	ax
	push 	dx	
input:
    mov 	ah,01h
    int 	21h
	block0
   	xor 	ah,ah
   	sub 	ax,48
   	cmp 	ax,0
   	je 		input_error
   	
   	mov 	di,offset num
   	sub 	ax,1
   	cmp 	ax,0
   	je 		find_ed ; Find the flag corresponding to the square
   	mov 	cx,ax
find_ing:
	inc 	di
	loop 	find_ing
find_ed:
	
	; check if the square has already been placed
   	mov 	al,ds:[di]
   	xor 	ah,ah
   	push 	di
   	cmp 	ax,0
   	je 		set_ok
   	jmp 	input_error
  	; this square is not played
set_ok:
	inc 	si
	push 	di
	push 	ax
	
	mov 	di,offset sum
	mov 	al,ds:[di]
	inc 	al
	mov 	ds:[di],al
	pop 	ax
	pop 	di
	mov 	di,offset flag
	mov 	al,ds:[di]
	xor 	ah,ah
	cmp 	ax,0
	je 		input_red
	pop 	di
	mov 	al,2
	mov 	ds:[di],al
	jmp 	input_return
	
input_red:
	pop 	di
	mov 	al,1
	mov 	ds:[di],al
	jmp 	input_return	

input_error:
	mov 	dx,offset error
	mov 	ah,09h
	int 	21h
	call 	delay
	jmp 	input

input_return:
	pop 	dx
	pop 	ax
	ret
input_number endp

; delay the program ,let the error message disappear after a while
delay proc near
    push ax
    push dx 
    mov dx,0012h
    mov ax,0
s1:
    sub ax,1
    sbb dx,0
    cmp ax,0
    jne s1
    cmp dx,0
    jne s1
    pop dx
    pop ax
    ret
delay endp

; update map
update_map proc near
    push    ax
    push    dx
    push    bx

    clear   0,0,20,38
    post_c  0,0
    mov     dx,offset game
    mov     ah,09h
    int     21H
    
    mov     di,offset num
    
	; update the first square
set_color_1:
    mov 	al,ds:[di]
    xor 	ah,ah
    cmp 	ax,0
    je 		_white_1
    cmp     ax,1
    je      _red_1
    set_color   2,2,8,4,16 ; blue
    jmp 	set_color_2
_white_1:
    set_color   2,2,8,4,0  ; white
    jmp 	set_color_2
_red_1:
	set_color   2,2,8,4,64 ; red
	
	; update the second square
set_color_2:
	inc 	di
    mov 	al,ds:[di]
    xor 	ah,ah
    cmp 	ax,0
    je 		_white_2
    cmp     ax,1
    je      _red_2
    set_color   12,2,18,4,16 ; blue
    jmp 	set_color_3
_white_2:
    set_color   12,2,18,4,0  ; white
    jmp 	set_color_3
_red_2:
	set_color   12,2,18,4,64 ; red
	
	; update the third square
set_color_3:
inc 	di
    mov 	al,ds:[di]
    xor 	ah,ah   
    cmp 	ax,0
    je 		_white_3
    cmp     ax,1
    je      _red_3
    set_color   22,2,28,4,16 ; blue
    jmp 	set_color_4
_white_3:
    set_color   22,2,28,4,0  ; white
    jmp 	set_color_4
_red_3:
	set_color   22,2,28,4,64 ; red
	
	; update the forth square
set_color_4:
	inc 	di
    mov 	al,ds:[di]
    xor 	ah,ah
    cmp 	ax,0
    je 		_white_4
    cmp     ax,1
    je      _red_4
    set_color   2,6,8,8,16 ; blue
    jmp 	set_color_5
_white_4:
    set_color   2,6,8,8,0  ; white

    jmp 	set_color_5
_red_4:
	set_color   2,6,8,8,64 ; red
	
	; set the fifth square
set_color_5:
	inc 	di
    mov 	al,ds:[di]
    xor 	ah,ah
    cmp 	ax,0
    je 		_white_5
    cmp     ax,1
    je      _red_5
    set_color   12,6,18,8,16 ; blue
    jmp 	set_color_6
_white_5:
    set_color   12,6,18,8,0  ; white
    jmp 	set_color_6
_red_5:
	set_color   12,6,18,8,64 ; red
	
	; set the sixth square
set_color_6:
	inc 	di
    mov 	al,ds:[di]
    xor 	ah,ah
    cmp 	ax,0
    je 		_white_6
    cmp     ax,1
    je      _red_6
    set_color   22,6,28,8,16 ; blue
    jmp 	set_color_7
_white_6:
    set_color   22,6,28,8,0  ; white
    jmp 	set_color_7
_red_6:
	set_color   22,6,28,8,64 ; red
	
	; set the seventh square
set_color_7:
	inc 	di
    mov 	al,ds:[di]
    xor 	ah,ah
    cmp 	ax,0
    je 		_white_7
    cmp     ax,1
    je      _red_7
    set_color   2,10,8,12,16 ; blue
    jmp 	set_color_8
_white_7:
    set_color   2,10,8,12,0  ; white
    jmp 	set_color_8
_red_7:
	set_color   2,10,8,12,64 ; red
	
	; set the eighth square
set_color_8:
	inc 	di
    mov 	al,ds:[di]
    xor 	ah,ah
    cmp 	ax,0
    je 		_white_8
    cmp     ax,1
    je      _red_8
    set_color   12,10,18,12,16 ; blue
    jmp 	set_color_9
_white_8:
    set_color   12,10,18,12,0  ; white
    jmp 	set_color_9
_red_8:
	set_color   12,10,18,12,64 ; red
	
	; set the ninth square
set_color_9:
	inc 	di
    mov 	al,ds:[di]
    xor 	ah,ah
    cmp 	ax,0
    je 		_white_9
    cmp     ax,1
    je      _red_9
    set_color   22,10,28,12,16 ; blue
    jmp 	update_return
_white_9:
    set_color   22,10,28,12,0  ; white
    jmp 	update_return
_red_9:
	set_color   22,10,28,12,64 ; red
	
update_return:
	pop 	bx	
	pop 	dx	
	pop 	ax	
	
    ret
update_map endp

; determine if the game is over
; the return value is stored in register BX and SI
; if si == 9, draw
; if bx == 1, red side wins
; if bx == 2, blue side wins
judge_game proc near

judge_0:
    ; take the first row of three numbers for comparison
    mov 	di,offset num
    mov 	al,ds:[di]
    xor 	ah,ah
   	inc 	di
   	mov 	bl,ds:[di]
   	xor 	bh,bh
   	inc 	di
   	mov 	cl,ds:[di]
   	xor 	ch,ch
   	cmp 	ax,bx
   	jne 	judge_1
   	cmp 	bx,cx
   	jne 	judge_1
   	; the three numbers are the same, indicating that one side may wins
   	cmp 	ax,0
   	je		judge_1
   	cmp 	ax,1
   	je		judge_red
   	jmp	 	judge_blue
judge_1:
   	; take the second row of three numbers for comparison
   	inc 	di
   	mov 	al,ds:[di]
    xor 	ah,ah
    inc 	di
   	mov 	bl,ds:[di]
   	xor 	bh,bh
   	inc 	di
   	mov 	cl,ds:[di]
   	xor 	ch,ch
   	cmp 	ax,bx
   	jne 	judge_2
   	cmp 	bx,cx
   	jne 	judge_2
   	; the three numbers are the same, indicating that one side may wins
   	cmp 	ax,0
   	je		judge_2
   	cmp 	ax,1
   	je		judge_red
   	jmp	 	judge_blue
judge_2:
   	; take the third row of three numbers for comparison
   	inc 	di
   	mov 	al,ds:[di]
    xor 	ah,ah
    inc 	di
   	mov 	bl,ds:[di]
   	xor 	bh,bh
   	inc 	di
   	mov 	cl,ds:[di]
   	xor 	ch,ch
   	cmp 	ax,bx
   	jne 	judge_3
   	cmp 	bx,cx
   	jne 	judge_3
   	; the three numbers are the same, indicating that one side may wins
   	cmp 	ax,0
   	je		judge_3
   	cmp 	ax,1
   	je		judge_red
   	jmp	 	judge_blue
judge_3:
   	; get the three numbers in the first column
   	mov 	di,offset num
   	mov 	al,ds:[di]
   	xor 	ah,ah
   	
   	add 	di,3
   	mov 	bl,ds:[di]
   	xor 	bh,bh
   	
   	add 	di,3
   	mov 	cl,ds:[di]
   	xor 	ch,ch
   	cmp 	ax,bx
   	jne 	judge_4
   	cmp 	bx,cx
   	jne 	judge_4
   	; the three numbers are the same, indicating that one side may wins
   	cmp 	ax,0
   	je		judge_4
   	cmp 	ax,1
   	je		judge_red
   	jmp	 	judge_blue
judge_4:
   	; get the three numbers in the second column
   	mov 	di,offset num
   	inc 	di
   	mov 	al,ds:[di]
   	xor 	ah,ah
   	
   	add 	di,3
   	mov 	bl,ds:[di]
   	xor 	bh,bh
   	
   	add 	di,3
   	mov 	cl,ds:[di]
   	xor 	ch,ch
   	cmp 	ax,bx
   	jne 	judge_5
   	cmp 	bx,cx
   	jne 	judge_5
   	; the three numbers are the same, indicating that one side may wins
   	cmp 	ax,0
   	je		judge_5
   	cmp 	ax,1
   	je		judge_red
   	jmp	 	judge_blue
   	
judge_5:
   	; get the three numbers in the third column
   	mov 	di,offset num
   	add 	di,2
   	mov 	al,ds:[di]
   	xor 	ah,ah
   	
   	add 	di,3
   	mov 	bl,ds:[di]
   	xor 	bh,bh
   	
   	add 	di,3
   	mov 	cl,ds:[di]
   	xor 	ch,ch
   	cmp 	ax,bx
   	jne 	judge_6
   	cmp 	bx,cx
   	jne 	judge_6
   	; the three numbers are the same, indicating that one side may wins
   	cmp 	ax,0
   	je		judge_6
   	cmp 	ax,1
   	je		judge_red
   	jmp	 	judge_blue 	
judge_6:
   	; take out the three diagonal numbers
   	mov 	di,offset num
   	mov 	al,ds:[di]
   	xor 	ah,ah
   	
   	add 	di,4
   	mov 	bl,ds:[di]
   	xor 	bh,bh
   	
   	add 	di,4
   	mov 	cl,ds:[di]
   	xor 	ch,ch
   	cmp 	ax,bx
   	jne 	judge_7
   	cmp 	bx,cx
   	jne 	judge_7
   	; the three numbers are the same, indicating that one side may wins
   	cmp 	ax,0
   	je		judge_7
   	cmp 	ax,1
   	je		judge_red
   	jmp	 	judge_blue
   	
judge_7:
   	; take out the three diagonal numbers
	mov 	di,offset num
	add 	di,2
	mov 	al,ds:[di]
	xor 	ah,ah
	
	add 	di,2
	mov 	bl,ds:[di]
	xor 	bh,bh
	
	add 	di,2
	mov 	cl,ds:[di]
	xor 	ch,ch
	cmp 	ax,bx
   	jne 	judge_no
   	cmp 	bx,cx
   	jne 	judge_no
   	; the three numbers are the same, indicating that one side may wins
   	cmp 	ax,0
   	je		judge_no
   	cmp 	ax,1
   	je		judge_red
   	jmp	 	judge_blue
	   	
judge_no:
	xor 	bx,bx
	mov 	bx,0
	jmp		judge_game_return
judge_red:
	xor		bx,bx	
	mov 	bx,1
	jmp		judge_game_return
judge_blue:
    xor	 	bx,bx
    mov 	bx,2
judge_game_return:
    ret
judge_game endp

code ends
end start

