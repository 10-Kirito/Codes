      M1 EQU 2           ; Upper limit of the number,m
      N EQU 6            ; the number of people,n
DATA SEGMENT
      SOURCE DB 01H,02H,03H,04H,05H,06H   ; number of the corresponding persion
      RESULT DB N DUP(0)                  ; A Boolean array that stores the current state of each person. 
                                          ; The initial value is 0,what we have here is the result
      M      DB 00H                       ; Control the times of outputs
      M2     DB 00H                       ; to store the index of the results
DATA ENDS

SSEG SEGMENT PARA STACK 'STACK'
      DB  256 DUP(?)
SSEG ENDS

CODE SEGMENT
      ASSUME CS:CODE,DS:DATA,SS:SSEG,ES:DATA
START:
      PUSH DS
      XOR AX,AX
      PUSH AX     ; This corresponds to retf at the end
      MOV AX,DATA
      MOV DS,AX
      MOV ES,AX 

      MOV DH,0    ; store the value of k into DH
      MOV DL,N    ; store the value of N into DL
      CMP DL,1    ; compare DL(N) to 1,if it's equal to 1,break out of the loop
      JZ LOP2
LOP1: 
      MOV AL,M1   ; store the value of m into AL
      CMP AL,DL   ; the mod operation in assembly first determines the size of m and n ,if m < n ,then the end value is m
      JB LOP4     ; Otherwise, you just use substraction to get the remainder

LOP3: 
      SUB AL,DL   
      CMP AL,DL
      JNB LOP3
      ; LOP4, this is the case where m is less than n, m is the result and AL is storing the result
LOP4: 
      CMP DH,0    ; if (k != 0)   
      JE  LOP5    
      ADD AL,DH   ; s = (s + k - 2) % n + 1
      SUB AL,2    
      CMP AL,DL
      JB LOP6
ALOP:
      SUB AL,DL
      CMP AL,DL
      JNB ALOP
LOP6: 
      ADD AL,1
LOP5: 
      MOV AH,0    ; store the value of AL(s) into AL
      MOV CL,AL   ; store the value of AL(s) into CL
      DEC AL      ; s - 1
      MOV BX,AX   
      MOV AL,SOURCE[BX]       ; printf(" %d ",a[s-1])
      MOV BL,M2               ; int the begining ,the value is 0
      MOV BH,0
      MOV RESULT[BX],AL       ; Store the number of the first person to die
      INC BL
      MOV M2,BL               ; add the subscript of M2 to one
      MOV AL,CL               
      SUB AL,1                ; i = s - 1
      MOV CH,AL               ; CH ---> i
                              ; for(i=s-1;i<n-1;i++)a[i]=a[i+1]
      MOV AL,DL               ; AL ---> n
      SUB AL,1                ; AL ---> n-1
      CMP CH, AL              ; compare the sizes of i and n - 1,and exit the loop if i is less than n - 1
      JNB LOP7                ; not less than
LOP8:                         ; enter the loop
      MOV AL,CH
      MOV AH,0
      MOV BX,AX
      MOV AL,SOURCE[BX+1]
      MOV SOURCE[BX],AL    
      INC CH
      MOV AL,DL
      SUB AL,1
      CMP CH, AL              ; i < n-1
      JB LOP8
LOP7:                         ; exit the loop
      MOV DH,CL               ; k=s
      DEC DL                  ; n--
      CMP DL,1                ; if DL == 1 ,exit the loop
      JNE LOP1
LOP2: 
      MOV BX,0
      MOV AL,SOURCE[BX]       ; printf(" %d ",a[0])
      MOV BX,N-1              ; The last person's subscript
      MOV RESULT[BX],AL       
      LEA DI,RESULT
      MOV M,N                 ; M ---> N ,the number of people

LOP0:                         ; The following sections output, in turn, what is stored in result
      MOV AL,[DI]
      AND AL,0F0H
      MOV CL,4
      SHR AL,CL               ; Remove the high number
      CMP AL,9                
      JA X1                   ; if AL > 9
      ADD AL,30H              ; AL <= 9,The high digit of the output number 
      MOV BL,AL               ;                 ^
      MOV AH,02H              ;                 |
      MOV DL,BL               ;                 |
      INT 21H                 ; Print the number of the first person to die
      JMP X2

      ; 
X1:                           ; The high number is greater than 9,即 10，11，12，13，14，15
      CMP AL,61H              ; 
      JA X5
      ADD AL,40H              ; ASCII values of letters corresponding to hexadecimal digits
      SUB AL,09H
      MOV BL,AL
      MOV AH,02H
      MOV DL,BL
      INT 21H
      JMP X2
X5:                           ; > 61
      ADD AL,20H
      MOV BL,AL
      MOV AH,02H
      MOV DL,BL
      INT 21H
X2:                           ; Take out the lower four digits of the number
      MOV AL,[DI]
      AND AL,0FH
      CMP AL,9
      JA X3
      ADD AL,30H              ; Print the number of the first person to die
      MOV BL,AL
      MOV AH,02H
      MOV DL,BL
      INT 21H
      JMP X6
X3:   
      CMP AL,61H
      JA X4
      ADD AL,40H
      SUB AL,09H
      MOV BL,AL
      MOV AH,02H
      MOV DL,BL
      INT 21H
      JMP X6
X4:   
      ADD AL,20H
      MOV BL,AL
      MOV AH,02H
      MOV DL,BL
      INT 21H
X6:   
      INC DI
      DEC M
      JNZ LOP0
      RETF
CODE ENDS
END START
