        ; 8080 assembler code
        .hexfile p4.hex
        .binfile p4.com
        ; try "hex" for downloading in hex format
        .download bin  
        .objcopy gobjcopy
        .postbuild echo "OK!"
        ;.nodump

; OS call list
PRINT_B			equ 1
PRINT_MEM		equ 2
READ_B			equ 3
READ_MEM		equ 4
PRINT_STR		equ 5
READ_STR		equ 6
GET_RND			equ 7
TExit			equ 8
TJoin			equ 9
TYield			equ 10
TCreate			equ 11
FILE_CREATE		equ 12
FILE_CLOSE		equ 13
FILE_OPEN		equ 14
FILE_READ		equ 15
FILE_WRITE 		equ 16
FILE_SEEK		equ 17
DIR_READ  		equ 18

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

	;This program prints a null terminated string to the screen

seekVal: dw '143',00H
buffer: ds 4096
data:  dw ' 51 52 53 54 55 56 57 58 59 60',00H
filename: dw 'numbers.txt',00H
begin:
	LXI SP,stack 	; always initialize the stack pointer
	
	;Read FILE NAME
	LXI B, filename	; put the address of string in registers B and C

	MOV H,B
	MOV L,C

	MVI A, FILE_OPEN	; store the OS call code to A
	call GTU_OS	; call the OS
	; b <- file handle id
	mov d,b ;for fseek
	mov e,b ;for fread

	;fseek
	LXI B, seekVal	; put the address of string in registers B and C
	mvi A, FILE_SEEK	; A = PRINT_B
	call GTU_OS	; call the OS

	;write bytes
	mvi d,31
	LXI B, data	; put the address of string in registers B and C
	MVI A, FILE_WRITE	; store the OS call code to A
	call GTU_OS	; call the OS

	;file close
	mov b,e
	MVI A, FILE_CLOSE	; store the OS call code to A
	call GTU_OS	; call the OS


	hlt		; end program