        ; 8080 assembler code
        .hexfile Sort.hex
        .binfile Sort.com
        ; try "hex" for downloading in hex format
        .download bin  
        .objcopy gobjcopy
        .postbuild echo "OK!"
        ;.nodump

	; OS call list
PRINT_B		equ 1
PRINT_MEM	equ 2
READ_B		equ 3
READ_MEM	equ 4
PRINT_STR	equ 5
READ_STR	equ 6
GET_RND		equ 7

	; Position for stack pointer
stack   equ 0F000h

	org 000H
	jmp begin

	; Start of our Operating System
GTU_OS:	PUSH D
	push D
	push H
	push psw
	nop	; This is where we run our OS in C++, see the CPU8080::isSystemCall()
		; function for the detail.
	pop psw
	pop h
	pop d
	pop D
	ret
	; ---------------------------------------------------------------
	; YOU SHOULD NOT CHANGE ANYTHING ABOVE THIS LINE        

	;This program adds numbers from 0 to 10. The result is stored at variable
	; sum. The results is also printed on the screen.

sum	ds 2 ; will keep the sum
numbers ds 50;
curr	ds 1;
loopCounter	ds 1;
newLine:	dw "",00AH,00H

begin:
	LXI SP,stack 	; always initialize the stack pointer
	mvi c, 50	; init C with 50
	LXI D,numbers

	mvi a, 0	; A = 0
	STA loopCounter
ReadNumbersloop:
	

	MVI A, GET_RND	; store the OS call code to A
	call GTU_OS	; call the OS

	MOV A,B
	STAX D;
	INX D;

	DCR c		; --C
	JNZ ReadNumbersloop	; goto ReadNumbersloop if C!=0

loopStart:

mvi e, 50
LXI B,numbers
LDAX B;
STA curr;
INX B;

JMP loopSort

swap: 			; mem[1] < D==mem[0] 	BC==memAddr == 1   swap mem[0]<->mem[1]
	LDAX B 		; A = mem[bc] = mem[1]
	MOV D,A 	; D = mem[1]
	DCX B 		; BC = BC -1 
	LDAX B 		; A = mem[bc] = mem[1]
	MOV H,A		; H = mem[0]
	MOV A,D 	; A = D
	STAX B 		; mem[0] = mem[1]
	INX B 		; BC = BC + 1 
	MOV A,H 	; A = mem[0]
	STAX B 		; mem[1] = mem[0]
	jmp afterSwap

loopSort:
	
	;MVI a, PRINT_MEM
	;call GTU_OS	; call the OS

	LDA curr	; A = curr
	MOV D,A 	; D=curr;


	LDAX B 		; A = mem[bc]

	SUB D		; A=A-Reg
	JC swap		; if A-D < 0 : JMP swap
afterSwap:
	LDAX B 		; A = mem[bc]
	STA curr	; curr = A  	A is big one always
	INX B
	DCR e		; --E
	JNZ loopSort	; goto loopSort if E!=0



LDA loopCounter
INR A
STA loopCounter
SUI 49
JC loopStart



mvi e, 50
LXI B,numbers
printAll:
	
	MVI a, PRINT_MEM
	call GTU_OS	; call the OS
	PUSH B

	LXI B, newLine	; put the address of string in registers B and C
	MVI A, PRINT_STR	; store the OS call code to A
	call GTU_OS	; call the OS
	

	POP B
	INX B;
	DCR e		; --E
	JNZ printAll	; goto printAll if E!=0

hlt		; end program
