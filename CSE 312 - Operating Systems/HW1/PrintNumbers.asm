        ; 8080 assembler code
        .hexfile PrintNumbers.hex
        .binfile PrintNumbers.com
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
MAX_VAL     equ 52

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

begin:
	LXI SP,stack 	; always initialize the stack pointer
    mvi C, 0	; init C with 0
    mvi D, MAX_VAL	; init D with MAX_VAL

loop:
	mvi A, PRINT_B	; A = PRINT_B
	MOV B,C 		; B=C
	call GTU_OS	; call the OS
	INR C ; increment C
	INR C ; increment C
	MOV A,C
	SUB D
	JM loop
	hlt		; end program