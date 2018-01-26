/* -----------------------------------------------------------------------  */ 
/*                                                                          */ 
/*                   HW02_141044031_FÜRKAN_YILDIZ                           */ 
/*                                                                          */ 
/*                                                                          */ 
/* -----------------------------------------------------------------------  */ 
/*                Created on 29/02/2016 by FÜRKAN YILDIZ                    */ 
/*                                                                          */ 
/* Description                                                              */ 
/* -----------------------------------------------------------------------  */
/*  For the second part of the homework II, which are used for calculating  */
/*  perimeter of rectangle, square, Circle and area of rectangle,square,    */
/*  circle  		 				     	            */ 
/*                                                                          */ 
/*------------------------------------------------------------------------  */ 


#include <stdio.h>
#define PI 3.14
int areaOfRectangle(int width, int height);
int perimeterOfRectangle(int width, int height);
int areaOfSquare(int edgeLength);
int perimeterOfSquare(int edgeLength);
double areaOfCircle(int radius);
double perimeterOfCircle(int radius);

int main(void){
	
	int width,height,edgeLength;
	double radius;

	printf("Please enter the width of the rectagle:");
	scanf("%d",&width);
	printf("Please enter the height of the rectagle:");
	scanf("%d",&height);
	printf("The area of the rectagle is: %d\n",areaOfRectangle(width,height));
	printf("The perimeter of the rectangle is: %d\n",perimeterOfRectangle(width,height));
	printf("Please enter the width of the square");
	scanf("%d",&edgeLength);
	printf("The area of the square is: %d\n",areaOfSquare(edgeLength));
	printf("The perimeter of the square is: %d\n",perimeterOfSquare(edgeLength));
	printf("Please enter the radius of the circle:");
	scanf("%lf",&radius);
	printf("The area of the circle is: %f\n",areaOfCircle(radius));
	printf("The perimeter of the circle is: %f\n",perimeterOfCircle(radius))	;


	return (0);
}

/*---------------------------------------------------------------------------*/
/*                         Function Prototypes 				     */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*                                                              	     */
/* 		      int areaOfRectangle(int width, int height)             */
/* -----------								     */
/*                                                                           */ 
/*     width Dikdörtgenin uzunluğu                  			     */ 
/*     height Dikdörtgenin yüksekliği                     		     */ 
/*      								     */
/* Description                                                               */
/* -----------								     */
/*     Bu fonksiyon, kullanıcıdan main'den alığı width ve height değişeken   */
/*     lerini kullanarak, dikdörtgenin alanını hesaplayacak.	             */
/*                                                            		     */ 
/*---------------------------------------------------------------------------*/


int areaOfRectangle(int width, int height) {
	return(width*height);
	/* Dikdörtgenin alanını bulmak için, uzun ve kısa kenar çarpılır.    */
}

/*---------------------------------------------------------------------------*/
/*                         Function Prototypes 				     */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*                                                              	     */
/* 		      int perimeterOfRectangle(int width, int height)        */
/* -----------								     */
/*                                                                           */ 
/*     width Dikdörtgenin uzunluğu                  			     */ 
/*     height Dikdörtgenin yüksekliği                     		     */ 
/*      								     */
/* Description                                                               */
/* -----------								     */
/*     Bu fonksiyon, kullanıcıdan main'den alığı width ve height değişeken   */
/*     lerini kullanarak, dikdörtgenin çevresini hesaplayacak.               */
/*                                                            		     */ 
/*---------------------------------------------------------------------------*/



int perimeterOfRectangle(int width, int height) {
/* Dikdörtgenin karşılıklı kenar uzunlukları eşit olduğundan, çevresini bulmak 
	için iki kenar uzunluğunu toplayıp "2" ile çarpmalıyız. */
	return((width+height)*2); 
}

/*---------------------------------------------------------------------------*/
/*                         Function Prototypes 				     */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*                                                              	     */
/* 		      int areaOfSquare(int edgeLength)		             */
/* -----------								     */
/*                                                                           */ 
/*     edgeLength Karenin bir kenarı                  			     */  
/*      								     */
/* Description                                                               */
/* -----------								     */
/*     Bu fonksiyon, kullanıcıdan main'den alığı edgeLength değişekenini     */
/*     kullanarak, karenin alanını hesaplayacak.       	                     */
/*                                                            		     */ 
/*---------------------------------------------------------------------------*/


int areaOfSquare(int edgeLength){
	return(edgeLength*edgeLength);
	/* Karenin tüm uzunlukları eşit olduğundan, alanını hesaplamak için bir 
	kenarının karesini alırız.*/
}


/*---------------------------------------------------------------------------*/
/*                         Function Prototypes 				     */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*                                                              	     */
/* 		      int perimeterOfSquare(int edgeLength)	             */
/* -----------								     */
/*                                                                           */ 
/*     edgeLength Karenin bir kenarı                  			     */  
/*      								     */
/* Description                                                               */
/* -----------								     */
/*     Bu fonksiyon, kullanıcıdan main'den alığı edgeLength değişekenini     */
/*     kullanarak, karenin çevresini hesaplayacak.       	             */
/*                                                            		     */ 
/*---------------------------------------------------------------------------*/



int perimeterOfSquare(int edgeLength) {
/* Karenin tüm kenarları eşit olduğundan bir kenarın uzunluğunu "4" ile
çarparak çevresini elde ederiz.*/
	return(edgeLength*4);



/*---------------------------------------------------------------------------*/
/*                         Function Prototypes 				     */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*                                                              	     */
/* 		      double areaOfCircle(int radius)	            	     */
/* -----------								     */
/*                                                                           */ 
/*     radius dairenin yarıçapı                 			     */  
/*      								     */
/* Description                                                               */
/* -----------								     */
/*     Bu fonksiyon, kullanıcıdan main'den alığı radius değişekenini  	     */
/*     kullanarak, çemberin alanını hesaplayacak.       	             */
/*                                                            		     */ 
/*---------------------------------------------------------------------------*/

}
double areaOfCircle(int radius) {
	return(PI*radius*radius);
/*    Dairenin alan formülü "PI*yarıçapın karesi"dir.			     */
}


/*---------------------------------------------------------------------------*/
/*                         Function Prototypes 				     */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*                                                              	     */
/* 		      double perimeterOfCircle(int radius)	       	     */
/* -----------								     */
/*                                                                           */ 
/*     radius dairenin yarıçapı                 			     */  
/*      								     */
/* Description                                                               */
/* -----------								     */
/*     Bu fonksiyon, kullanıcıdan main'den alığı radius değişekenini  	     */
/*     kullanarak, çemberin çevresini hesaplayacak.       	             */
/*                                                            		     */ 
/*---------------------------------------------------------------------------*/
double perimeterOfCircle(int radius) {
	return(2*PI*radius);
/*    Dairenin çevre formülü "2*PI*yarıçap"tır.			    	     */
}
