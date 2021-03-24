; align 32 bit variables to 32-bits
; align op codes to 16 bits
       THUMB
       AREA    DATA, ALIGN=4 
       EXPORT  M [DATA,SIZE=4]
M      SPACE   4
		EXPORT N [DATA,SIZE=4]
N		SPACE 4
                 
       AREA    |.text|, CODE, READONLY, ALIGN=2
       EXPORT  Start
Start  LDR R2,=M       ; R2 = &M, R2 points to M
       MOV R0,#1       ; Initial seed
       STR R0,[R2]     ; M=1
	   LDR R2, =N
	   MOV R0, #2048
	   STR R0, [R2]

loop   	LDR R1, =N
		LDR R0, [R1]
		LSR R0, R0, #2
		LDR R2, =M
		STR R0, [R2]
		
       B   loop
;------------Random------------
; Return R0= random number
; Linear congruential generator 
; from Numerical Recipes by Press et al.
Random LDR R2,=M    ; R2 = &M, R2 points to M
       LDR R0,[R2]  ; R0=M
       LDR R1,=1664525
       MUL R0,R0,R1 ; R0 = 1664525*M
       LDR R1,=1013904223
       ADD R0,R1    ; 1664525*M+1013904223 
       STR R0,[R2]  ; store M
       BX  LR
       ALIGN      
       END  
           