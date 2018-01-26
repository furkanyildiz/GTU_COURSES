/* -----------------------------------------------------------------------  */ 
/*                                                                          */ 
/*                   HW01_141044031_FÜRKAN_YILDIZ                           */ 
/*                                                                          */ 
/*                                                                          */ 
/* -----------------------------------------------------------------------  */ 
/*                Created on 19/02/2016 by FÜRKAN YILDIZ                    */ 
/*                                                                          */ 
/* Description                                                              */ 
/* -----------------------------------------------------------------------  */
/*    For the first part of the homework I, which are used for calculating  */
/*      the final grade  		 				    */ 
/*                                                                          */ 
/*------------------------------------------------------------------------  */ 






#include <stdio.h>
int main(void){
	float fmidtermw;
	float smidtermw;
	float tmidtermw;
	float fhww;
	float shww;
	float fw;
	float fmidtermg;
	float smidtermg;
	float tmidtermg;
	float fhwg;
	float shwg;
	float fg;
	float finalgrade;


	printf("Please enter the 1. midterm weight:");
	scanf("%f",&fmidtermw);
	printf("Please enter the 2. midterm weight:");
	scanf("%f",&smidtermw);
	printf("Please enter the 3. midterm weight:");
	scanf("%f",&tmidtermw);
	printf("Please enter the 1. homework weight:");
	scanf("%f",&fhww);
	printf("Please enter the 2. homework weight:");
	scanf("%f",&shww);
	printf("Please enter the final exam weight:");
	scanf("%f",&fw);
	printf("Please enter the 1. midterm grade:");
	scanf("%f",&fmidtermg);
	printf("Please enter the 2. midterm grade:");
	scanf("%f",&smidtermg);
	printf("Please enter the 3. midterm grade:");
	scanf("%f",&tmidtermg);
	printf("Please enter the 1. homework grade:");
	scanf("%f",&fhwg);
	printf("Please enter the 2. homework grade:");
	scanf("%f",&shwg);
	printf("Please enter the final exam grade:");
	scanf("%f",&fg);
	
	finalgrade = (fmidtermg*fmidtermw + smidtermg*smidtermw + 
	tmidtermg*tmidtermw + fhwg*fhww + shwg*shww + fg*fw) / 100;	
   	/* Final notunun matematiksel olarak hesaplanması. */
	printf("Your final grade is: %f\n",finalgrade);



	return 0;

}
