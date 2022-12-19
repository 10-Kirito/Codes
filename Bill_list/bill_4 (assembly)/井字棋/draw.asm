dseg segment
      center_x dw 150             ;原点坐标_x
      center_y dw 90              ;原点坐标_y
      radius   dw 50              ;半径_r
      label_x  dw ?               ;外接正方形右边界
      label_y  dw ?               ;外接正方形下边界
      distance dw ?
dseg ends
cseg segment
      assume cs:cseg , ds:dseg
start:
      mov ax , dseg               ;装载ds段
      mov ds , ax

      mov ah , 0                  ;设置图形显示模式4
      mov al , 04h
      int 10h

      mov ax , center_x
      add ax , radius
      mov label_x , ax
      mov ax , center_y
      add ax , radius
      mov label_y , ax
      mov ax , radius
      mul ax
      mov distance , ax

      mov dx , center_y        ;mov dx , [0002]
      sub dx , radius
      dec dx                   ;增加一行余量

row:
      inc dx
      cmp dx , label_y
      ja  exit
      mov cx , center_x
      sub cx , radius
column:
      cmp cx , label_x
      ja  row

      push dx
      mov ax , dx
      sub ax , center_y
      imul ax

      mov bx , ax

      mov ax , cx
      sub ax , center_x
      imul ax

      pop dx
      add ax , bx
      cmp ax , distance
      ja  next
      mov al , 02              ;color
      mov ah , 0ch             ;0c号子功能
      int 10h
next:
      inc cx
      jmp column

exit:
		
	  mov ah , 0                  ;设置图形显示模式4
      mov al , 03h
      int 10h
      mov ax , 4c00h
      int 21h

cseg ends
end  start
