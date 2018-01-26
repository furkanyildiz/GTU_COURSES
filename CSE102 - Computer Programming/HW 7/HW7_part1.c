/* -----------------------------------------------------------------------   */ 
/*                                                                           */ 
/* HW04_141044031_FÜRKAN_YILDIZ 		                                     */
/*                                                                           */ 
/* main.c                                                                    */ 
/* -----------------------------------------------------------------------   */ 
/* Created on 12/04/2016 by FÜRKAN YILDIZ                                    */ 
/*                                                                           */ 
/* Description                                                               */ 
/* -----------------------------------------------------------------------   */
/* The 7. Homework is a recursive palindrome finder function. A palindrome   */
/* is a sequence of characters which reads the same backward or forward.     */
/* In the input string, there may be punctuations, spaces etc. that the      */
/* program must ignore. The program will match only letters. For example,    */
/* “ab, cd!ed~cb%a” is a palindrome but "ab!ab" is not.					  	 */
/* The function must work case insensitive. For example, “AbcDedCba” is a    */
/* palindrome. function returns 1 if the given string is a palindrome, 		 */
/* otherwise (any invalid conditions and not palindrome) it returns 0. 		 */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                                 Includes 			                     */
/*---------------------------------------------------------------------------*/
#include <stdio.h>

/*--------------------------------------------------------------------------- */ 
/*                         Function Prototypes 				   				  */ 
/*--------------------------------------------------------------------------- */
/*--------------------------------------------------------------------------- */ 
/*                                                              	   		  */ 
/* int isPalindrome(char * str)	        								 	  */
/*	*str  - Palidrom olup olmadığını kontrol edeceğimiz string. 	  		  */
/* -----------								     							  */   
/* Description                                                                */ 
/* -----------								     							  */ 
/*  Bu fonksiyon,verilen stringin, boyutunu hesaplayıp,"TheStrPalindromeOrNot"*/ 
/*  fonksiyonuna yollayacak. daha sonra oradan gelen değeri return edecek     */ 
/*                                                            		     	  */  
/*--------------------------------------------------------------------------- */
int isPalindrome(char * str);
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* int TheStrPalindromeOrNot(char *str, int size);	        				 */
/*	*str  - Palidrom olup olmadığını kontrol edeceğimiz string. 	  		 */
/*	size  - Palidrom olup olmadığını kontrol edeceğimiz stringin boyutu		 */
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon,verilen stringin palidrom olup olmadığını araştıracak.  	  */ 
/*  Önce verilen stringin size'ına bakacak, 1 den küçükse veya NULL'sa 		  */ 
/*  (string yoksa), 0 return edecek. Stringin boyutu 1 den büyükse, 		  */ 
/*  stringin 0. ve sonuncu elemanına bakacak, eğer a-z veya A-Z aralığındaysa */ 
/*  ikiside, yeni bir if döngüsüne girecek bu döngüde, stringin ilk elemanı	  */ 
/*  ile son elemanı eşitse veya ilk ve son eleman arasında 32 fark varsa 	  */ 
/*  (büyük ve küçük harfler eş sayılacağından a=A gibi, ASCII değerleri farkı */ 
/*  nı kullanıyoruz bu eşliği anlamak için orneğin (a-A=32)), tekrar aynı     */
/*  fonksiyonu çağırarak içeride fakat bu sefer 1. ve sonuncu elemanları eş   */
/*  buluğumuzdan artık onları tekrar tekrar kontrol etmemize gerek yok, 	  */
/*  onları stringden silebiliriz silmek içinde  fonksiyonu tekrar çağırırken, */
/*  parametre olarak fonksiyona stringin 1. elemanının adresini ve size-2 yi  */
/*  veriyoruz (hem baştan hem sonran eleman sildiğimizden size-2), stringin   */
/*  ilk elemanı ile son elemanı eşit değilse direk return 0 yapmalıyız.       */ 
/*  Çünkü palidromu bir çift eşit olmayan harf dahi bozacaktır.   			  */ 
/*  Bu arada fonksiyon, harf dışında her şeyi ignore edeceğinden,			  */ 
/*  örneğin ilk eleman harf dışında bir şey ise ilk  elemanı siliyoruz,       */ 
/*  içeride kendi fonksiyonunu çağırarak (stringin 1. adresi ile) ve bir      */ 
/*  eleman  sildiğimizden size bir azalıyor. Eğer stringin son  elemanı harf  */ 
/*  dışında bir şey ise, son elemanı silmek için size'ı bir azaltıyoruz.      */ 
/*  Eğer stringin hem 1. hemde sonuncu elemanı harf değilse, 1. ve sonuncu    */ 
/*  elemanı silmeliyiz.Fonksiyonu, stringin 1. adresini vererek ve ve size'ı  */ 
/*  2 azaltarak tekrar çağırıyoruz. Bu şekilde fonksiyonu tekrar çağırarak,   */
/*  baştan veya sondan eleman silerek programa devam ederken, size eğer 2 	  */
/*  olursa, 1. ve 2. elemanın eşit olup olmadığına bakacak, eğer eşitlerse,   */
/*  1 return edecek. Eğer size bir olursa direk 1 return edecek				  */
/*  çünkü tek kalan harfin önenmi yoktur, sondanda baştanda aynı okunur.      */  
/*--------------------------------------------------------------------------- */
int TheStrPalindromeOrNot(char *str, int size);
int main(){

	char *string ="    a+^%+^45%/%^a484564^f+65d+^&/+4^'+'^554a a    ";
	printf("returns: %d\n",isPalindrome(string));
	printf("%s",string);
	return 0;
}
/*--------------------------------------------------------------------------- */
/*			Function Implementations			   						      */
/*--------------------------------------------------------------------------- */

/*--------------------------------------------------------------------------- */
/* Function isPalindrome 							    					  */
/* -----------																  */
/*  Bu fonksiyon,verilen stringin boyutunu hesaplayacak. Daha sonra bu string */ 
/*  de en az 1 harf olup olmadığına bakacak. Çünkü en az 1 harf yoksa, 		  */
/*  palidrom olma olasılığıda yoktur. Eğer en az 1 harf varsa, hesaplanan 	  */ 
/*  boyut ile birlikte, stringi "TheStrPalindromeOrNot" fonksiyonuna 		  */
/*  gönderecek ve ordan gelen değeri return edecek.							  */ 
/*--------------------------------------------------------------------------- */
int isPalindrome(char * str){

	int size;
	int i;
	int count=0;

	for(size=0; str[size]!= '\0'; size++);
	
	for(i=0; i<size; i++){
		if((str[i]>='a' && str[i]<='z') ||(str[i]>='A' && str[i]<='Z'))
			count++;
	}
	if(count>=1)
		return TheStrPalindromeOrNot(str,size);
	else
		return 0;

}
/*--------------------------------------------------------------------------- */
/* Function TheStrPalindromeOrNot 							    			  */
/* -----------																  */
/*  Bu fonksiyon,verilen stringin palidrom olup olmadığını araştıracak.  	  */ 
/*  Önce verilen stringin size'ına bakacak, 1 den küçükse veya NULL'sa 		  */ 
/*  (string yoksa), 0 return edecek. Stringin boyutu 1 den büyükse, 		  */ 
/*  stringin 0. ve sonuncu elemanına bakacak, eğer a-z veya A-Z aralığındaysa */ 
/*  ikiside, yeni bir if döngüsüne girecek bu döngüde, stringin ilk elemanı	  */ 
/*  ile son elemanı eşitse veya ilk ve son eleman arasında 32 fark varsa 	  */ 
/*  (büyük ve küçük harfler eş sayılacağından a=A gibi, ASCII değerleri farkı */ 
/*  nı kullanıyoruz bu eşliği anlamak için orneğin (a-A=32)), tekrar aynı     */
/*  fonksiyonu çağırarak içeride fakat bu sefer 1. ve sonuncu elemanları eş   */
/*  buluğumuzdan artık onları tekrar tekrar kontrol etmemize gerek yok, 	  */
/*  onları stringden silebiliriz silmek içinde  fonksiyonu tekrar çağırırken, */
/*  parametre olarak fonksiyona stringin 1. elemanının adresini ve size-2 yi  */
/*  veriyoruz (hem baştan hem sonran eleman sildiğimizden size-2), stringin   */
/*  ilk elemanı ile son elemanı eşit değilse direk return 0 yapmalıyız.       */ 
/*  Çünkü palidromu bir çift eşit olmayan harf dahi bozacaktır.   			  */ 
/*  Bu arada fonksiyon, harf dışında her şeyi ignore edeceğinden,			  */ 
/*  örneğin ilk eleman harf dışında bir şey ise ilk  elemanı siliyoruz,       */ 
/*  içeride kendi fonksiyonunu çağırarak (stringin 1. adresi ile) ve bir      */ 
/*  eleman  sildiğimizden size bir azalıyor. Eğer stringin son  elemanı harf  */ 
/*  dışında bir şey ise, son elemanı silmek için size'ı bir azaltıyoruz.      */ 
/*  Eğer stringin hem 1. hemde sonuncu elemanı harf değilse, 1. ve sonuncu    */ 
/*  elemanı silmeliyiz.Fonksiyonu, stringin 1. adresini vererek ve ve size'ı  */ 
/*  2 azaltarak tekrar çağırıyoruz. Bu şekilde fonksiyonu tekrar çağırarak,   */
/*  baştan veya sondan eleman silerek programa devam ederken, size eğer 2 	  */
/*  olursa, 1. ve 2. elemanın eşit olup olmadığına bakacak, eğer eşitlerse,   */
/*  1 return edecek. Eğer size bir olursa direk 1 return edecek				  */
/*  çünkü tek kalan harfin önenmi yoktur, sondanda baştanda aynı okunur.      */  
/*--------------------------------------------------------------------------- */







int TheStrPalindromeOrNot(char *str, int size){
	int ans;
	if(str==NULL)
		return 0;
	else if(size==1)
		return 1;
	else if(size==2 && str[0]==str[size-1])
		return 1;
	else if(size<1)
		return 0;
	/* Stringin ilk ve son elemanı harf ise,*/
	if(((str[0]<='z' && str[0]>='a') || (str[0]<='Z' && str[0]>='A')) &&
	   ((str[size-1]<='z' && str[size-1]>='a') || 
	   (str[size-1]<='Z' && str[size-1]>='A'))){
		if(str[0]==str[size-1] || (str[0]-str[size-1]==32) || 
		  (str[0]-str[size-1]==-32)){
			ans= TheStrPalindromeOrNot(&str[1],size-2);
		}
		else if(str[0]!=str[size-1]) {
			ans= 0;
			}
 	}
 	/* Stringin ilk elemanı, harf değilse, */
  	else if(((str[0]>'z' || str[0]<'a') && (str[0]>'Z' || str[0]<'A')) &&
	   	((str[size-1]<='z' && str[size-1]>='a') || 
	   	(str[size-1]<='Z' && str[size-1]>='A'))){
   		ans= TheStrPalindromeOrNot(&str[1],size-1);	   	
   	}
   	/* Stringin son elemanı, harf değilse, */
	else if(((str[0]<='z' && str[0]>='a') || (str[0]<='Z' && str[0]>='A')) &&
	   ((str[size-1]>'z' || str[size-1]<'a') && 
	   (str[size-1]>'Z' || str[size-1]<'A'))){
		ans= TheStrPalindromeOrNot(str,size-1);
	}
	/* Stringin hem ilk hemde son elemanı, harf değilse, */
	else if(((str[0]>'z' || str[0]<'a') && (str[0]>'Z' || str[0]<'A')) &&
		((str[size-1]>'z' || str[size-1]<'a') && 
	   (str[size-1]>'Z' || str[size-1]<'A'))){
		ans= TheStrPalindromeOrNot(&str[1],size-2);
	}
		return ans;
}
