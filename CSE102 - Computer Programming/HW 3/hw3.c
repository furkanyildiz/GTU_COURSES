/* -----------------------------------------------------------------------   */ 
/*                                                                           */ 
/* HW03_141044031_FÜRKAN_YILDIZ 		                                     */
/*                                                                           */ 
/* main.c                                                                    */ 
/* -----------------------------------------------------------------------   */ 
/* Created on 05/03/2016 by FÜRKAN YILDIZ                                    */ 
/*                                                                           */ 
/* Description                                                               */ 
/* -----------------------------------------------------------------------   */
/* 3. Ödevde program, kullanıcıdan alınan sayının, tek olup olmadığını,	     */
/* o sayının faktoriyel sayı olup olmadığını ve sayının narsistik olup       */
/* olmadığını kontrol eden bir algoritmaya sahip.                            */
/*                                                                           */ 
/*---------------------------------------------------------------------------*/ 


/*---------------------------------------------------------------------------*/
/*                                 Includes 			                     */
/*---------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>

/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				                 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	         */ 
/* void welcome(void)			                                             */ 
/* -----------								    							 */   
/* Description                                                               */ 
/* -----------								    							 */ 
/*  Bu fonksiyon, program çalıştığında, kullanıcıya hoşgeldin diyerek        */ 
/*  programın amacını söyleyecek.					    					 */ 
/*                                                            		    	 */  
/*---------------------------------------------------------------------------*/

void welcome(void);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void OddNumber(int x)		                                     		 */
/*	x  - Konsoldan girilen sayı    				    	     				 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, girilen sayının tek olup olmadığını kontrol edecek         */ 
/*  eğer sayı, 2 ile bölünebiliyorsa tek değil, bölünebiliyorsa tek olacak.  */ 
/*                                                            		     	 */  
/*---------------------------------------------------------------------------*/

void OddNumber(int x);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				    			 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	    	 */ 
/* void FactorialNumber(int y)		                                   		 */ 
/* -----------								     							 */ 
/*	y  - Konsoldan girilen sayı    				    	     				 */  
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, girilen sayının faktoriyel bir sayı olup olmadığını        */
/*  kontrol edecek. Konsola girilen sayıyı, sayı birden büyük eşit olduğu    */ 
/*  sürece, sürekli olarak 1 den başlayıp artarak, bölecek ve en sonunda     */
/*  bölüm 1 olursa, sayının faktoriyel bir sayı olduğunu, 1 olmazsa,         */
/*  sayının faktoriyel bir sayı olmadığını söyleyecek.                       */
/*                                                                           */   
/*---------------------------------------------------------------------------*/

void FactorialNumber(int y);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				     			 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	    	 */ 
/* void NarcissisticNumber(int z)		                            		 */ 
/* -----------								    							 */
/*	z   - Konsoldan girilen sayı    				    					 */   
/* Description                                                               */ 
/* -----------								   							     */ 
/*  Bu fonksiyon, konsoldan girilen sayının, narsistik olup olmadığını       */ 
/*  kontrol edecek.Öncelikle sayının değerini bir değişkene atayacak ve o    */ 
/*  değişkenin değeri 0 olana kadar, 10 a bölecek. Her 10 a böldüğünde       */
/*  i 1 kez artacak ve böylece girilen sayının basamak sayısı "i" olacak.    */
/*  Basamak sayısını bulduktan sonra, while döngüsü ile girilen sayıyı       */
/*  basamaklarına ayırıp her basamağın, basamak sayısı ile kuvveti alınacak  */ 
/*  ve "if statement" ile sonucun, girilen sayıya eşit olup  olmadığını      */
/*  kontrol ediyor eğer eşitse, gerilen sayı narsistik sayıdır.              */
/*                                                                           */  
/*---------------------------------------------------------------------------*/

void NarcissisticNumber(int z);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				     			 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	         */ 
/* void calculator(void)		                           	   			     */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								       							 */
/* Bu fonksiyon, kullanıcıdan 2 sayı değeri alacak. Önce 1. sayı değerinin	 */ 
/* sıfırdan küçük olup olmadığına bakacak, eğer sıfıra eşit veya küçükse,    */ 
/* başka pozitif bir sayı isteyecek, eğer sayı zaten pozitif ise kullanıcıya */
/* 3 seçenek sunacak "odd number" "factorial number" ve "narcissistic number"*/
/* olarak ve kullanıcı bunlardan birini seçecek(2. sayı değeri) ve seçtiği   */
/* seçeneğe göre bu fonksiyon, kullanucının yapmak istediği fonksiyonu       */ 
/* çağıracak  								    							 */
/*      								     								 */  
/*---------------------------------------------------------------------------*/

void calculator(void);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				     			 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   	     */ 
/* void condition(void)		                           	     	    		 */ 
/* -----------								   							     */   
/* Description                                                               */ 
/* -----------								    							 */ 
/*  Bu fonksiyon, kullanıcı konsola, hatalı bir değer girdiğinde veya        */ 
/*  kullanıcı girdiği değer ile işlemi yapıp bitirdiğinde çağırılacak.       */ 
/*  Kullanıcıya programı devam ettirip ettirmemek istediğini soracak,        */
/*  eğer kullanıcı programı devam ettirmek isterse "calculator" fonksiyonunu */
/*  çağıracak, eğer istemezse ekrana "good bye" yazıp, programı              */
/*  sonlandıracak.						             						 */ 
/*      								    								 */  
/*---------------------------------------------------------------------------*/


void condition(void);
	
int main(void){
	welcome();
	calculator();
	return 0;
}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function calculator 							    						 */
/* -----------																 */
/* Bu fonksiyon, kullanıcıdan 2 sayı değeri alacak. Önce 1. sayı değerinin   */ 
/* sıfırdan küçük olup olmadığına bakacak, eğer sıfıra eşit veya küçükse,    */ 
/* başka pozitif bir sayı isteyecek, eğer sayı zaten pozitif ise kullanıcıya */
/* 3 seçenek sunacak "odd number" "factorial number" ve "narcissistic number"*/
/* olarak ve kullanıcı bunlardan birini seçecek(2. sayı değeri) ve seçtiği   */
/* seçeneğe göre bu fonksiyon, kullanucının yapmak istediği fonksiyonu       */ 
/* çağıracak  								    							 */


void calculator(void){
	int num1;
/* Konsoldan girilecek pozitif tamsayı            							 */
	int num2;
/* Yapılacak işlemi seçmek için, atanan tam sayı   							 */
	printf("Please enter a positive integer :");
	scanf("%d",&num1);
	

	if(num1<=0){
		printf("The entered number is not positive.\n");
		condition();
	}
	else{
		printf("Which property would you like to check?\n");
		printf("1)Odd Number\n");
		printf("2)Factorial Number\n");
		printf("3)Narcissistic number\n");
		printf("Please enter(1/2/3)");
		scanf("%d",&num2);
		if(num2==1){
			OddNumber(num1);
		}
		else if(num2==2){
			FactorialNumber(num1);
		}
		else if(num2==3){

			NarcissisticNumber(num1);
		}
		else{
			printf("This is not 1,2 or 3 !!!");
/* 3 işlemden herhangibiri seçilmezse verilecek hata 						*/
		}

	}

}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			    						 */
/*---------------------------------------------------------------------------*/
/* Function welcome 							    						 */
/* -----------																 */
/*  Bu fonksiyon, program çalıştığında, kullanıcıya hoşgeldin diyerek        */ 
/*  programın amacını söyleyecek.					    					 */ 

void welcome(void){
	printf("***************************************************\n");
	printf("*                    WELCOME!                     *\n");
	printf("*  This program checks whether the given number   *\n");
	printf("* is an odd, a factorial or a narcissictic number *\n");
	printf("***************************************************\n");

}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			    						 */
/*---------------------------------------------------------------------------*/
/* Function condition 							    						 */
/* -----------																 */
/* Bu fonksiyon, kullanıcıdan 2 sayı değeri alacak. Önce 1. sayı değerinin   */
/* sıfırdan küçük olup olmadığına bakacak, eğer sıfıra eşit veya küçükse,    */ 
/* başka pozitif bir sayı isteyecek, eğer sayı zaten pozitif ise kullanıcıya */
/* 3 seçenek sunacak "odd number" "factorial number" ve "narcissistic number"*/
/* olarak ve kullanıcı bunlardan birini seçecek(2. sayı değeri) ve seçtiği   */
/* seçeneğe göre bu fonksiyon, kullanucının yapmak istediği fonksiyonu       */ 
/* çağıracak  								    							 */


void condition(void){
	char cevap;
/* Devam etmek istiyormusunuz sorusuna cevap vermek için atanan karakter	 */

	printf("Do you want to continue (y/n)?");
	scanf(" %s",&cevap);
	switch(cevap){
		case 'y': calculator(); break;
		case 'n': printf("Good bye!\n"); break;
		default : printf("Please enter y or n \n"); condition();
	}

}

/*---------------------------------------------------------------------------*/
/*			Function Implementations			     						 */
/*---------------------------------------------------------------------------*/
/* Function OddNumber 							    						 */
/* -----------																 */
/*  Bu fonksiyon, girilen sayının faktoriyel bir sayı olup olmadığını        */
/*  kontrol edecek. Konsola girilen sayıyı, sayı birden büyük eşit olduğu    */ 
/*  sürece, sürekli olarak 1 den başlayıp artarak, bölecek ve en sonunda     */
/*  bölüm 1 olursa, sayının faktoriyel bir sayı olduğunu, 1 olmazsa,         */
/*  sayının faktoriyel bir sayı olmadığını söyleyecek.                       */


void OddNumber(int x){
	if(x%2==0){
		printf("%d is not an odd number!\n",x);
		condition();
	}
	else{
		printf("%d is an odd number.\n",x);
		condition();
	}
}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function FactorialNumber 					            				 */
/* -----------																 */
/*  Bu fonksiyon, girilen sayının faktoriyel bir sayı olup olmadığını        */ 
/*  kontrol edecek. Konsola girilen sayıyı, sayı birden büyük eşit olduğu    */ 
/*  sürece, sürekli olarak 1 den başlayıp artarak, bölecek ve en sonunda     */
/*  bölüm 1 olursa, sayının faktoriyel bir sayı olduğunu, 1 olmazsa,         */
/*  sayının faktoriyel bir sayı olmadığını söyleyecek.                       */


void FactorialNumber(int y){
	int i;
/* Girilen sayıyı her seferinde böleceğimiz sayı, 1 den başlatıyoruz ve n=1 
veya n<1 olana kadar i yi arttırıp, tekrar tekrar bölünen sayıya bölüyoruz.  */
	double n;
/* Girilen sayı, ve bu sayıyı her seferinde böldükten sonra atadığımız değişken
 */
	i=1;
	n=y;
	while(y>=1)
	{
		n=n/i;
		i+=1;
		if(n==1)
		{
			printf("%d is factorial number.\n",y);
			condition();
			break;
		}
		else if(n<1)
		{
			printf("%d is not factorial number!\n",y);
			condition();
			break;
		}
	}	
}

/*---------------------------------------------------------------------------*/
/*			Function Implementations			     						 */
/*---------------------------------------------------------------------------*/
/* Function FactorialNumber 					             				 */
/* ----------- 																 */
/*  Bu fonksiyon, konsoldan girilen sayının, narsistik olup olmadığını       */ 
/*  kontrol edecek.Öncelikle sayının değerini bir değişkene atayacak ve o    */ 
/*  değişkenin değeri 0 olana kadar, 10 a bölecek. Her 10 a böldüğünde       */
/*  i 1 kez artacak ve böylece girilen sayının basamak sayısı "i" olacak.    */
/*  Basamak sayısını bulduktan sonra, while döngüsü ile girilen sayıyı       */
/*  basamaklarına ayırıp her basamağın, basamak sayısı ile kuvveti alınacak  */ 
/*  ve "if statement" ile sonucun, girilen sayıya eşit olup  olmadığını      */
/*  kontrol ediyor eğer eşitse, gerilen sayı narsistik sayıdır.              */

void NarcissisticNumber(int z){
	int a;
/* Basamak sayısını bulmak için, konsola girilen değerin atandığı karakter   */
	int i;
/* Girilen sayının basamak sayısı                                            */
	int top;
/* Basamaklarına ayrılmış, sayıların kuvvetini alıp toplayacak.              */
	int x;
/* Girilen sayıyı basamaklara ayırmak için, konsola girilen değerin atandığı 
karakter 								    */
	int l;
/* Sayının basamaklarının, basamak sayısına göre kuvvetini alacak            */
	top=0;
	a=z;
	x=z;
	for(i=0;a>0;++i){
		a=a/10;
	}
	while (x>=1){
		l=x%10;
		l=pow(l,i);
		top=top+l;		
		x=x/10;
	}

	if(top==z){
		printf("%d is a narcissistic number\n",z);
		condition();
	}
	else{
		printf("%d is not a narcissictic number\n",z);
		condition();
	}

}
/*---------------------------------------------------------------------------*/
/*                           End of main.c 				     				 */
/*---------------------------------------------------------------------------*/
