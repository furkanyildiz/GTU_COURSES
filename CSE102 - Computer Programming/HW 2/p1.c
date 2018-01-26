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
/*    For the first part of the homework II, which are used for calculating */
/*      the final grade  		 				    */ 
/*                                                                          */ 
/*------------------------------------------------------------------------  */ 



#include <stdio.h>
void calculateLastGrade();
int main(void){
	calculateLastGrade();



	return 0;

}

/*---------------------------------------------------------------------------*/
/*                         Function Prototypes 				     */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*                                                              	     */
/* 		      void calculateLastGrade()                              */
/* -----------								     */
/* Description                                                               */
/* -----------								     */
/*     Bu fonksiyon, kullanıcıdan 1. midterm, 1. homework ve final exam      */
/*     sınavlarının ağırlıklarını ve notlarını alarak, kullanıcının          */
/*     final grade'sini hesaplıyor.  		                             */
/*                                                            		     */ 
/*---------------------------------------------------------------------------*/ 






void calculateLastGrade(){


	float mt1w,hw1w,f1w,mt1g,hw1g,final1g,fgrade1;

	printf("Please enter the 1. midterm weight:");
	scanf("%f",&mt1w);
	printf("Please enter the 1. homework weight:");
	scanf("%f",&hw1w);
	printf("Please enter the final exam weight:");
	scanf("%f",&f1w);
	printf("Please enter the 1. midterm grade:");
	scanf("%f",&mt1g);
	printf("Please enter the 1. homework grade:");
	scanf("%f",&hw1g);
	printf("Please enter the final exam grade:");
	scanf("%f",&final1g);
	
	fgrade1= ((mt1w*mt1g)+(hw1w*hw1g)+(f1w*final1g))/100; 
/*    Final gradeyi, hesaplatmak için "fgrade1" adında bir değişken          */
/*    tanımlıyoruz ve bu değişkene gerekli matematiksel işlemleri atıyoruz.  */
	printf("Your final grade is: %f\n",fgrade1);

}
