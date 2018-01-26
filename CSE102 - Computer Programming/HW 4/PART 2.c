/* -----------------------------------------------------------------------   */ 
/*                                                                           */ 
/* HW04_141044031_FÜRKAN_YILDIZ 		                                     */
/*                                                                           */ 
/* main.c                                                                    */ 
/* -----------------------------------------------------------------------   */ 
/* Created on 23/03/2016 by FÜRKAN YILDIZ                                    */ 
/*                                                                           */ 
/* Description                                                               */ 
/* -----------------------------------------------------------------------   */
/* 4. Ödevin 2. partında program, kullanıcıdan pozitif tam sayılar alınacak  */
/* ve ASCII sanatıyla bu sayı ekrana bastırılacak. Bastırılacak numaranın    */
/* yanı sıra kullanıcı ayrıca sayının etrafında oluşturulacak çerçevenin     */
/* boyutunu ve sayıyı çizdireceği karakteri girecek. Tüm datalar 7x7         */
/* boyutunda bastırılacak.Ayrıca kullanıcı en fazla 5 haneli sayı girmeli.   */
/*                                                                           */ 
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/*                                 Includes 			                     */
/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void getInputs(int *num, int *borderWidth, char *borderChar)		         */
/*	*num  - Konsoldan çizdirmek için girilen sayı    				  		 */
/*	*borderWidth  - Konsoldan çerçeve kalınlığı için girilen sayı    		 */
/*	*borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, Konsoldan çizdirilecek sayının, çerçeve genişliğinin       */ 
/*  ve sayının hangi karakterle çizdirileceğinin değerlerini alacak		     */ 
/*                                                            		     	 */  
/*---------------------------------------------------------------------------*/
void getInputs(int *num, int *borderWidth, char *borderChar);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* int printNumber(int num, int borderWidth, char borderChar)		         */
/*	num  - Konsoldan çizdirmek için girilen sayı    				  		 */
/*	borderWidth  - Konsoldan çerçeve kalınlığı için girilen sayı    		 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, Tüm fonksiyonların birleşip anlam kazandığı yer.           */
/*  Sayılar burada basılacak, çerçeve burada basılacak.                      */ 
/*  		     															 */ 
/*                                                            		     	 */  
/*---------------------------------------------------------------------------*/
int printNumber(int num, int borderWidth, char borderChar);

/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void Border(int borderWidth, char borderChar)					         */
/*	borderWidth  - Çerçevenin kalınlığı				          				 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */  
/*  Bu fonksiyon, Basılan sayının üstüne ve altına çerçeve çizecek.          */ 
/*  		     															 */ 
/*                                                            		     	 */  
/*---------------------------------------------------------------------------*/
void Border(int borderWidth, int numberOfSize, char borderChar);

/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void BorderIn(int borderWidth, char borderChar)					         */
/*	borderWidth  - Çerçevenin kalınlığı				          				 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, basılan sayıların yanındaki (sağındaki ve solundaki) 	     */ 
/*  çerçeveleri oluşturacak. Bu çerçeveyi "printNumber"	fonksiyonunda	     */ 
/*  satır satır döngüyle oluşturacak.                                        */ 
/*                                                            		     	 */ 
/*---------------------------------------------------------------------------*/
void BorderIn(int borderWidth, char borderChar);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void One(int line, int borderChar)								         */
/*	line  - İşlem yapacağımız satır numarası          				  		 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, "1" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "1" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*                                                            		     	 */ 
/*---------------------------------------------------------------------------*/
void One(int line, int borderChar);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void Two(int line, int borderChar)								         */
/*	line  - İşlem yapacağımız satır numarası          				  		 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, "2" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "2" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*                                                            		     	 */ 
/*---------------------------------------------------------------------------*/
void Two(int line, int borderChar);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void Three(int line, int borderChar)								         */
/*	line  - İşlem yapacağımız satır numarası          				  		 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, "3" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "3" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*                                                            		     	 */ 
/*---------------------------------------------------------------------------*/
void Three(int line, int borderChar);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void Four(int line, int borderChar)								         */
/*	line  - İşlem yapacağımız satır numarası          				  		 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, "4" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "4" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*                                                            		     	 */ 
/*---------------------------------------------------------------------------*/
void Four(int line, int borderChar);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void Five(int line, int borderChar)								         */
/*	line  - İşlem yapacağımız satır numarası          				  		 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, "5" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "5" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*                                                            		     	 */ 
/*---------------------------------------------------------------------------*/
void Five(int line, int borderChar);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void Six(int line, int borderChar)								         */
/*	line  - İşlem yapacağımız satır numarası          				  		 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, "6" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "6" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*                                                            		     	 */ 
/*---------------------------------------------------------------------------*/
void Six(int line, int borderChar);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void Seven(int line, int borderChar)								         */
/*	line  - İşlem yapacağımız satır numarası          				  		 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, "7" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "7" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*                                                            		     	 */ 
/*---------------------------------------------------------------------------*/
void Seven(int line, int borderChar);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void Eight(int line, int borderChar)								         */
/*	line  - İşlem yapacağımız satır numarası          				  		 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, "8" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "8" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*                                                            		     	 */ 
/*---------------------------------------------------------------------------*/
void Eight(int line, int borderChar);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void Nine(int line, int borderChar)								         */
/*	line  - İşlem yapacağımız satır numarası          				  		 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, "9" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "9" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*                                                            		     	 */ 
/*---------------------------------------------------------------------------*/
void Nine(int line, int borderChar);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void Zero(int line, int borderChar)								         */
/*	line  - İşlem yapacağımız satır numarası          				  		 */
/*	borderChar  - Konsoldan sayının hangi karekterle çizdirileceğini 		 */
/*  ifade eden karakter														 */ 
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, "0" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "0" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*                                                            		     	 */ 
/*---------------------------------------------------------------------------*/
void Zero(int line, int borderChar);


int main(){
	/* Kullanıcıdan alınan sayı */
	int num;
	/* Kullanıcıdan alınan genişlik */
	int borderWidth;
	/* Kullanıcıdan alınan karakter(çizilecek sayı için) */
	char borderChar;
	
	getInputs(&num,&borderWidth,&borderChar);
	printNumber(num,borderWidth,borderChar);



	return 0;
}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function getInputs 							    						 */
/* -----------																 */
/* Bu fonksiyon, kullanıcıdan 2 sayı değeri alacak. Önce 1. sayı değerinin   */ 
/* sıfırdan küçük olup olmadığına bakacak, eğer sıfıra eşit veya küçükse,    */ 
/* başka pozitif bir sayı isteyecek, eğer sayı zaten pozitif ise kullanıcıya */
/* 3 seçenek sunacak "odd number" "factorial number" ve "narcissistic number"*/
/* olarak ve kullanıcı bunlardan birini seçecek(2. sayı değeri) ve seçtiği   */
/* seçeneğe göre bu fonksiyon, kullanucının yapmak istediği fonksiyonu       */ 
/* çağıracak  								    							 */
/*---------------------------------------------------------------------------*/
void getInputs(int* num, int* borderWidth, char* borderChar){

	scanf("%d %d %c",num, borderWidth,borderChar);
	
}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function printNumber 							    					 */
/* -----------																 */
/*  Bu fonksiyon, Basılan sayının üstüne ve altına çerçeve çizecek.          */ 
/*---------------------------------------------------------------------------*/
int printNumber(int num, int borderWidth, char borderChar){
/* Basım işlemi yapılacak satır */
	int line;
	int i;
/* Girilen sayının basamaklara ayrılarak atıldığı değişken  */
	int num1;
/* Girilen sayının basamak numarası  */
	int numberOfSize;
/* Girilen sayıyı değiştirmeden onun üzerinden işlem yapılabilmesi için girilen
sayının atandığı değişken */
	int a;
	if(num<=99999 && num>=0){
		a=num;
	 	for(numberOfSize=0;a>0;++numberOfSize){
			a=a/10;
		}
		Border(borderWidth,numberOfSize,borderChar);
		for(line=0; line<=6; line++){
			BorderIn(borderWidth,borderChar);
			for(i=1; i<=numberOfSize; i++){
				num1=num/pow(10,numberOfSize-i);
				num1%=10;

				switch(num1){
					case 1: One(line,borderChar);   break;
					case 2: Two(line,borderChar);   break;
					case 3: Three(line,borderChar); break;
					case 4: Four(line,borderChar);  break;
					case 5: Five(line,borderChar);  break;
					case 6: Six(line,borderChar);   break;
					case 7: Seven(line,borderChar); break;
					case 8: Eight(line,borderChar); break;
					case 9: Nine(line,borderChar);  break;
					case 0: Zero(line,borderChar);  break;
					default: break;
			
				}
		
		
			}
		BorderIn(borderWidth,borderChar);
		printf("\n");
		}

		Border(borderWidth,numberOfSize,borderChar);
		return 1;
	}
	else
		return 0;
}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function Border		 							    					 */
/* -----------																 */
/*  Bu fonksiyon, Basılan sayının üstüne ve altına çerçeve çizecek.          */ 
/*---------------------------------------------------------------------------*/
void Border(int borderWidth, int numberOfSize, char borderChar){
	int j;
	int i;
	int k;
	for(j=0; j<borderWidth; j++){
		for(i=1; i<=numberOfSize; i++){
			printf("%c%c%c",borderChar,borderChar,borderChar);
			printf("%c%c%c%c",borderChar,borderChar,borderChar,borderChar);
		}
		for(k=1; k<=2*borderWidth; k++){
			printf("%c",borderChar);
		}
		printf("\n");
	
	}
}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function BorderIn	 							    					 */
/* -----------																 */
/*  Bu fonksiyon, basılan sayıların yanındaki (sağındaki ve solundaki) 	     */ 
/*  çerçeveleri oluşturacak. Bu çerçeveyi "printNumber"	fonksiyonunda	     */ 
/*  satır satır döngüyle oluşturacak.                                        */ 
/*---------------------------------------------------------------------------*/
void BorderIn(int borderWidth, char borderChar){
	int i;
	for(i=0; i<borderWidth; i++){
		printf("%c",borderChar);
	}
}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function One			 							    					 */
/* -----------																 */
/*  Bu fonksiyon, "1" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "1" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*---------------------------------------------------------------------------*/
void One(int line, int borderChar){

	switch(line){
	
	case 0: printf("       "); break;
	case 1: printf("   %c   ",borderChar); break;
	case 2: printf("  %c%c   ",borderChar,borderChar); break;
	case 3: printf("   %c   ",borderChar); break;
	case 4: printf("   %c   ",borderChar); break;
	case 5: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 6: printf("       "); break;
	default: break;
	}


}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function Two			 							    					 */
/* -----------																 */
/*  Bu fonksiyon, "2" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "2" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*---------------------------------------------------------------------------*/
void Two(int line, int borderChar){

	switch(line){
	
	case 0: printf("       "); break;
	case 1: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 2: printf("    %c  ",borderChar); break;
	case 3: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 4: printf("  %c    ",borderChar); break;
	case 5: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 6: printf("       "); break;
	default: break;
	
	
	
	}

}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function Three		 							    					 */
/* -----------																 */
/*  Bu fonksiyon, "3" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "3" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*---------------------------------------------------------------------------*/
void Three(int line, int borderChar){

	switch(line){

	case 0: printf("       "); break;
	case 1: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 2: printf("    %c  ",borderChar); break;
	case 3: printf("   %c%c  ",borderChar,borderChar); break;
	case 4: printf("    %c  ",borderChar); break;
	case 5: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 6: printf("       "); break;
	default: break;
	
	
	
	}

}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function Four		 							    					 */
/* -----------																 */
/*  Bu fonksiyon, "4" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "4" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*---------------------------------------------------------------------------*/
void Four(int line, int borderChar){

	switch(line){
	
	case 0: printf("       "); break;
	case 1: printf("  %c %c  ",borderChar,borderChar); break;
	case 2: printf("  %c %c  ",borderChar,borderChar); break;
	case 3: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 4: printf("    %c  ",borderChar); break;
	case 5: printf("    %c  ",borderChar); break;
	case 6: printf("       "); break;
	default: break;
	
	
	
	}

}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function Five		 							    					 */
/* -----------																 */
/*  Bu fonksiyon, "5" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "5" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*---------------------------------------------------------------------------*/

void Five(int line, int borderChar){


	switch(line){
	
	case 0: printf("       "); break;
	case 1: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 2: printf("  %c    ",borderChar); break;
	case 3: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 4: printf("    %c  ",borderChar); break;
	case 5: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 6: printf("       "); break;
	default: break;
	
	
	
	}

}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function Six			 							    					 */
/* -----------																 */
/*  Bu fonksiyon, "6" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "6" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*---------------------------------------------------------------------------*/
void Six(int line, int borderChar){

	switch(line){
	
	case 0: printf("       "); break;
	case 1: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 2: printf("  %c    ",borderChar); break;
	case 3: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 4: printf("  %c %c  ",borderChar,borderChar); break;
	case 5: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 6: printf("       "); break;
	default: break;
	
	
	
	}

}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function Seven 									    					 */
/* -----------																 */
/*  Bu fonksiyon, "7" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "7" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*---------------------------------------------------------------------------*/
void Seven(int line, int borderChar){


	switch(line){
	
	case 0: printf("       "); break;
	case 1: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 2: printf("    %c  ",borderChar); break;
	case 3: printf("    %c  ",borderChar); break;
	case 4: printf("    %c  ",borderChar); break;
	case 5: printf("    %c  ",borderChar); break;
	case 6: printf("       "); break;
	default: break;
	
	
	
	}

}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function Eight		 							    					 */
/* -----------																 */
/*  Bu fonksiyon, "8" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "8" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*---------------------------------------------------------------------------*/
void Eight(int line, int borderChar){


	switch(line){
	
	case 0: printf("       "); break;
	case 1: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 2: printf("  %c %c  ",borderChar,borderChar); break;
	case 3: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 4: printf("  %c %c  ",borderChar,borderChar); break;
	case 5: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 6: printf("       "); break;
	default: break;
	
	
	
	}

}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function Nine 							    							 */
/* -----------																 */
/*  Bu fonksiyon, "9" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "9" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*---------------------------------------------------------------------------*/
void Nine(int line, int borderChar){

	switch(line){
	
	case 0: printf("       "); break;
	case 1: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 2: printf("  %c %c  ",borderChar,borderChar); break;
	case 3: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 4: printf("    %c  ",borderChar); break;
	case 5: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 6: printf("       "); break;
	default: break;
	
	
	
	}

}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function Zero		 							    					 */
/* -----------																 */
/*  Bu fonksiyon, "0" sayısının satırlarını içeren bir yapıya sahip	         */ 
/*  bu fonksiyon içinde "0" sayısının satırlarını tek tek yazarak, bu        */ 
/*  fonksiyonu çağıracağız.                                                  */ 
/*---------------------------------------------------------------------------*/
void Zero(int line, int borderChar){


	switch(line){
	
	case 0: printf("       "); break;
	case 1: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 2: printf("  %c %c  ",borderChar,borderChar); break;
	case 3: printf("  %c %c  ",borderChar,borderChar); break;
	case 4: printf("  %c %c  ",borderChar,borderChar); break;
	case 5: printf("  %c%c%c  ",borderChar,borderChar,borderChar); break;
	case 6: printf("       "); break;
	default: break;
	
	}

}
