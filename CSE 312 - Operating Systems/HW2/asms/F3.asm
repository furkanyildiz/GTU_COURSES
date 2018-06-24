        ; 8080 assembler code
        .hexfile F3.hex
        .binfile F3.com
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
MAX_VAL     equ 101

	; Position for stack pointer
stack   equ 0F000h

	org 000H
	jmp begin

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

begin:
	LXI SP,stack 	; always initialize the stack pointer PC=15
    mvi C, 50	; init C with 0		PC=16
    mvi D, MAX_VAL	; init D with MAX_VAL		PC=18

loop:
	mvi A, PRINT_B	; A = PRINT_B			PC=20
	MOV B,C 		; B=C  					PC=22
	call GTU_OS	; call the OS 				PC=23
	INR C ; increment C 					PC=1A			
	MOV A,C
	SUB D
	JM loop
	hlt		; end program