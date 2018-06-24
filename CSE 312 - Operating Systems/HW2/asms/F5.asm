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
start_address: db 1
end_address: db 1
TARGET: DB 23
SIZE_N: DB 50
SIZE_C: DB 50
FOUND_INDEX: DB 0
SEARCH_COUNT: DB 3

found_message:	dw 'FOUND IN RANDOM ARRAY',00AH,00H ; null terminated string
not_found_message:	dw 'NOT FOUND IN RANDOM ARRAY',00AH,00H 
deneme_message:	dw 'DENEME DENEME DAN DAN DAN',00AH,00H 

start_address_first: db 1
start_address_second: db 1
end_address_first: db 1
end_address_second: db 1

begin:
	LXI SP,stack 	; always initialize the stack pointer
	LXI D, array	; 
	MVI L, 50		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


PRODUCE_RANDOM: ;ok

	MVI A, GET_RND	; store the OS call code to A
	call GTU_OS			; call the OS
	MOV A, B
	STAX D
	INX D
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
	JMP print_array

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
	INX B ; increment index of array
	LDAX B ;A<-a[j+1]
	CMP D ; a[j+1] - a[j]
	JC SWAP ; if a[j+1] < a[j]
	JMP end_if 

SWAP:
	LDAX B ; A<- a[j+1]
	MOV D,A ; D <- A
	DCX B
	LDAX B ; A<- a[j]
	MOV L,A  ; L<-a[j]
	MOV A,D  ; A<-a[j+1]
	STAX B ; a[j] <- a[j+1]
	INX B
	MOV A,L  ;A<- a[j]""
	STAX B ;a[j+1] <- a[j]
	JMP end_if

print_array:
LXI B, array	;
MVI L, 50   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
SORTED: ;ok
	MVI A, PRINT_MEM	; store the OS call code to A
	call GTU_OS			; call the OS
	INX B
	DCR L
	MOV A, L
   JNZ SORTED			; if zero, find number, and print index


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

MVI H,0

SEARCH: 		; H regine koyulan indexdeki elemanı targete atıp binary search yapar.
LXI B,array
MOV A,H
;A deki sayi kadar ileri gider 
n_th_elem:
	MVI E,0  
	CMP E
	JZ store_target
	INX B
	DCR A
	jmp n_th_elem

store_target:
LDAX B				; A <- (BC) ;middeki eleman
STA TARGET  		; TARGET <- A


BINARY:
	LXI H,array
	MOV A,H
	STA start_address_first
	MOV A,L
	STA start_address_second


	MVI A,49  ;D deki sayi kadar ileri gider
	find_last_address:
		MVI E,0  
		CMP E
		JZ found_last_address
		INX H
		DCR A
		jmp find_last_address

	found_last_address:

		MOV A,H
		STA end_address_first
		MOV A,L
		STA end_address_second



;start_address ve end_address kaydedildi
BIG_LOOP:

LDA SIZE_N   ; A<- SIZE_N 		this is next step size
STA SIZE_C   ; SIZE_C <- A   	current size save

LDA FOUND_INDEX

LDA start_address_first  	;HL <- start_address
MOV B,A
LDA start_address_second  	;HL <- start_address
MOV C,A
LDA end_address_first  		;HL <- start_address
MOV D,A
LDA end_address_second  	;HL <- start_address
MOV E,A
LDAX B						; A <- (BC) ;end adress A da
MOV H,A
LDAX D 						; A <- (DE) ;end adress A da
CMP H
JNZ  check_size
LDA TARGET ; A<- TARGET
CMP H
JZ   found
jmp  not_found


check_size:
	LDA SIZE_C ; A<- SIZE
	mvi H, 0
	CMP H
	JNZ continue_search
	LDAX B						; A <- (BC) ;end adress A da
	MOV H,A
	LDA TARGET ; A<- TARGET
	CMP H
	JZ found
	INX B
	LDAX B						; A <- (BC) ;end adress A da
	MOV H,A

	LDA FOUND_INDEX
	INR A
	STA FOUND_INDEX


	LDA TARGET ; A<- TARGET
	CMP H
	JZ found
	jmp not_found


continue_search:
	;start adress BC, end address DE de
	mvi D, 0	;bolmenın sonucu
	divide:
		LDA SIZE_N ; A<- SIZE
		MVI E, 1
		CMP E
		JZ after_divide
		MVI E, 0
		CMP E
		JZ after_divide
		DCR A
		DCR A
		STA SIZE_N
		INR D ;result in D
		jmp divide

	after_divide:
		mov A,D
		STA SIZE_N
		;A deki sayi kadar ileri gider 
		find_mid_address:
			MVI E,0  
			CMP E
			JZ compare
			INX B
			DCR A
			jmp find_mid_address

		compare:
			LDAX B						; A <- (BC) ;middeki eleman
			MOV E,A 					; E <- middeki eleman
			LDA TARGET 					; A <- TARGET
			CMP E
			JZ found_mid
			JC go_left 					; A < E  	 TARGET < MID
			;go right
			LDA FOUND_INDEX 
			INR D
			ADD D
			STA FOUND_INDEX

			INX B
			MOV A,B
			STA start_address_first
			MOV A,C
			STA start_address_second
			jmp BIG_LOOP



go_left:
	DCX B
	MOV A,B
	STA end_address_first
	MOV A,C
	STA end_address_second
	jmp BIG_LOOP

found_mid:
	LDA FOUND_INDEX
	ADD D
	STA FOUND_INDEX
	jmp found

found:
	LXI B, found_message	; put the address of string in registers B and C
	MVI A, PRINT_STR	; store the OS call code to A
	call GTU_OS	; call the OS
	LDA FOUND_INDEX
	MOV B,A 	;bulunursa B de index
	MVI A, PRINT_B	; store the OS call code to A
	call GTU_OS	; call the OS
	jmp end_binary

 
not_found: 	
	LXI B, not_found_message	; put the address of string in registers B and C
	MVI A, PRINT_STR	; store the OS call code to A
	call GTU_OS	; call the OS
	jmp end_binary



end_binary: 
	MVI L,0
	LDA SEARCH_COUNT   ; A <- SEARCH_COUNT
	DCR A
	STA SEARCH_COUNT
	CMP L
	JZ end_f5
	MVI L,1
	CMP L
	JZ third_search
	MVI A,50
	STA SIZE_N
	STA SIZE_C
	MVI A,0
	STA FOUND_INDEX	
	MVI H,9
	jmp SEARCH

third_search:
	MVI H,39
	MVI A,50
	STA SIZE_N
	STA SIZE_C
	MVI A,0
	STA FOUND_INDEX	
	jmp SEARCH

end_f5:
	hlt		; end program
