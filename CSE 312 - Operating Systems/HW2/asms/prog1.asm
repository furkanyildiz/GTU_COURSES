        ; 8080 assembler code
        .hexfile prog1.hex
        .binfile prog1.com
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
TExit		equ 8
TJoin		equ 9
TYield		equ 10
TCreate		equ 11

MAX_VAL_F1     equ 51
MAX_VAL_F3     equ 101

	; Position for stack pointer
stack   equ 0F000h

	org 000H
	jmp main_prog

	; Start of our Operating System
GTU_OS:	PUSH D 		;PC=3
	push D 			;;PC=4
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


main_prog:
	LXI SP,stack 		; always initialize the stack pointer

	LXI B, F1			; put the address of string in registers B and C
	MVI A, TCreate		; store the OS call code to A
	call GTU_OS			; call the OS

	MVI A, TJoin
	call GTU_OS


	LXI B, F2			; put the address of string in registers B and C
	MVI A, TCreate		; store the OS call code to A
	call GTU_OS			; call the OS

	MVI A, TJoin
	call GTU_OS

	LXI B, F3			; put the address of string in registers B and C
	MVI A, TCreate		; store the OS call code to A
	call GTU_OS			; call the OS

	MVI A, TJoin
	call GTU_OS

	hlt


F1:
	LXI SP,stack 	; always initialize the stack pointer PC=15
    mvi C, 0	; init C with 0		PC=16
    mvi D, MAX_VAL_F1	; init D with MAX_VAL		PC=18

loop_f1:
	mvi A, PRINT_B	; A = PRINT_B			PC=20
	MOV B,C 		; B=C  					PC=22
	call GTU_OS	; call the OS 				PC=23
	INR C ; increment C 					PC=1A			
	MOV A,C
	SUB D
	JM loop_f1
	MVI A, TExit
	call GTU_OS

F2:
	LXI SP,stack 	; always initialize the stack pointer
    mvi c, 20	; init C with 10
	mvi a, 0	; A = 0
loop_f2:
	ADD c		; A = A + C
	DCR c		; --C
	JNZ loop_f2	; goto loop if C!=0
	STA SUM		; SUM = A
	LDA SUM		; A = SUM
	MOV B, A	; B = A
	MVI A, PRINT_B	; store the OS call code to A
	call GTU_OS	; call the OS
	MVI A, TExit
	call GTU_OS



F3:
	LXI SP,stack 	; always initialize the stack pointer PC=15
    mvi C, 50	; init C with 0		PC=16
    mvi D, MAX_VAL_F3	; init D with MAX_VAL		PC=18

loop_f3:
	mvi A, PRINT_B	; A = PRINT_B			PC=20
	MOV B,C 		; B=C  					PC=22
	call GTU_OS	; call the OS 				PC=23
	INR C ; increment C 					PC=1A			
	MOV A,C
	SUB D
	JM loop_f3
	MVI A, TExit
	call GTU_OS