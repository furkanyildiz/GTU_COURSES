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
GET_RND     equ 7
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


non_sorted_items: db 50 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
array:	DS 50 ; Liste

begin:
	LXI SP,stack 	; always initialize the stack pointer
	LXI D, array	; 
	MVI L, 50		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


PRODUCE_RANDOM: ;ok

	MVI A, GET_RND	; store the OS call code to A
	call GTU_OS			; call the OS
	MOV A, B
	STAX D
	INR D
	DCR L
	MOV A, L
    JNZ PRODUCE_RANDOM			; if zero, find number, and print index


LXI B, array	; 

OUTER_FOR:
	LDA non_sorted_items
	DCR A ; A <- A - 1
	STA non_sorted_items ; save
	MVI H, 0 		; inner loop counter initilize with 0
	LXI B, array	;array address in BC register
	JNZ INNER_FOR ; if non_sorted_items!=0 go inner loop
	
	MVI L, 50   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	LXI D, array	;
	JMP SORTED

INNER_FOR:
		LDA non_sorted_items
		CMP H 		; j!=i
		JZ OUTER_FOR ; if j == i go outher loop
		JMP IF_COND
end_if:	INR H
		JMP INNER_FOR

IF_COND:
	LDAX B ; A<-a[j]
	MOV D,A ; D <- a[j]
	INR B ; increment index of array
	LDAX B ; A<-a[j+1]
	CMP D ; a[i+1] - a[i]
	JC SWAP ; if A=a[i+1] < D=a[i]
	JMP end_if
	

SWAP:
	LDAX B ; A<- a[j+1]
	MOV D,A ; D <- A
	DCR B
	LDAX B ; A<- a[j]
	MOV L,A  ; L<-a[j]
	MOV A,D  ; A<-a[j+1]
	STAX B ; a[j] <- a[j+1]
	INR B
	MOV A,L  ;A<- a[j]
	STAX B ;a[j+1] <- a[j]
	JMP end_if
	
MVI L, 50   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LXI D, array	;
SORTED: ;ok
	LDAX D  ; A <- (DE) 
	MOV B,A 
	MVI A, PRINT_B	; store the OS call code to A
	call GTU_OS			; call the OS
	INR D
	DCR L
	MOV A, L
    JNZ SORTED			; if zero, find number, and print index

end:  	hlt		; end program
