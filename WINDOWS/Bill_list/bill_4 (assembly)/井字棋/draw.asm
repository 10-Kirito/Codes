dseg segment
      center_x dw 150             ;ԭ������_x
      center_y dw 90              ;ԭ������_y
      radius   dw 50              ;�뾶_r
      label_x  dw ?               ;����������ұ߽�
      label_y  dw ?               ;����������±߽�
      distance dw ?
dseg ends
cseg segment
      assume cs:cseg , ds:dseg
start:
      mov ax , dseg               ;װ��ds��
      mov ds , ax

      mov ah , 0                  ;����ͼ����ʾģʽ4
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
      dec dx                   ;����һ������

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
      mov ah , 0ch             ;0c���ӹ���
      int 10h
next:
      inc cx
      jmp column

exit:
		
	  mov ah , 0                  ;����ͼ����ʾģʽ4
      mov al , 03h
      int 10h
      mov ax , 4c00h
      int 21h

cseg ends
end  start
