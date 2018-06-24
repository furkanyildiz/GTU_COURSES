        ; 8080 assembler code
        .hexfile test.hex
        .binfile test.com
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
start:	dw 'THE TEST IS STARTING...',00AH,00H ; null terminated string
done:	dw 'THE TEST HAS DONE SUCCESSFULLY',00AH,00H ; null terminated string

begin:
	LXI SP,stack 	; always initialize the stack pointer
loop:
	;first say "THE TEST IS STARTING..."
	LXI B, start	; put the address of string in registers B and C
	MVI A, PRINT_STR	; store the OS call code to A
	call GTU_OS	; call the OS

	;test read_b and print_b systam calls
	MVI A, READ_B	; store the OS call code to A
	call GTU_OS	; call the OS
	MVI A, PRINT_B	; store the OS call code to A
	call GTU_OS	; call the OS
	
	;test read_mem and print_mem system calls
	;test print_mem system call
	MVI A, READ_MEM	; store the OS call code to A
	call GTU_OS	; call the OS
	MVI A, PRINT_MEM	; store the OS call code to A
	call GTU_OS	; call the OS

	;test read_str and print_str system calls
	MVI A, READ_STR	; store the OS call code to A
	call GTU_OS	; call the OS
	MVI A, PRINT_STR	; store the OS call code to A
	call GTU_OS	; call the OS

	;test get_rnd system call
	MVI A, GET_RND	; store the OS call code to A
	call GTU_OS	; call the OS
	MVI A, PRINT_B	; store the OS call code to A
	call GTU_OS	; call the OS

	;last say "THE TEST HAS DONE SUCCESSFULLY"
	LXI B, DONE	; put the address of string in registers B and C
	MVI A, PRINT_STR	; store the OS call code to A
	call GTU_OS	; call the OS

	hlt		; end program
