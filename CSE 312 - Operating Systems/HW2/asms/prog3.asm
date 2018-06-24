; 8080 assembler code
        .binfile p3.com
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

array: ds 10   

MAX_VAL_F3     equ 101

begin:
	LXI SP,stack 	; always initialize the stack pointer
   

	LXI D, array	
	MVI H, 10
	MVI E, 0

	thread_create:

		LXI B, f3	
		MVI A, TCreate	
		call GTU_OS	

		MOV A, B
		STAX D

		INR D

		DCR H
		MOV C, H

		JNZ thread_create
		


	thread_join:
		
		MOV B, A
		LDAX D

		MVI A, TJoin
		call GTU_OS	

		INR D

		DCR H
		MOV C, H

		JNZ thread_join



	hlt		
	
F3:
	LXI SP,stack 	; always initialize the stack pointer PC=15
    mvi C, 50	; init C with 0					PC=
    mvi D, MAX_VAL_F3	; init D with MAX_VAL		PC=

loop:
	mvi A, PRINT_B	; A = PRINT_B				PC=
	MOV B,C 		; B=C  						PC=
	call GTU_OS	; call the OS 					PC=
	INR C ; increment C 						PC=		
	MOV A,C
	SUB D
	JM loop
	MVI A, TExit
	call GTU_OS