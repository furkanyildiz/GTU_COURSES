        ; 8080 assembler code
        .hexfile prog4.hex
        .binfile prog4.com
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


MAX_VAL     equ 101

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


TID1:	db 0
TID2:	db 0 




;;F4
non_sorted_items: db 50 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
array:	DS 50 ; Liste


;;;F5

FOUND_INDEX: DB 0
TARGET_ff: DB 23
SIZE_N: DB 50
SIZE_C: DB 50

non_sorted_items_ff: db 50 ;F5's 
array_ff:	DS 50 ; F5's Liste
start_address_first: db 1
start_address_second: db 1
end_address_first: db 1
end_address_second: db 1
found_message:	dw 'FOUND IN RANDOM ARRAY',00AH,00H ; null terminated string
not_found_message:	dw 'NOT FOUND IN RANDOM ARRAY',00AH,00H 
SEARCH_COUNT: DB 3

main_prog:
	LXI SP,stack 		; always initialize the stack pointer
	
	LXI B, F4			; put the address of string in registers B and C
	MVI A, TCreate		; store the OS call code to A
	call GTU_OS			; call the OS
	MOV A,B 			; move to A the created thread id
	STA TID1 			; store the created thread id

	LXI B, F5			; put the address of string in registers B and C
	MVI A, TCreate		; store the OS call code to A
	call GTU_OS			; call the OS
	MOV A,B 			; move to A the created thread id
	STA TID2 			; store the created thread id

	LDA TID1 			;load TID
	MOV B, A
	MVI A, TJoin
	call GTU_OS
	
	LDA TID2 			;load TID
	MOV B, A
	MVI A, TJoin
	call GTU_OS

	hlt




F4:
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

end_f4:  	
	MVI A, TExit
	call GTU_OS




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

F5:

	LXI SP,stack 	; always initialize the stack pointer
	LXI D, array_ff	; F5's array
	MVI L, 50		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


PRODUCE_RANDOM_ff: ;ok

	MVI A, GET_RND	; store the OS call code to A
	call GTU_OS			; call the OS
	MOV A, B
	STAX D
	INX D
	DCR L
	MOV A, L
    JNZ PRODUCE_RANDOM_ff			; if zero, find number, and print index


LXI B, array_ff	; 

OUTER_FOR_ff:
	LDA non_sorted_items_ff
	DCR A ; A <- A - 1
	STA non_sorted_items_ff ; save
	MVI H, 0 		; inner loop counter initilize with 0
	LXI B, array_ff	;array_ff address in BC register
	JNZ INNER_FOR_ff ; if non_sorted_items_ff!=0 go inner loop
	
	MVI L, 50   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	LXI D, array_ff	;
	JMP print_array_ff

INNER_FOR_ff:
		LDA non_sorted_items_ff
		CMP H 		; j!=i
		JZ OUTER_FOR_ff ; if j == i go outher loop
		JMP IF_COND_ff
end_if_ff:	INR H
		JMP INNER_FOR_ff

IF_COND_ff:
	LDAX B ; A<-a[j]
	MOV D,A ; D <- a[j]
	INX B ; increment index of array_ff
	LDAX B ;A<-a[j+1]
	CMP D ; a[j+1] - a[j]
	JC SWAP_ff ; if a[j+1] < a[j]
	JMP end_if_ff 

SWAP_ff:
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
	JMP end_if_ff

print_array_ff:
LXI B, array_ff	;
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

SEARCH_ff: 		; H regine koyulan indexdeki elemanı TARGET_ffe atıp BINARY_ff SEARCH_ff yapar.
LXI B,array_ff
MOV A,H
;A deki sayi kadar ileri gider 
n_th_elem_ff:
	MVI E,0  
	CMP E
	JZ store_TARGET_ff_ff
	INX B
	DCR A
	jmp n_th_elem_ff

store_TARGET_ff_ff:
LDAX B				; A <- (BC) ;middeki eleman
STA TARGET_ff  		; TARGET_ff <- A


BINARY_ff:
	LXI H,array_ff
	MOV A,H
	STA start_address_first
	MOV A,L
	STA start_address_second


	MVI A,49  ;D deki sayi kadar ileri gider
	find_last_address_ff:
		MVI E,0  
		CMP E
		JZ found_last_address_ff
		INX H
		DCR A
		jmp find_last_address_ff

	found_last_address_ff:

		MOV A,H
		STA end_address_first
		MOV A,L
		STA end_address_second



;start_address ve end_address kaydedildi
BIG_LOOP_ff:

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
LDA TARGET_ff ; A<- TARGET_ff
CMP H
JZ   found
jmp  not_found


check_size:
	LDA SIZE_C ; A<- SIZE
	mvi H, 0
	CMP H
	JNZ continue_SEARCH_ff
	LDAX B						; A <- (BC) ;end adress A da
	MOV H,A
	LDA TARGET_ff ; A<- TARGET_ff
	CMP H
	JZ found
	INX B
	LDAX B						; A <- (BC) ;end adress A da
	MOV H,A

	LDA FOUND_INDEX
	INR A
	STA FOUND_INDEX


	LDA TARGET_ff ; A<- TARGET_ff
	CMP H
	JZ found
	jmp not_found


continue_SEARCH_ff:
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
			LDA TARGET_ff 					; A <- TARGET_ff
			CMP E
			JZ found_mid
			JC go_left 					; A < E  	 TARGET_ff < MID
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
			jmp BIG_LOOP_ff



go_left:
	DCX B
	MOV A,B
	STA end_address_first
	MOV A,C
	STA end_address_second
	jmp BIG_LOOP_ff

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
	jmp end_BINARY_ff

 
not_found: 	
	LXI B, not_found_message	; put the address of string in registers B and C
	MVI A, PRINT_STR	; store the OS call code to A
	call GTU_OS	; call the OS
	jmp end_BINARY_ff



end_BINARY_ff: 
	MVI L,0
	LDA SEARCH_COUNT   ; A <- SEARCH_ff_COUNT
	DCR A
	STA SEARCH_COUNT
	CMP L
	JZ end_f5
	MVI L,1
	CMP L
	JZ third_SEARCH_ff
	MVI A,50
	STA SIZE_N
	STA SIZE_C
	MVI A,0
	STA FOUND_INDEX	
	MVI H,9
	jmp SEARCH_ff

third_SEARCH_ff:
	MVI H,39
	MVI A,50
	STA SIZE_N
	STA SIZE_C
	MVI A,0
	STA FOUND_INDEX	
	jmp SEARCH_ff

end_f5:  	
	MVI A, TExit
	call GTU_OS
