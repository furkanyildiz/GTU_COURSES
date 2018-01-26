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
/* 4. Ödevin 1. partında program, sinüs ve kosünüs değerleri Taylor serisi   */
/* yardımıyla hesaplanacak. Hesaplama için kullanıcıdan, hesaplanmak istenen */
/* açı ve seride hesaplanmak istenilen ilk n terim istenilecek.			     */
/* Program, girilen bu açı ve n değerine göre, sinüs ve kosinüsün değerlerini*/
/* hesaplayacak. (Math kütüphanesi kullanmadan.) Ayrıca açı yerine "e" veya  */
/* "E" girilirse, exit değerine 1 atanarak çıkış yapılacak. Aksi durumda ise */
/* exit değeri sıfır olarak atanacak.                                        */
/*---------------------------------------------------------------------------*/
#include <stdio.h>
#define PI 3.14
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void getInputs(int* degree, int* n, int* exit)		  			         */
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
void getInputs(int* degree, int* n, int* exit);
double pow(double x,double n);
double factorial(int n);
double sine(int degree, int n);
double cosine(int degree, int n);

int main(){
	int n,degree,exit;
	exit=0;
	/*printf("pow %f\n",pow(90,48));*/
	/*printf("fac %f\n",factorial(48));*/

	
	/*while(exit==0){*/
	
		getInputs(&degree,&n,&exit);

	/*}*/
	printf("sin(%d) where n is %d =%.4f\n",degree,n,sine(degree,n));
	printf("cos(%d) where n is %d =%.4f\n",degree,n,cosine(degree,n));

	return 0;	
}
void getInputs(int* degree, int* n, int* exit){
	char chrac;
	int i;
	int h,m;
	i=0;
	m=0;
	h=0;
	scanf("%c",&chrac);
	if(chrac== 'e' || chrac=='E'){
		*exit=1;
		return;
	}
	else{
		i=0;
	
		for(; (chrac>='0' && chrac<='9')  || (chrac ==' ' );  scanf("%c",&chrac))
		{
		
			if(chrac==' '){
				i=1;
				}
			else{
				if(i==0){
					h = h * 10 + (chrac - '0' );
				}
				 if(i==1){
					m = m * 10 + (chrac - '0' );
				}
				}
		}
		if(*degree>360)
    		*degree=*degree % 360;
		*degree=h;
		*n=m;
	}

	h=0;
	m=0;
}

/*
	int a;
	char c;
	a=scanf("%d %d",num, mum);
	
###scanf in değeri burada 2 num girilirse 2 olacak, hiç girilmez direk
	sayı girilirse 0 olacak. Eğer değer sıfırsa hemen alttaki if else ye girecek,
	yukaradki scanf char girildiğinden onu okuyamadı ve bir yerde tuttu. İlk
	scanf o charı okumak için bekliyor. Yani yazacağımız ilk charlı scanf, bizden
	değer istemeyecek, o saklanan charı okuyacak. okuduktan sonra o değer eğer 'e'
	veya 'E' ise *ezit değerini 1 yapacak. Aksi durumda hep sıfır.
	
	
	if(a==0)
		scanf("%c",k);
		if(c=='e' || c== 'E')
			*exit=1;
	else
		*exit=0;
*/

double pow(double x,double n){ /* NEGATİFLER İÇİN CALISMIYOR*/
	int i;
	double b;
	b=1.0;
	if(n==0){
		b=1;
		return b;
	}
	else if(n==1){
		b=x;
		return b;
	}
	else{
		for(i=1; i<=n; i++){
			b=b*x;
		}
		return b;
	}	
}

double factorial(int n){
	int i,a;
	a=1;
	
	for(i=1; i<=n; i++){
		a=a*i;
	}
	return a;
}

double sine(int degree, int n){
	double a;
	double b;
	double c,i,k,sum,l;
	if(degree>360)
    	degree=degree % 360;
	l=degree;
	l=l*PI/180.0;
	sum=0;
	
	do{
		for(i=0; i<n; i++){

			a=pow(-1,i);
			b=pow(l,2*i+1);
			c=factorial(2*i+1);
			k=a*b/c;
			sum+=k;
		}
	}while(sum<=-1 && sum>=1);
		return sum;
	
}
double cosine(int degree, int n){

	double a,b,c,i,k,sum,l;
	if(degree>360)
    	degree=degree % 360;
	l=degree;
	l=l*PI/180.0;
	sum=0;
	do{
	for(i=0; i<n; i++){
		a=pow(-1,i);
		b=pow(l,2*i);
		c=factorial(2*i);
		k=a*b/c;
		sum+=k;
	}
	}while(sum<=-1.0 && sum>=1.0);

	
	
	
	return sum;
}
