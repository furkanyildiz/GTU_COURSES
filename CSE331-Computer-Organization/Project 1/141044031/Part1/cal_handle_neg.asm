.text
.globl power

power:

	addi $sp, $sp, -16
	sw $t3,12($sp)
	sw $t2,8($sp)
	sw $t1,4($sp)
	sw $t0,0($sp)

	add $t0 $zero, $a0 #t0=n ussu ifadesi
	addi $t1, $zero,10
	addi $t2, $zero,1 #count
	addi $t3, $zero,10

	beq $t2, $t0, equal_p

	Loop1: mult $t1, $t3
		mflo $t1
		addi $t2, $t2,1 #count++
		bne $t2, $t0, Loop1



	equal_p:add $v0, $t1, $zero
	lw $t0, 0($sp)
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	lw $t3, 12($sp)
	addi $sp,$sp,16
	jr $ra

.text
.globl find_num_of_digits

find_num_of_digits:
	addi $sp,$sp,-12
	sw $t2, 8($sp)
	sw $t1, 4($sp)
	sw $t0, 0($sp)
	addi $t0, $zero,0 #count
	add $t1, $zero,$a0
	addi $t2, $zero,10 #bolecegimiz sayi
	Loop: div $t1, $t2
		mflo $t1
		addi $t0,$t0,1
		bne $t1, $zero,Loop
	add $v0, $t0, $zero
	lw $t0, 0($sp)
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	addi $sp, $sp,12
	jr $ra


.text
.globl extend_num
#arg1=num, arg2:num i kac basamakli istedigimizin sayisi
#fonksiyon num sayisinin basamak sayisini arg2 ye esitler
#daha num in basamak sayisi daha kucuk ise tabi
extend_num:
	addi $sp,$sp,-24
	sw $s2, 20($sp)
	sw $s1, 16($sp)
	sw $s0, 12($sp)
	sw $t2, 8($sp)
	sw $t1, 4($sp)
	sw $t0, 0($sp)



	add $s2, $ra, $zero #save return adress
	
	add $s0, $zero, $a0
	add $s1, $zero, $a1

	add $t1, $zero,10 #basamak sayisini arttirmak icin 10 ile carpmaliyiz

	add $a0,$zero, $s0
	jal find_num_of_digits
	add $t0, $v0,$zero # t0 = s0 sayisinin basamak sayisi

	slt $t2, $t0, $s1 #if(t0<s1) t0=1 else t0=0
	beq $t2, $zero, end  #s0 sayisinin basamak sayisi, s1 den buyuk yada esitse direk bitmeli fonksiyon

	extend_Loop: mult $s0, $t1
	mflo $s0
	add $a0,$zero, $s0
	jal find_num_of_digits
	add $t0,$zero,$v0
	bne $t0, $s1, extend_Loop

	end:add $v0, $zero,$s0

	add $ra, $s2, $zero

	lw $t0, 0($sp)
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	lw $s0, 12($sp)
	lw $s1, 16($sp)
	lw $s2, 20($sp)
	addi $sp,$sp,24
	jr $ra

.text
.globl multf
multf:
	addi $sp, $sp, -68
	sw $s6, 64($sp)
	sw $s5, 60($sp)
	sw $s4, 56($sp)
	sw $s3, 52($sp)
	sw $s2, 48($sp)
	sw $s1, 44($sp)
	sw $s0, 40($sp)
	sw $t9, 36($sp)
	sw $t8, 32($sp)
	sw $t7, 28($sp)
	sw $t6, 24($sp)
	sw $t5, 20($sp)
	sw $t4, 16($sp)
	sw $t3, 12($sp)
	sw $t2, 8($sp)
	sw $t1, 4($sp)
	sw $t0, 0($sp)

	add $s6, $ra, $zero #save return adress


	add $s0, $zero, $a0 # virgulden sonra 1.sayi
	add $s1, $zero, $a1 # virgulden sonra 2.sayi
	add $s2, $zero, $a2 # virgulden once 1.sayi
	add $s3, $zero, $a3 # virgulden once 2.sayi

	addi $t8,$zero,-1
	# check 1. number is negative or not
	c1:
		slt $t6,$s2,$zero #if(s2<0) t6=1, else t6=0
		beq $t6,$zero,c2
		mult $s2,$t8
		mflo $s2

	# check 2. number is negative or not
	c2:
		slt $t7,$s3,$zero #if(s3<0) t7=1, else t7=0
		beq $t7,$zero,do_mult
		mult $s3,$t8
		mflo $s3


	#1. sayiyi birlestirme 13.25 ise sayi 1325 yapma
	do_mult:
	add $a0,$zero,$s0
	jal find_num_of_digits
	add $t0,$zero, $v0 #t0 = virgulden sonraki birinci sayinin basamak sayisi

	add $a0,$zero, $t0
	jal power
	add $t1,$zero,$v0 #t1, virgulden onceki sayiyi kacla carpacagimiz

	mult $s2 $t1
	mflo $t3
	add $t3,$t3,$s0 #sayi 13.25 ise t3 de 1325 yazar

	#2. sayiyi birlestirme

	add $a0,$zero,$s1
	jal find_num_of_digits
	add $t2,$zero, $v0 #t2 = virgulden sonraki birinci sayinin basamak sayisi

	add $a0,$zero, $t2
	jal power
	add $t1,$zero,$v0 #t1, virgulden onceki sayiyi kacla carpacagimiz

	mult $s3,$t1
	mflo $t4
	add $t4, $t4,$s1  #sayi 13.25 ise t4 de 1325 yazar

	#1. ve 2. sayiyi carpalim
	mult $t3 $t4
	mflo $s5 #1. ve 2. sayinin carpim sonuclari



	add $t5, $t0,$t2
	add $a0,$zero,$t5
	jal power
	add $t5,$zero,$v0

	div $s5, $t5
	mflo $t9
	mfhi $v1

	and $t1, $t6,$t7
	beq $t1, $zero,check_or
	bne $t1, $zero,end_of_mult
	
	check_or: or $t1, $t6,$t7

	beq $t1, $zero,end_of_mult
	mult $t9,$t8
	mflo $t9

	end_of_mult:
	add $v0,$zero,$t9
	add $ra,$zero, $s6

	lw $t0, 0($sp)
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	lw $t3, 12($sp)
	lw $t4, 16($sp)
	lw $t5, 20($sp)
	lw $t6, 24($sp)
	lw $t7, 28($sp)
	lw $t8, 32($sp)
	lw $t9, 36($sp)
	lw $s0, 40($sp)
	lw $s1, 44($sp)
	lw $s2, 48($sp)
	lw $s3, 52($sp)
	lw $s4, 56($sp)
	lw $s5, 60($sp)
	lw $s6, 64($sp)
	addi $sp,$sp,68
	jr $ra

.text
.globl sum

sum:
	addi $sp, $sp,-60
	sw $s7,56($sp)
	sw $s6,52($sp)
	sw $s5,48($sp)
	sw $s4,44($sp)
	sw $s3,40($sp)
	sw $s2,36($sp)
	sw $s1,32($sp)
	sw $s0,28($sp)
	sw $t6,24($sp)
	sw $t5,20($sp)
	sw $t4,16($sp)
	sw $t3,12($sp)
	sw $t2,8($sp)
	sw $t1,4($sp)
	sw $t0,0($sp)

	add $s7, $zero, $ra # save return adress.


	add $s0, $zero, $a0 # virgulden sonra 1.sayi
	add $s1, $zero, $a1 # virgulden sonra 2.sayi
	add $s4, $zero, $a2 # virgulden once 1.sayi
	add $s5, $zero, $a3 # virgulden once 2.sayi

	add $a0,$zero,$s0
	jal find_num_of_digits 
	add $t1,$zero, $v0 # t1 = virgulden sonra 1.sayinin basamak sayisi

	add $a0,$zero,$s1
	jal find_num_of_digits
	add $t2,$zero, $v0 # t2 = virgulden sonra 2.sayinin basamak sayisi



	slt $t6, $t1, $t2 #if(t1<t2) t6=1 else t6=0
	bne $t6,$zero,Else_sum
	beq $t1 $t2,ok
	#t1>t2 durumu
	#t2 yi t1 in basamak sayisina gelene kadar 10 ile carp
	sub $t4,$t1,$t2
	add $a0,$zero, $t4
	jal power
	add $t4,$zero,$v0 #t1, virgulden onceki sayiyi kacla carpacagimiz

	mult $s1 $t4
	mflo $s1
	addi $t4, $zero, 0
	add $t3,$zero,$t1 #t3 en buyuk basamak sayisi
	beq $zero $zero,ok2

	Else_sum: 
	#t2>t1 durumu
	#t1 yi t2 in basamak sayisina gelene kadar 10 ile carp
	sub $t4,$t2,$t1
	add $a0,$zero, $t4
	jal power
	add $t4,$zero,$v0 #t1, virgulden onceki sayiyi kacla carpacagimiz

	mult $s0 $t4
	mflo $s0
	addi $t4, $zero, 0


	ok:
	add $t3, $zero,$t2
	ok2:
	add $s2,$s0,$s1 #virgulden sonraki sayilarin toplami

	add $a0,$s2, $zero
	jal find_num_of_digits #s2(virglden sonraki toplamin basamak sayisini hesapla in v0)
	add $t1,$v0, $zero


	beq $t3, $t1,EldeYok



	#EldeVar
	addi $t4, $zero, 0 #initilaze t4
	addi $t4,$zero,1 #if(EldeVar) t4==1
	addi $t5, $v0, -1 #t5 = virglden sonraki toplamin basamak sayisi -1

	add $a0,$zero, $t5 

	jal power

	sub $s2, $s2,$v0

	EldeYok:add $t4, $t4, $zero
	add $s6,$s4,$s5 #virgulden onceki sayilarin toplami
	add $s6,$s6,$t4 #virgulden onceki sayilerin elde ile toplami


	add $v0, $s6, $zero
	add $v1, $s2, $zero

	add $ra, $zero, $s7 # restore return adress.

	lw $t0,0($sp)
	lw $t1,4($sp)
	lw $t2,8($sp)
	lw $t3,12($sp)
	lw $t4,16($sp)
	lw $t5,20($sp)
	lw $t6,24($sp)
	lw $s0,28($sp)
	lw $s1,32($sp)
	lw $s2,36($sp)
	lw $s3,40($sp)
	lw $s4,44($sp)
	lw $s5,48($sp)
	lw $s6,52($sp)
	lw $s7,56($sp)	
	addi $sp,$sp,60

	jr $ra

.text
.globl subf

subf:

	addi $sp, $sp, -60
	sw $s6, 56($sp)
	sw $s5, 52($sp)
	sw $s4, 48($sp)
	sw $s3, 44($sp)
	sw $s2, 40($sp)
	sw $s1, 36($sp)
	sw $s0, 32($sp)
	sw $t7, 28($sp)
	sw $t6, 24($sp)
	sw $t5, 20($sp)
	sw $t4, 16($sp)
	sw $t3, 12($sp)
	sw $t2, 8($sp)
	sw $t1, 4($sp)
	sw $t0, 0($sp)


	add $s4, $ra, $zero #save return adress

	add $s0, $zero, $a0 # virgulden sonra 1.sayi
	add $s1, $zero, $a1 # virgulden sonra 2.sayi
	add $s2, $zero, $a2 # virgulden once 1.sayi
	add $s3, $zero, $a3 # virgulden once 2.sayi

	add $t6, $zero, $zero #initialize


	#virgulden onceki kisim icin 2. sayi daha buyukse (2. sayi-1.sayi)*(-1) yapilmali
	slt $t4, $s2,$s3 # if(s2<s3) t4=1 else t4=0
	beq $t4, $zero, check2

	# s2 < s3 durumu icin
	add $t5,$zero, $s2
	add $s2,$zero, $s3
	add $s3,$zero, $t5

	add $t5,$zero, $s0
	add $s0,$zero, $s1
	add $s1,$zero, $t5

	beq $zero, $zero, after_comma

	check2: bne $s2,$s3,after_comma
	slt $t6, $s0,$s1 #if(s0<s1) $t6=1, else $t6=0
	beq $t6, $zero, after_comma

	add $t5,$zero, $s2
	add $s2,$zero, $s3
	add $s3,$zero, $t5

	add $t5,$zero, $s0
	add $s0,$zero, $s1
	add $s1,$zero, $t5

	after_comma:
	#cikarilacak sayinin daha buyuk olma durumu for after comma

	add $a0,$zero, $s0
	jal find_num_of_digits
	add $t1, $v0, $zero  #t1 =  1. sayinin basamak sayisi for after comma 

	add $a0,$zero, $s1
	jal find_num_of_digits
	add $t2, $v0, $zero  #t2 =  2. sayinin basamak sayisi for after comma 
	

	slt $t3, $t1,$t2  #if(t1 < t2) t3=1, otherwise, t3=0
	beq $t3,$zero,AH
	#t1<t2 durumu
	add $a0,$zero,$s0
	add $a1,$zero,$t2
	jal extend_num
	add $s0,$zero,$v0 #1. sayiyi extend ettik artik 2. sayi ile ayni basamak sayisina sahip

	#update t1
	add $a0,$zero, $s0
	jal find_num_of_digits
	add $t1, $v0, $zero  #t1 =  1. sayinin yeni basamak sayisi for after comma 

	j compare_two_numbers

	AH: beq $t1, $t2, compare_two_numbers
	#t1>t2 durumu
	add $a0,$zero,$s1
	add $a1,$zero,$t1
	jal extend_num
	add $s1,$zero,$v0 #2. sayiyi extend ettik artik 1. sayi ile ayni basamak sayisina sahip





	#update t2
	add $a0,$zero, $s1
	jal find_num_of_digits
	add $t2, $v0, $zero  #t2 =  2. sayinin yeni basamak sayisi for after comma 

	compare_two_numbers:


	slt $t0, $s0, $s1 #if (s0<s1) $to = 1, else $t0=0
	beq $t0, $zero, Else #if(t0 == $zero) ya sayilar esittir yada cikarilacak sayi daha kucuktur
	

	#if t1 == t2 haline getirdikten sonra
	do:add $a0,$zero, $t1
	jal power
	add $s0, $v0, $s0 #alinan eldeyi virgulden sonra 1. sayiya ekledik



	Else: sub $s5, $s0, $s1
	sub $s6, $s2, $s3
	sub $s6, $s6,$t0 #verilen eldeyi cikartiyoruz virgulden onceki kisimdan, eger elde verilmediyse t0 == 0

	#beq $t4, $zero, return_sum
	or $t7,$t4,$t6
	beq $t7, $zero, return_sum

	#t4!= 0 yani cikarilan sayinin virgulden onceki kismi daha buyukse
	addi $t5, $zero,-1
	mult $s6,$t5
	mflo $s6

	return_sum:
	add $v0, $s6, $zero #becore comma
	add $v1, $s5, $zero #after comma

	add $ra, $zero, $s4 # restore return adress.

	lw $t0, 0($sp)
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	lw $t3, 12($sp)
	lw $t4, 16($sp)
	lw $t5, 20($sp)
	lw $t6, 24($sp)
	lw $t7, 28($sp)
	lw $s0, 32($sp)
	lw $s1, 36($sp)
	lw $s2, 40($sp)
	lw $s3, 44($sp)
	lw $s4, 48($sp)
	lw $s5, 52($sp)
	lw $s6, 56($sp)
	addi $sp, $sp, 60
	jr $ra
	

	.data
	str: .asciiz "Result ="
	str2: .asciiz ","
	error_mesage: .asciiz "Please give 2 integer 1 character and 2 integer value and dont press enter after character. Press only enter after giving integer"

.text
.globl main

main:
 	li $v0, 5
 	syscall
 	add $s0,$zero, $v0 # add the first number read into $s0.

	li $v0, 5
 	syscall
 	add $s1,$zero, $v0 # add the after comma of first number read into $s1.

	li $v0, 12
 	syscall
 	add $s4,$zero, $v0 # add the operator read into $s4.

 	li $v0, 5
 	syscall
 	add $s2,$zero, $v0 # add the second number read into $s2.

	li $v0, 5
 	syscall
 	add $s3,$zero, $v0 # add the after comma of second number read into $s3.

 	#hangi operatorun girildigini ASCII kodlarindan yararlanarak kontrol ediyorum.
	addi $t0, $zero,42 # * op
	addi $t1, $zero,43 # + op
	addi $t2, $zero,45 # - op

	addi $t6,$zero,1
	addi $t7,$zero,-1


 	add $a0, $zero,$s1 #1. sayinin ondalikli kismi
	add $a1, $zero,$s3 #2. sayinin ondalikli kismi
	add $a2, $zero,$s0 #1. sayinin tam kismi
	add $a3, $zero,$s2 #2. sayinin tam kismi


	slt $t3, $zero, $s0 #1. sayi sifirdan buyukse t3=1 else t3=0
	slt $t4, $zero, $s2 #2. sayi sifirdan buyukse t4=1 else t4=0

	beq $t0,$s4, go_mult
	beq $t1,$s4, go_sum
	beq $t2,$s4, go_sub
	beq $zero, $zero, exception

	go_mult:
	jal multf
	beq $zero, $zero, results

	go_sum:
	and $t5, $t3, $t4
	beq $t5, $zero,sum_control #sayilardan en az biri negatif ise atlar.
	jal sum
	beq $zero, $zero, results

	sum_control:


		beq $t3,$t6,sum_plus_minus
		beq $t4,$t6,sum_minus_plus
		#-- durumu
		mult $s0,$t7
		mflo $a2 #s0yi parametre olarak gonderirken degistiridk
		mult $s2,$t7
		mflo $a3 #s2yi parametre olarak gonderirken degistiridk
		jal sum

		add $t0,$zero, $v0
		add $t1,$zero, $v1

		mult $t0,$t7
		mflo $t0

		beq $zero, $zero, print_results

	sum_plus_minus:
		#B'yi - ile carp 
		mult $s2,$t7
		mflo $a3

		#A-B yap
		jal subf
		beq $zero, $zero, results

	sum_minus_plus:
		#A'yi - ile carp 
		mult $s0,$t7
		mflo $s0
		#ve B-A yap
	 	add $a0, $zero,$s3 #2. sayinin ondalikli kismi
		add $a1, $zero,$s1 #1. sayinin ondalikli kismi
		add $a2, $zero,$s2 #2. sayinin tam kismi
		add $a3, $zero,$s0 #1. sayinin tam kismi
		
		jal subf
		beq $zero, $zero, results

	go_sub:
	and $t5, $t3, $t4

	beq $t5, $zero,sub_control #sayilardan en az biri negatif ise atlar.
	#++ durumu
	jal subf
	beq $zero, $zero, results


	sub_control:
		beq $t3,$t6,sub_plus_minus
		beq $t4,$t6,sub_minus_plus
		#-- durumu
		#A ve B yi - le carp
		mult $s0,$t7
		mflo $s0

		mult $s2,$t7
		mflo $s2
		#ve B-A yap
	 	add $a0, $zero,$s3 #2. sayinin ondalikli kismi
		add $a1, $zero,$s1 #1. sayinin ondalikli kismi
		add $a2, $zero,$s2 #2. sayinin tam kismi
		add $a3, $zero,$s0 #1. sayinin tam kismi
		
		jal subf
		beq $zero, $zero, results

	sub_plus_minus:
		#B'yi - ile carp 
		mult $s2,$t7
		mflo $a3

		#A+B yap
		jal sum
		beq $zero, $zero, results


	sub_minus_plus:
		#A'yi - ile carp 
		mult $s0,$t7
		mflo $a2
		#-(A+B) yi hesaplamaya calis A+B yi hesapla - ile carp
		jal sum
		add $t0,$zero, $v0
		add $t1,$zero, $v1

		mult $t0,$t7
		mflo $t0

		beq $zero, $zero, print_results

	results:
	add $t0, $zero, $v0
	add $t1, $zero, $v1

	print_results:
	li $v0, 4 # system call code for print_str
	la $a0, str # address of string to print
	syscall # print the string

	li $v0, 1 # system call code for print_int
	add $a0,$zero, $t0 # copy result to a0
	syscall # print it

	li $v0, 4 # system call code for print_str
	la $a0, str2 # address of string to print
	syscall # print the string

	li $v0, 1 # system call code for print_int
	add $a0,$zero, $t1 # copy result to a0
	syscall # print it

    li $v0, 10 # end program
    syscall

	exception:
    li $v0, 4 # system call code for print_str
	la $a0, error_mesage # address of string to print
	syscall # print the string

    li $v0, 10      # end program
    syscall