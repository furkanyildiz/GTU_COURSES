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
/*      the lived days in earth and another planet.  		 	    */ 
/*                                                                          */ 
/*------------------------------------------------------------------------  */ 


#include <stdio.h>
int main(void){
	/* Değişkenleri tanımlıyoruz  */
	int cyear;
	int cmonth;
	int cday;
	int byear;
	int bmonth;
	int bday;
	int s1;
	int phour;
	int pday;
	int pmonth;
	int s2;
	int s3;
	int s4;
	int s5;
	int s6;

	printf("Please enter the current date.\n");
	printf("Year:");
	scanf("%d", &cyear);
	printf("Month:");
	scanf("%d",&cmonth);
	printf("Day:");
	scanf("%d",&cday);
	printf("Please enter your birthday.\n");
	printf("Year:");
	scanf("%d", &byear);
	printf("Month:");
	scanf("%d",&bmonth);
	printf("Day:");
	scanf("%d",&bday);
	s1=(cyear-byear)*365+(cmonth-bmonth)*30+(cday-bday); 
	/* Dünyada yaşanan toplam gün sayısını s1 ile ifade ettik */
	printf("You have lived %d days.\n",s1);
	
	printf("Please enter about the time of another planet\n");
	printf("How many hours is a day?");
	scanf("%d",&phour);
	printf("How many days is a month?");
	scanf("%d",&pday);
	printf("How many months is a year?");
	scanf("%d",&pmonth);

  	
	s2=s1*24/phour;  /* Total days in the another planet.  */ 
	s3=s2/(pday*pmonth);  /* Planette geçen 1 yıl */ 
	s4=s2-(pday*pmonth*s3); 
	/* Planette geçen toplam günden, yılı hesaplayınca kalan gün sayısı  */
	s5=s4/pday;    /* Planette geçen ay */
	s6=s4-s5*pday;    /* Planette geçen gün  */



	printf("If you lived in a planet where a day is %d hours, ",phour);
	printf("a month is %d days and a year is %d months:",pday,pmonth);
	printf(" you were %d years, %d months and %d days old\n",s3,s5,s6);


	return 0;

}
