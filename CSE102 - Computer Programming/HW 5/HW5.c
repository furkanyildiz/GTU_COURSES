/* -----------------------------------------------------------------------    */ 
/*                                                                            */ 
/* HW04_141044031_FÜRKAN_YILDIZ 		                                      */
/*                                                                            */ 
/* main.c                                                                     */ 
/* -----------------------------------------------------------------------    */ 
/* Created on 04/04/2016 by FÜRKAN YILDIZ                                     */ 
/*                                                                            */ 
/* Description                                                                */ 
/* -----------------------------------------------------------------------    */
/* The 5. Homework is a chess simulator that performs basic operations        */
/* in a game.We have an 8x8 board ofwhich the columns and rows are represented*/
/* by characters and integers.We di use lowercase and uppercase letters for   */ 
/* the black and white users, respectively. 								  */
/* You will store the board in a character array of size 64 and perform all   */
/* of the operations using pointers. The three main operations that can be    */
/* performed in this stage of the game are 1) Initializing theboard by placing*/
/* piece the pieces in the correct order for both users, 2) ChecisKingMovable */
/* whether he can move from its position to a specified cell			      */
/* 3) Displaying the board 4) Exit.											  */
/*----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                                 Includes 			                     */
/*---------------------------------------------------------------------------*/
#include <stdio.h>

/*---------------------------------------------------------------------------*/
/*                                 Defines	 			                     */
/*---------------------------------------------------------------------------*/
#define ROW 8
#define COLUMN 8
#define SIZE 64
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void initBoard(char *board)	        									 */
/*	*board  - Tek boyutlu array parametresi			   				  		 */
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon,satranç kurallarına göre, taşları satrancın başlangıç       */ 
/*  konumundaki, yerlerine getirerek, tek boyutlu arrayimizi dolduracak.     */ 
/*                                                            		     	 */  
/*---------------------------------------------------------------------------*/
void initBoard(char *board);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void getPosition(char *col, int *row)        							 */
/*	*col  - Arrayin satranç tahtasına göre sütün değeri		   				 */
/*	*row  - Arrayin satranç tahsatına göre satır değeri			   			 */
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, satranç tahtasına göre, satır ve sütün değerlerini alacak  */
/*  Örneğin, satranç tahsatına göre "a2" yazınca a. sütün 2. satıra gidecek. */ 
/*---------------------------------------------------------------------------*/
void getPosition(char *col, int *row);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* int isValidCell(char col, int row)        								 */
/*	*col  - Arrayin satranç tahtasına göre sütün değeri		   				 */
/*	*row  - Arrayin satranç tahsatına göre satır değeri			   			 */
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, verilen hücrenin, satranç tahtasına göre geçerli olup	     */ 
/*  olmadığını kontrol edecek. Geçerliyse 1, değilse 0 return edecek.        */
/*  Örneğin "a2" gibi bir değer yollanınca, geçerli olduğundan 1, "k9"       */ 
/*  gibi bir değer basılınca ise geçersiz olduğundan 0 return edilecek.      */     
/*---------------------------------------------------------------------------*/
int isValidCell(char col, int row);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void printBoard(char *board)	        									 */
/*	*board  - Tek boyutlu array parametresi			   				  		 */
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon,satranç tahtasının anlık durumunu ekrana basacak. 		     */ 
/*                                                            		     	 */  
/*---------------------------------------------------------------------------*/
void printBoard(char *board);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* int isPieceMovable(char *board)	        								 */
/*	*board  - Tek boyutlu array parametresi			   				  		 */
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, kullanıcıya, source ve target pozisyonlarını soracak,      */
/*  sourcede bulunan taşın kurallarına göre, target pozisyona gidip 		 */  
/*  gidemiyeceğini kontrol edecek. Gidebiliyorsa 1, gidemiyorsa 0 return   	 */
/*  edecek.																   	 */  
/*---------------------------------------------------------------------------*/
int isPieceMovable(char *board);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* void FindIndexInArray(char sourceCol, int sourceRow, char targetCol,      */
/* int targetRow, int *index1, int *index2)									 */
/*	sourceCol  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  sütünda bulunduğunu belirten değişken.						   			 */
/*	sourceRow  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  satırda bulunduğunu belirten değişken.						   			 */
/*	targetCol  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi sütünda bulunduğunu belirten değişken.				     	 */
/*	targetRow  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi satırda bulunduğunu belirten değişken.				     	 */
/*	*index1    - Oynatmak istediğimiz taşın, satranç tahtasındaki satır      */
/*  sütün değerlerinden, arrayde nerede (hangi indexte) bulunduğunu belirten */
/*  değişken. Örneğin "a2", arrayde 48.indexe denk.		 					 */
/*	*index2    - Oynatmak istediğimiz taşın, gideceği yerin,   				 */
/*  satranç tahtasındaki satır sütün değerlerinden, arrayde nerede    		 */
/*  (hangi indexte)  bulunduğunu belirtendeğişken. Örneğin "a2", arrayde 	 */
/*  48.indexe denk.		 					 								 */
/* -----------								     							 */   
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, işlem yapılmak için girilen satır ve sütün değerlerini     */ 
/*  arrayde işlem yapabilmek için, index'e çeviriyor. Bu indexe çevirme      */
/*  işlemini, hem oynamak istediğimiz taşın bulunduğu yer, hemde 		     */ 
/*  oynayacağımız yer için gerçekleştiriyor ve işlemlerimize bu indexlerle	 */
/*  gerçekleştiriyoruz.														 */          
/*---------------------------------------------------------------------------*/
void FindIndexInArray(char sourceCol, int sourceRow, char targetCol,
 					  int targetRow, int *index1, int *index2);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* int isKnightMovable(char *board, char sourceCol, int sourceRow, 			 */
/* char targetCol, int targetRow)  									     	 */
/*	board      -Tek boyutlu array parametresi						         */
/*	sourceCol  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  sütünda bulunduğunu belirten değişken.						   			 */
/*	sourceRow  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  satırda bulunduğunu belirten değişken.						   			 */
/*	targetCol  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi sütünda bulunduğunu belirten değişken.				     	 */
/*	targetRow  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi satırda bulunduğunu belirten değişken.				     	 */
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, oyunun kurallarına göre, At'ın kaynak hücreden, istenilen  */ 
/*  hücreye gidip gidemeyeceğini kontrol edecek. Eğer gidiyorsa 1, 			 */
/*  gidemiyorsa 0, return edecek.   										 */         
/*---------------------------------------------------------------------------*/
int isKnightMovable(char *board, char sourceCol, int sourceRow, 
					char targetCol, int targetRow);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* int isRookMovable(char *board, char sourceCol, int sourceRow, 			 */
/* char targetCol, int targetRow)  									   	 	 */
/*	board      -Tek boyutlu array parametresi						         */
/*	sourceCol  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  sütünda bulunduğunu belirten değişken.						   			 */
/*	sourceRow  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  satırda bulunduğunu belirten değişken.						   			 */
/*	targetCol  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi sütünda bulunduğunu belirten değişken.				     	 */
/*	targetRow  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi satırda bulunduğunu belirten değişken.				     	 */
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, oyunun kurallarına göre, Kale'nin kaynak hücreden,istenilen*/ 
/*  hücreye gidip gidemeyeceğini kontrol edecek. Eğer gidiyorsa 1, 			 */
/*  gidemiyorsa 0, return edecek.   										 */         
/*---------------------------------------------------------------------------*/
int isRookMovable(char *board , char sourceCol, 
				  int sourceRow, char targetCol, int targetRow);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* int isBishopMovable(char *board, char sourceCol, int sourceRow, 			 */
/* char targetCol, int targetRow)  									   	 	 */
/*	board      -Tek boyutlu array parametresi						         */
/*	sourceCol  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  sütünda bulunduğunu belirten değişken.						   			 */
/*	sourceRow  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  satırda bulunduğunu belirten değişken.						   			 */
/*	targetCol  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi sütünda bulunduğunu belirten değişken.				     	 */
/*	targetRow  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi satırda bulunduğunu belirten değişken.				     	 */
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, oyunun kurallarına göre, Fil'in kaynak hücreden,istenilen  */ 
/*  hücreye gidip gidemeyeceğini kontrol edecek. Eğer gidiyorsa 1, 			 */
/*  gidemiyorsa 0, return edecek.   										 */         
/*---------------------------------------------------------------------------*/
int isBishopMovable (char *board, char sourceCol, 
					 int sourceRow, char targetCol, int targetRow);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* int isQueenMovable(char *board, char sourceCol, int sourceRow, 			 */
/* char targetCol, int targetRow)  									   	 	 */
/*	board      -Tek boyutlu array parametresi						         */
/*	sourceCol  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  sütünda bulunduğunu belirten değişken.						   			 */
/*	sourceRow  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  satırda bulunduğunu belirten değişken.						   			 */
/*	targetCol  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi sütünda bulunduğunu belirten değişken.				     	 */
/*	targetRow  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi satırda bulunduğunu belirten değişken.				     	 */
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, oyunun kurallarına göre, Vezir'in kaynak hücreden,istenilen*/ 
/*  hücreye gidip gidemeyeceğini kontrol edecek. Eğer gidiyorsa 1, 			 */
/*  gidemiyorsa 0, return edecek.   										 */         
/*---------------------------------------------------------------------------*/
int isQueenMovable(char *board, char sourceCol, 
				   int sourceRow, char targetCol, int targetRow);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* int isKingMovable(char *board, char sourceCol, int sourceRow, 			 */
/* char targetCol, int targetRow)  									   	 	 */
/*	board      -Tek boyutlu array parametresi						         */
/*	sourceCol  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  sütünda bulunduğunu belirten değişken.						   			 */
/*	sourceRow  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  satırda bulunduğunu belirten değişken.						   			 */
/*	targetCol  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi sütünda bulunduğunu belirten değişken.				     	 */
/*	targetRow  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi satırda bulunduğunu belirten değişken.				     	 */
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, oyunun kurallarına göre, Şah'ın kaynak hücreden,istenilen  */ 
/*  hücreye gidip gidemeyeceğini kontrol edecek. Eğer gidiyorsa 1, 			 */
/*  gidemiyorsa 0, return edecek.   										 */         
/*---------------------------------------------------------------------------*/
int isKingMovable(char *board , char sourceCol, 
				  int sourceRow, char targetCol, int targetRow);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* int isPawnMovable(char *board, char sourceCol, int sourceRow, 			 */
/* char targetCol, int targetRow)  									   	 	 */
/*	board      -Tek boyutlu array parametresi						         */
/*	sourceCol  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  sütünda bulunduğunu belirten değişken.						   			 */
/*	sourceRow  - Oynatmak istediğimiz taşın, satranç tahtasına göre hangi    */
/*  satırda bulunduğunu belirten değişken.						   			 */
/*	targetCol  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi sütünda bulunduğunu belirten değişken.				     	 */
/*	targetRow  - Oynatmak istediğimiz taşın gideceği yerin, satranç tahtasına*/ 
/*  göre hangi satırda bulunduğunu belirten değişken.				     	 */
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, oyunun kurallarına göre, Piyon'un kaynak hücreden,istenilen*/ 
/*  hücreye gidip gidemeyeceğini kontrol edecek. Eğer gidiyorsa 1, 			 */
/*  gidemiyorsa 0, return edecek.   										 */         
/*---------------------------------------------------------------------------*/
int isPawnMovable (char *board, char sourceCol, 
				   int sourceRow, char targetCol, int targetRow);
/*---------------------------------------------------------------------------*/ 
/*                         Function Prototypes 				   				 */ 
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/ 
/*                                                              	   		 */ 
/* 	void emptyBuffer() 														 */
/* -----------								     							 */ 
/* Description                                                               */ 
/* -----------								     							 */ 
/*  Bu fonksiyon, Bufferi boşaltacak.									     */ 
/*---------------------------------------------------------------------------*/

void emptyBuffer()
{
	while ( getchar() != '\n' );
}	
int main()
{
	char board [64];
	int initComplete = 0;
	char empty;

	int command;
	scanf("%d", &command);

	while(command!=4)
	{
		switch(command)
		{
			case 1: initBoard(board); 
				initComplete = 1; 
				printf("OK\n");
				break;
			case 2: 
				/*Read space character after command number*/
				scanf("%c", &empty);
				if (initComplete)
				{
					if(isPieceMovable(board))
						printf("YES\n");
					else
						printf("NO\n");
				}
				else
				{  
					printf("Board is not initialized!\n");
					emptyBuffer();
				}
				break;
			case 3: 
				if (initComplete)
					printBoard(board);
				else  
					printf("Board is not initialized!\n");
					emptyBuffer();
				break;

			default: printf("Invalid command!\n"); emptyBuffer(); break;

		}	
		
		scanf("%d", &command);
	
	}
	return 0;
}

/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function initBoard 							    						 */
/* -----------																 */
/*  Bu fonksiyon, satranç tahtasına göre, satır ve sütün değerlerini alacak  */
/*  Örneğin, satranç tahsatına göre "a2" yazınca a. sütün 2. satıra gidecek. */ 
/*---------------------------------------------------------------------------*/
void initBoard(char *board){
/* For döngüsü için atanan değişkenler 	*/
	int i,k,l;

	board[0]='r';
	board[1]='n';
	board[2]='b';
	board[3]='q';
	board[4]='k';		
	board[5]='b';
	board[6]='n';
	board[7]='r';
	for(i=8; i<=15; i++){
		board[i]='p';
	}
	
	for(k=16; k<=47; k++){
		board[k]=' ';
	}
	for(l=48; l<=55; l++){
		board[l]='P';
	}
	
	
	board[56]='R';
	board[57]='N';
	board[58]='B';
	board[59]='Q';
	board[60]='K';		
	board[61]='B';
	board[62]='N';
	board[63]='R';
	
	
	board[16]='P';
	board[26]='n';
	board[31]='k';
	board[37]='b';
	board[34]='q';
	board[33]='r';
	board[43]='Q';
	board[37]='b';
	board[44]='p';
	board[46]='N';
	board[32]='B';
	board[39]='N';
		board[25]='P';
}

/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function getPosition 							    				     */
/* -----------																 */
/*  Bu fonksiyon, satranç tahtasına göre, satır ve sütün değerlerini alacak  */
/*  Örneğin, satranç tahsatına göre "a2" yazınca a. sütün 2. satıra gidecek. */ 
/*---------------------------------------------------------------------------*/
void getPosition(char *col, int *row){
	scanf("%c %d",col,row);
}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function isValidCell 							    				     */
/* -----------																 */
/*  Bu fonksiyon, verilen hücrenin, satranç tahtasına göre geçerli olup	     */ 
/*  olmadığını kontrol edecek. Geçerliyse 1, değilse 0 return edecek.        */
/*  Örneğin "a2" gibi bir değer yollanınca, geçerli olduğundan 1, "k9"       */ 
/*  gibi bir değer basılınca ise geçersiz olduğundan 0 return edilecek.      */     
/*---------------------------------------------------------------------------*/
int isValidCell(char col, int row){

	if((col>='a' && col<='h') && (row<9 && row>0))
	{
		return 1;
	}
	return 0;

}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function printBoard 							    					     */
/* -----------																 */
/*  Bu fonksiyon,satranç tahtasının anlık durumunu ekrana basacak. 		     */ 
/*---------------------------------------------------------------------------*/
void printBoard(char *board){
	int i;
	
	/* ROW'un değerini atadığımız değişken, farklı değişkene atıyoruz çünkü
	değeri, print ederken değiştirmeliyiz. */
	int rowsize;
	
	
	
	printf("  a b c d e f g h\n");
	printf("  - - - - - - - -\n");
	
	rowsize=ROW;
	for(i=0; i<SIZE; i++){
		if(i%ROW==0){
			printf("%d|",rowsize);
		}
		if(i%ROW!=7)
			printf("%c ",board[i]);
		else if(i%ROW==7){
			printf("%c",board[i]);
		}
		if (i%COLUMN == COLUMN -1){

			printf("| \n");
			rowsize-=1;
		}

	}
	printf("  - - - - - - - -\n");

}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function FindIndexInArray 							    			 	 */
/* -----------																 */
/*  Bu fonksiyon, işlem yapılmak için girilen satır ve sütün değerlerini     */ 
/*  arrayde işlem yapabilmek için, index'e çeviriyor. Bu indexe çevirme      */
/*  işlemini, hem oynamak istediğimiz taşın bulunduğu yer, hemde 		     */ 
/*  oynayacağımız yer için gerçekleştiriyor ve işlemlerimize bu indexlerle	 */
/*  gerçekleştiriyoruz.														 */          
/*---------------------------------------------------------------------------*/
void FindIndexInArray(char sourceCol, int sourceRow, char targetCol, 
					  int targetRow, int *index1, int *index2){
	
		int sc,tc;
/* Satranç tablosundaki rowlarda, a nın değeri 0, b'nin değeri 1, 
c nin değeri 2,  ...  h'nin değeri 7 olmalı, bunu sağlamak için girilen harfi 
ASCII integerine çevirip, a'nın değeri olan ASCII integerinden çıkartıyoruz. 
Yani burada a, sıfır numaramız, başlangıc noktamız. 						 */
	
	sc=(int)sourceCol-'a';
	tc=(int)targetCol - 'a';
	
	/*Sourcerow'un arrayde hangi index'i belirttiğini gösterecek. */
	*index1= (ROW-sourceRow)*COLUMN+sc;
	/* Targetrow'un arrayde hangi index'i belirttiğini gösterecek.*/
	*index2= (ROW-targetRow)*COLUMN+tc;
	
}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function isPieceMovable	 							    			 	 */
/* -----------																 */
/*  Bu fonksiyon, kullanıcıya, source ve target pozisyonlarını soracak,      */
/*  sourcede bulunan taşın kurallarına göre, target pozisyona gidip 		 */  
/*  gidemiyeceğini kontrol edecek. Gidebiliyorsa 1, gidemiyorsa 0 return   	 */
/*  edecek.																   	 */  
/*---------------------------------------------------------------------------*/
int isPieceMovable(char *board){
	/* Satranç tahtasındaki hareket ettirmek istediğimiz taşın sütünu*/
	char sourceCol;
	/* Satranç tahtasındaki taşı hareket ettirmek istediğimiz yerin sütünu*/
	char targetCol;
	/* Kaynak hücre den sonra target hücre girilirken araya koyulan boşluğun
	işleme katılmasını engellemek için, scanfle aldığımız değişken. */
	char forSpace;
	/* Satranç tahtasındaki hareket ettirmek istediğimiz taşın satırı*/
	int  sourceRow;
	/* Satranç tahtasındaki taşı hareket ettirmek istediğimiz yerin satırı*/
	int targetRow;
/* Hareket etmek istediğimiz yerin ve hareket ettireceğimiz yerin satranç 
tahtasına göre geçerli adresler olup olmadığını kontrol etecek değişkenler.  */
	int m,n;
	/* Hareket edeceğimiz yerin indexi*/
	int index1;
	/* Hareket etmek istedğimiz yerin indexi*/
	int index2;
	/* Kontrol değişkeni, eğer fonksiyonlardan 1, return değeri gelirse 1,
	0 return değeri gelirse 0 return edecek.*/
	int controller;
	getPosition(&sourceCol, &sourceRow);
	scanf("%c",&forSpace);
	getPosition(&targetCol, &targetRow);
/* Hareket etmek istediğimiz yerin ve hareket ettireceğimiz yerin satranç 
tahtasına göre geçerli adresler olup olmadıüını kontrol etecek, eğer ikiside
geçerliyse, gerekli işlemler yapılacak, herhangi biri bile geçersizse, direk 
return 0 edilecek.														*/
	m=isValidCell(sourceCol,sourceRow);
	n=isValidCell(targetCol,targetRow);

	if (m==1 && n==1){
	
		FindIndexInArray(sourceCol, sourceRow,targetCol, targetRow,
															   &index1,&index2);
	
	/* OYNAMAK İSTEDİĞİMİZ TAŞ BOŞSSA */
		if(board[index1]==' '){
			return 0;
		}	
	
	/*KÜÇÜK HARFLİ TAŞLARIN SAHİBİ OYUNCU İÇİN: */
		else if(board[index1]=='r' || board[index1]=='n' || board[index1]== 'b' 
		|| board[index1]=='q' || board[index1]=='k' || board[index1]=='p'){
			/* Gideceği yerde kendi elemanı varsa oynayamaz, 0 return eder */
			if(board[index2]=='r' || board[index2]=='n' || board[index2]=='b' 
			|| board[index2]=='q' || board[index2]=='k' || board[index2]=='p'){
				return 0;
		
			}
			/*Gideceği yerde rakip taşı varsa */
			else if(board[index2]=='R' || board[index2]=='N' || 
					board[index2]=='B' || board[index2]=='Q' || 
					board[index2]=='K' || board[index2]=='P'){
		
				if(board[index1]=='n'){
					controller=isKnightMovable(board,sourceCol,
												sourceRow,targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='r'){
					controller=isRookMovable(board,sourceCol,sourceRow,
											 targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='b'){
					controller=isBishopMovable(board,sourceCol,sourceRow,
											   targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='q'){
					controller=isQueenMovable(board,sourceCol,sourceRow,
											  targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
			
				else if(board[index1]=='k'){
					controller=isKingMovable(board,sourceCol,sourceRow,
											 targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
			
				else if(board[index1]=='p'){
					controller=isPawnMovable(board,sourceCol,sourceRow,
											 targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
			
			
					return 0;
			
			
			}
			/*gideceği yer boşsa */
			else{
					controller=0;

				if(board[index1]=='n'){
					controller=isKnightMovable(board,sourceCol,
											   sourceRow,targetCol, targetRow);
					if(controller==0) 
						return 0;
					else 
						return 1;	
				}
				if(board[index1]=='r'){
					controller=isRookMovable(board,sourceCol,
											 sourceRow,targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='b'){
					controller=isBishopMovable(board,sourceCol,sourceRow,
												targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='q'){
					controller=isQueenMovable(board,sourceCol,sourceRow,
											  targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='k'){
					controller=isKingMovable(board,sourceCol,sourceRow,
											 targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='p'){
					controller=isPawnMovable(board,sourceCol,sourceRow,
											 targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
			}
			return 0;
		}


	/*BÜYÜK HARFLİ TAŞLARIN SAHİBİ OYUNCU İÇİN */
		else if(board[index1]=='R' || board[index1]=='N' || 
				board[index1]== 'B'|| board[index1]=='Q' || 
				board[index1]=='K' || board[index1]=='P'){

			/* Gideceği yerde kendi elemanı varsa oynayamaz, 0 return eder */
			if( board[index2]=='R' || board[index2]=='N' || 
				board[index2]=='B' || board[index2]=='Q' || 
				board[index2]=='K' || board[index2]=='P'){
				return 0;
		
			}
			/*Gideceği yerde rakip taşı varsa */
		
			else if(board[index2]=='r' || board[index2]=='n' || 
					board[index2]=='b' || board[index2]=='q' || 
					board[index2]=='k' || board[index2]=='p'){

				if(board[index1]=='N'){
					controller=isKnightMovable(board,sourceCol,sourceRow,
														targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;	
		
				}
				else if(board[index1]=='R'){
					controller=isRookMovable(board,sourceCol,sourceRow,
														targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='B'){
					controller=isBishopMovable(board,sourceCol,sourceRow,
														targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='Q'){
					controller=isQueenMovable(board,sourceCol,sourceRow,
														targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='K'){
					controller=isKingMovable(board,sourceCol,sourceRow,
														targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='P'){
					controller=isPawnMovable(board,sourceCol,sourceRow,
														targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
			}
			/*gideceği yer boşsa */
			else{
				if(board[index1]=='N'){
					controller=isKnightMovable(board,sourceCol,sourceRow,
														targetCol, targetRow);
				
					if(controller==0)
						return 0;
					else 
						return 1;	
		
				}
				else if(board[index1]=='R'){
					controller=isRookMovable(board,sourceCol,sourceRow,
														targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='B'){
					controller=isBishopMovable(board,sourceCol,sourceRow,
														targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='Q'){
					controller=isQueenMovable(board,sourceCol,sourceRow,
														targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='K'){
					controller=isKingMovable(board,sourceCol,sourceRow,
														targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='P'){
					controller=isPawnMovable(board,sourceCol,sourceRow,
														targetCol, targetRow);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
		
		
			}
	
		}
	}
		return 0;
}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function isKnightMovable 							    			 	 */
/*  Bu fonksiyon, oyunun kurallarına göre, Kale'nin kaynak hücreden,istenilen*/ 
/*  hücreye gidip gidemeyeceğini kontrol edecek. Eğer gidiyorsa 1, 			 */
/*  gidemiyorsa 0, return edecek.   										 */         
/*---------------------------------------------------------------------------*/

int isKnightMovable(char *board, char sourceCol, int sourceRow, 
					char targetCol, int targetRow){
	
	int index1,index2;
	
	FindIndexInArray(sourceCol, sourceRow,targetCol, targetRow,&index1,&index2);

	if(sourceCol>='c' && sourceCol<='f' && sourceRow<=6 && sourceRow>=3)
	{
		if(index2==index1+ROW*1+2 || index2==index1+ROW*1-2 || 
		   index2==index1-ROW*2+1 || index2==index1+ROW*2-1 || 
		   index2==index1-ROW*1+2 || index2==index1-ROW*1-2 || 
		   index2==index1+ROW*2+1 || index2==index1-ROW*2-1)

			return 1;
		else
			return 0;
	}
	
/* Oynatacağımız at "a" sutununda ise */
	else if(sourceCol=='a'){
		
		if(sourceRow<=6 && sourceRow>=3){
			if(index2==index1+ROW*1+2 || index2==index1+ROW*2+1 || 
			   index2==index1-ROW*1+2 || index2==index1+ROW*2+1)
				return 1;
			else
				return 0;
		
		}
		else if (sourceRow==8){
			if(index2==index1+ROW*1+2 || index2==index1+ROW*2+1)
				return 1;
			else
				return 0;
		
		
		}
		else if(sourceRow==7){
			if(index2==index1+ROW*1+2 || index2==index1+ROW*2+1 || 
			   index2==index1-ROW*1+2)
				return 1;
			else
				return 0;
		
		
		}
		else if(sourceRow==2){
			if(index2==index1+ROW*1+2 || index2==index1-ROW*1+2 || 
			   index2==index1+ROW*2+1)
				return 1;
			else
				return 0;
		
		}
		else if(sourceRow==1){
			if(index2==index1-ROW*1+2 || index2==index1-ROW*2+1)
				return 1;
			else
				return 0;
		
		
		}
	
	
	}
	/* Oynatacağımız at "b" sütünunda ise*/
	else if (sourceCol=='b'){
		if(sourceRow<=6 && sourceRow>=3){
			if(index2==index1+ROW*1+2 || index2==index1+ROW*2+1 || 
			   index2==index1+ROW*2-1 || index2==index1-ROW*1+2 ||  
			   index2==index1-ROW*2+1 || index2==index1+ROW*2-1)
				return 1;
			else
				return 0;
		
		}
		else if (sourceRow==8){
			if(index2==index1+ROW*1+2 || index2==index1+ROW*2+1 || 
			   index2==index1+ROW*2-1)
				return 1;
			else
				return 0;
		
		
		}
		else if(sourceRow==7){
			if(index2==index1+ROW*1+2 || index2==index1+ROW*2+1 || 
			   index2==index1+ROW*2-1 || index2==index1-ROW*1+2)
				return 1;
			else
				return 0;
		
		
		}
		else if(sourceRow==2){
			if(index2==index1+ROW*1+2 || index2==index1-ROW*1+2 || 
			   index2==index1+ROW*2+1|| index2==index1+ROW*2-1)
				return 1;
			else
				return 0;
		
		}
		else if(sourceRow==1){
			if(index2==index1-ROW*1+2 || index2==index1-ROW*2+1|| 
			   index2==index1-ROW*2-1)
				return 1;
			else
				return 0;
		
		
		}
	}
/* Atı oynatacağımız sütün "g" ise */
	else if (sourceCol=='g'){
		if(sourceRow<=6 && sourceRow>=3){
			if( index2==index1+ROW*1-2 || index2==index1+ROW*2+1 || 
				index2==index1+ROW*2-1 || index2==index1-ROW*1-2 || 
				index2==index1+ROW*2+1 || index2==index1+ROW*2-1)
				return 1;
			else
				return 0;
		
		}
		else if (sourceRow==8){
			if(index2==index1+ROW*1-2 || index2==index1+ROW*2+1 || 
			   index2==index1+ROW*2-1)
				return 1;
			else
				return 0;
		
		
		}
		else if(sourceRow==7){
			if(index2==index1+ROW*1-2 || index2==index1+ROW*2+1 || 
			   index2==index1+ROW*2-1 || index2==index1-ROW*1-2)
				return 1;
			else
				return 0;
		
		
		}
		else if(sourceRow==2){
			if(index2==index1+ROW*1-2|| index2==index1-ROW*1-2 || 
			   index2==index1+ROW*2+1 || index2==index1+ROW*2-1)
				return 1;
			else
				return 0;
		
		}
		else if(sourceRow==1){
			if(index2==index1-ROW*1-2 || index2==index1-ROW*2+1 ||
    		   index2==index1-ROW*2-1)
				return 1;
			else
				return 0;
		
		
		}
	
	
	
	
	}
/*Atı oynatacağımız sütün "h" ise */ 
	else if (sourceCol=='h'){
		if(sourceRow<=6 && sourceRow>=3){
			if( index2==index1+ROW*1-2 || index2==index1+ROW*2+1  || 
				index2==index1+ROW*2-1 ||  index2==index1-ROW*1-2 || 
				index2==index1+ROW*2+1 || index2==index1+ROW*2-1)
				return 1;
			else
				return 0;
		
		}
		else if (sourceRow==8){
			if(index2==index1+ROW*1-2 || index2==index1+ROW*2-1)
				return 1;
			else
				return 0;
		
		
		}
		else if(sourceRow==7){
			if(index2==index1+ROW*1-2 || index2==index1+ROW*2+1 || 
			   index2==index1-ROW*1-2)
				return 1;
			else
				return 0;
		
		
		}
		else if(sourceRow==2){
			if(index2==index1+ROW*1-2 || index2==index1-ROW*1-2 || 
			   index2==index1+ROW*2-1)
				return 1;
			else
				return 0;
		
		}
		else if(sourceRow==1){
			if(index2==index1-ROW*1-2 || index2==index1-ROW*2-1)
				return 1;
			else
				return 0;
		
		
		}
	}
	return 0;
}


/********************************** KALE*******************************/
int isRookMovable(char *board , char sourceCol, int sourceRow, 
				  char targetCol, int targetRow){

	int index1,index2;
	
	int i;		
	
	FindIndexInArray(sourceCol, sourceRow,targetCol, targetRow,&index1,&index2);

	
/*KALEYİ KÜÇÜK TAŞLARA SAHİP OYUNUCU OYNACYAKSA*/
	if(board[index1]=='r' || board[index1]=='n' || board[index1]== 'b' || 
	   board[index1]=='q' || board[index1]=='k' || board[index1]=='p'){
		/*Kale sağa gitcekse */
		if(index2-index1>0 && index2-index1<=7){
			i=index1+1;
		/*i%ROW sıfıra eşit olduğunda alt satıra geçicek, onu engellemeliyiz */
			while(i<=index2 && i%ROW!=0){
		
				if(i<index2){
					if(board[i]== ' ')
						i++;
					else	
						return 0;
				}
				else if(i==index2){
					if(board[i]==' '  || board[i]=='R' || board[i]=='N' || 
					   board[i]== 'B' || board[i]=='Q' || board[i]=='K' || 
					   board[i]=='P')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
	
				}
			}
			return 0;
		}
		/*Kale sola gidecekse */
		else if(index1-index2>0 && index1-index2<=7){
			i=index1-1;
			/* "ROW-1" üst satıra geçmesin diye*/
			while(i>=index2 && (i%ROW)!=(ROW-1)){ 
				if(i>index2){
					if(board[i]== ' ')
						i--;
					else	
						return 0;
			
				}
				else if(i==index2){
					if(board[i]==' '  || board[i]=='R' || board[i]=='N' || 
					   board[i]== 'B' || board[i]=='Q' || board[i]=='K' || 
					   board[i]=='P')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
	
				}
	
			}
				return 0;
	
		}
		/* Kale yukarı gidekse */
		else if(index1>index2 && (index1-index2)%8==0){
			i=index1-ROW;

			while(i>=index2 && i>=0){
				if(i>index2){
					if(board[i]== ' ')
						i-=ROW;
					else	
						return 0;
				}
				else if(i==index2){
					if(board[i]==' '  || board[i]=='R' || board[i]=='N' || 
					   board[i]== 'B' || board[i]=='Q' || board[i]=='K' || 
					   board[i]=='P')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
	
			
				}
		
			}
			return 0;
		}
		/* Kale aşşağı gidekse */
		else if(index2>index1 && (index2-index1)%8==0){
			i=index1+ROW;
			/*Arrayın son elemanı 63 olduğundan 63 ü geçememeli */
			while(i<=index2 && i<=63){ 
				if(index2>i){
					if(board[i]== ' ')
						i+=ROW;
					else	
						return 0;
			
			
				}
				else if(i==index2){
					if(board[i]==' '  || board[i]=='R' || board[i]=='N' || 
					   board[i]== 'B' || board[i]=='Q' || board[i]=='K' || 
					   board[i]=='P')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
			
				}
			
			
			
			}
			return 0;
		}
		else
			return 0;
	
	
	
	
	}
	
/*************BÜYÜK TAŞLARA SAHİP OYUNCU OYNAYCAKSA**********/
	
	else if(board[index1]=='R' || board[index1]=='N' || board[index1]== 'B' || 
			board[index1]=='Q' || board[index1]=='K' || board[index1]=='P'){
	
	/*Kale sağa gitcekse */
		if(index2-index1>0 && index2-index1<=7){
			i=index1+1;
		/*i%ROW sıfıra eşit olduğunda alt satıra geçicek, onu engellemeliyiz */
			while(i<=index2 && i%ROW!=0){
		
				if(i<index2){
					if(board[i]== ' ')
						i++;
					else	
						return 0;
				}
				else if(i==index2){
					if(board[i]==' '  || board[i]=='r' || board[i]=='n' || 
					   board[i]== 'b' || board[i]=='q' || board[i]=='k' || 
					   board[i]=='p')
						return 1;
					else
						return 0;  /*y(gidilecek yerde) kendi taşı olabilir  */
	
				}
			
			}
			return 0;
		}
		/*Kale sola gidecekse */
		else if(index1-index2>0 && index1-index2<=7){
	
			i=index1-1;
			/* "ROW-1" üst satıra geçmesin diye*/
			while(i>=index2 && i%ROW!=ROW-1){ 
				if(i>index2){
					if(board[i]== ' ')
						i--;
					else	
						return 0;
			
				}
				else if(i==index2){
					if(board[i]==' ' ||  board[i]=='r' || board[i]=='n' || 
					   board[i]== 'b' || board[i]=='q' || board[i]=='k' || 
					   board[i]=='p')
						return 1;
					else
						return 0;  /*y(gidilecek yerde) kendi taşı olabilir  */
	
				}
	
			}
			return 0;
	
		}
		/* Kale yukarı gidekse */
		else if(index1>index2 && (index1-index2)%8==0){
			i=index1-ROW;
			while(i>=index2 && i>=0){
				if(i>index2){
					if(board[i]== ' ')
						i-=ROW;
					else	
						return 0;
				}
				else if(i==index2){
					if(board[i]==' ' ||  board[i]=='r' || board[i]=='n' || 
					   board[i]== 'b' || board[i]=='q' || board[i]=='k' || 
					   board[i]=='p')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
	
			
				}
		
			}
			return 0;
	
	
		}
		/* Kale aşşağı gidekse */
		else if(index2>index1 && (index2-index1)%8==0){
			i=index1+ROW;
			/*Arrayın son elemanı 63 olduğundan 63 ü geçememeli */
			if(index2>i){
				while(i<=index2 && i<=63){ 
					if(board[i]== ' ')
						i+=ROW;
					else	
						return 0;
			
			
				}
			}
			else if(i==index2){
				if(board[i]==' '  || board[i]=='r' || board[i]=='n' || 
				   board[i]== 'b' || board[i]=='q' || board[i]=='k' || 
				   board[i]=='p')
					return 1;
				else
					return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
			
			}		
		}
	}
			return 0;
}

/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function isBishopMovable 							    			 	 */
/*  Bu fonksiyon, oyunun kurallarına göre, Fil'in kaynak hücreden,istenilen  */ 
/*  hücreye gidip gidemeyeceğini kontrol edecek. Eğer gidiyorsa 1, 			 */
/*  gidemiyorsa 0, return edecek.   										 */         
/*---------------------------------------------------------------------------*/
int isBishopMovable (char *board, char sourceCol, int sourceRow, 
								  char targetCol, int targetRow){
	int index1,index2;
	
	int i;		
	
	FindIndexInArray(sourceCol, sourceRow,targetCol, targetRow,&index1,&index2);

/*******KÜÇÜK TAŞLARA SAHİP OYUNUCU OYNACYAKSA**************** */
	if(board[index1]=='r' || board[index1]=='n' || board[index1]== 'b' || 
	   board[index1]=='q' || board[index1]=='k' || board[index1]=='p'){
	
	/* Sağ üst çapraza gidekse fil*/
		if((index1-index2+1)%7==1){
			i=index1-(ROW-1);
			while(1){
			
	/* Gitmek istediği yerden önce çaprazlarda herhangi taş varsa,
	    gidemeyecek, istediği yere   */
				if(i>index2){
					if(board[i]==' ')
						i-=(ROW-1);
					else
						return 0;	
				}
				else if(i==index2){
					if(board[i]==' '  || board[i]=='R' || board[i]=='N' || 
					   board[i]== 'B' || board[i]=='Q' || board[i]=='K' || 
					   board[i]=='P')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
				
				}
			}
			return 0;
		}
		/* Sol üst çapraza gidecekse fil*/
		else if((index1-index2+1)%9==1){

			i=index1-(ROW+1);
			while(1){
			
	/* Gitmek istediği yerden önce çaprazlarda herhangi taş varsa, 
	   gidemeyecek, istediği yere*/
				if(i>index2){
					if(board[i]==' ')
						i-=(ROW+1);
					else
						return 0;	
				}
				else if(i==index2){

					if(board[i]==' '  || board[i]=='R' || board[i]=='N' || 
					   board[i]== 'B' || board[i]=='Q' || board[i]=='K' || 
					   board[i]=='P')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
				
				}

			}
			return 0;
		}
		/*Sağ alt çapraza gidecekse fil */
		else if((index2-index1)%9==0){
			i=index1+(ROW+1);
			while(1){
			
	/* Gitmek istediği yerden önce çaprazlarda herhangi taş varsa, 
	   gidemeyecek, istediği yere*/
				if(i<index2){
					if(board[i]==' ')
						i+=(ROW+1);
					else
						return 0;	
				}
				else if(i==index2){
					if(board[i]==' '  || board[i]=='R' || board[i]=='N' || 
					   board[i]== 'B' || board[i]=='Q' || board[i]=='K' || 
					   board[i]=='P')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
				
				}
			}
			return 0;
		}
		/*Sol alt çapraza gidecekse fil */
		else if((index2-index1)%7==0){

			i=index1+(ROW-1);
			while(1){
			
	/* Gitmek istediği yerden önce çaprazlarda herhangi taş varsa, 
	   gidemeyecek, istediği yere*/
				if(i<index2){
					if(board[i]==' ')
						i+=(ROW+-1);
					else
						return 0;	
				}
				else if(i==index2){
					if(board[i]==' '  || board[i]=='R' || board[i]=='N' || 
					   board[i]== 'B' || board[i]=='Q' || board[i]=='K' || 
					   board[i]=='P')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
				
				}
			}
			return 0;
		}

	}
/***** BÜYÜK HARFLERE SAHİP OYUNUCU OYNAYCASAKSA ****** */
	if(board[index1]=='R' || board[index1]=='N' || board[index1]== 'B' || 
	   board[index1]=='Q' || board[index1]=='K' || board[index1]=='P'){
	/* Sağ üst çapraza gidekse fil*/
		if((index1-index2+1)%7==1){
			i=index1-(ROW-1);
			while(1){
			
	/* Gitmek istediği yerden önce çaprazlarda herhangi taş varsa, 
	   gidemeyecek, istediği yere*/
				if(i>index2){
					if(board[i]==' ')
						i-=(ROW-1);
					else
						return 0;	
				}
				else if(i==index2){
					if(board[i]==' '  || board[i]=='r' || board[i]=='n' || 
					   board[i]== 'b' || board[i]=='q' || board[i]=='k' || 
					   board[i]=='p')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
				
				}
			}
			return 0;
		}
		


		/* Sol üst çapraza gidecekse fil*/
		else if((index1-index2+1)%9==1){
			i=index1-(ROW+1);
			while(1){
			
	/* Gitmek istediği yerden önce çaprazlarda herhangi taş varsa, 
	   gidemeyecek, istediği yere*/
				if(i>index2){
					if(board[i]==' ')
						i-=(ROW+1);
					else
						return 0;	
				}
				else if(i==index2){
					if(board[i]==' '  || board[i]=='r' || board[i]=='n' || 
					   board[i]== 'b' || board[i]=='q' || board[i]=='k' || 
					   board[i]=='p')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
				
				}
			}
			return 0;
		}
		/*Sağ alt çapraza gidecekse fil */
		else if((index2-index1)%9==0){
			i=index1+(ROW+1);
			while(1){
			
	/* Gitmek istediği yerden önce çaprazlarda herhangi taş varsa, 
	   gidemeyecek, istediği yere*/
				if(i<index2){
					if(board[i]==' ')
						i+=(ROW+1);
					else
						return 0;	
				}
				else if(i==index2){
					if(board[i]==' '  || board[i]=='r' || board[i]=='n' || 
					   board[i]== 'b' || board[i]=='q' || board[i]=='k' || 
					   board[i]=='p')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
				
				}
			}
			return 0;
		}
		/*Sol alt çapraza gidecekse fil */
		else if((index2-index1)%7==0){

			i=index1+(ROW-1);
			while(1){
			
	/* Gitmek istediği yerden önce çaprazlarda herhangi taş varsa, 
	   gidemeyecek, istediği yere*/
				if(i<index2){
					if(board[i]==' ')
						i+=(ROW+-1);
					else
						return 0;	
				}
				else if(i==index2){
					if(board[i]==' '  || board[i]=='r' || board[i]=='n' || 
					   board[i]=='b'  || board[i]=='q' || board[i]=='k' ||
					   board[i]=='p')
						return 1;
					else
						return 0;  /*(gidilecek yerde) kendi taşı olabilir  */
				
				}
			}
		return 0;
		}	
	}
		return 0;
}
/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function isQueenMovable	 							    			 	 */
/*  Bu fonksiyon, oyunun kurallarına göre, Vezir'in kaynak hücreden,istenilen*/ 
/*  hücreye gidip gidemeyeceğini kontrol edecek. Eğer gidiyorsa 1, 			 */
/*  gidemiyorsa 0, return edecek.   										 */         
/*---------------------------------------------------------------------------*/
int isQueenMovable(char *board, char sourceCol, int sourceRow, char targetCol, 
				                                               int targetRow){

	int index1,index2;
	
	FindIndexInArray(sourceCol, sourceRow,targetCol, targetRow,&index1,&index2);


	if(((index1-index2+1)%7==1) ||((index1-index2+1)%9==1) ||
         ((index2-index1)%9==0) || ((index2-index1)%7==0)){
		return isBishopMovable(board ,sourceCol,sourceRow,targetCol,targetRow);
	}
	else if((index2-index1>0 && index2-index1<=7)   ||
			(index1-index2>0 && index1-index2<=7)   || 
			(index1>index2 && (index1-index2)%8==0) ||
			(index2>index1 && (index2-index1)%8==0)){
			return isRookMovable(board,sourceCol,sourceRow,targetCol,targetRow);
	
	}
		return 0;
}

/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function isKingMovable	 							    			 	 */
/*  Bu fonksiyon, oyunun kurallarına göre, Şah'in kaynak hücreden,istenilen	 */ 
/*  hücreye gidip gidemeyeceğini kontrol edecek. Eğer gidiyorsa 1, 			 */
/*  gidemiyorsa 0, return edecek.   										 */         
/*---------------------------------------------------------------------------*/
int isKingMovable(char *board , char sourceCol, int sourceRow, char targetCol, 
															   int targetRow){

	int index1,index2;
	
	FindIndexInArray(sourceCol, sourceRow,targetCol,targetRow, &index1,&index2);
/* Küçük harflere sahip oyuncu şahı oynatacaksa */
	if(board[index1]=='k'){
		if((sourceCol>='b' && sourceCol<='g') &&(sourceRow>=2 && sourceRow<=7)){
			if((board[index2]==' ' || board[index2]=='R' || board[index2]=='N' 
				|| board[index2] =='B' || board[index2]== 'Q'  
				|| board[index2] =='K' || board[index2]== 'P') 
				&& (index2-index1== 1  || index2-index1==  7 
				|| index2-index1==  8  || index2-index1==  9 
				|| index2-index1== -1  || index2-index1== -9 
				|| index2-index1== -8  || index2-index1== -7)){
				return 1;}
			else
				return 0;
		}
		else if(sourceCol=='a'){
			if(index1==0){
					if((board[index2]==' '  || board[index2]=='R'  || 
						board[index2]=='N'  || board[index2]== 'B' || 
						board[index2]=='Q'  || board[index2]=='K'  || 
						board[index2]=='P') &&(index2-index1==1    || 
						index2-index1== 9   || index2-index1== 8 )) 
						return 1;
					else
						return 0;
			}
			else if(index1==56){
					if(((board[index2]==' '  || board[index2]== 'R' || 
						 board[index2]=='N'  || board[index2]== 'B' || 
						 board[index2]=='Q'  || board[index2]== 'K' || 
						 board[index2]=='P') &&(index2-index1==1 	|| 
						 index2-index1==-7   || index2-index1==-8 )))
						return 1;
					else
						return 0;
			}
			else{
					if((board[index2]==' '  || board[index2]=='R'  || 
						board[index2]=='N'  || board[index2]== 'B' || 
						board[index2]=='Q'  || board[index2]=='K'  || 
						board[index2]=='P') && (index2-index1==1   ||
						index2-index1== 9 	|| index2-index1== 8   || 
						index2-index1==-7   || index2-index1==-8 ))
						return 1;
					else
						return 0;
			}
	
		}
		else if(sourceCol=='h'){

			if(index1==7){
				if(((board[index2]==' '  || board[index2]=='R'  || 
					 board[index2]=='N'  || board[index2]=='B'	|| 
					 board[index2]=='Q'  || board[index2]=='K'  || 
					 board[index2]=='P') && (index2-index1==-1  || 
					 index2-index1==7    || index2-index1==8)))
					return 1;
				else
					return 0;
				}
			else if(index1==63){
				if((board[index2]==' '  || board[index2]=='R' 	|| 
					board[index2]=='N'  || board[index2]=='B'	|| 
					board[index2]=='Q'  || board[index2]=='K'   || 
					board[index2]=='P') &&(index2-index1==-1    || 
					index2-index1==-9   || index2-index1==-8))
					return 1;
				else
					return 0;
			}
					
			else{
				if((board[index2]==' '  || board[index2]=='R'   || 
					board[index2]=='N'  || board[index2]== 'B'  || 
				    board[index2]=='Q'  || board[index2]=='K'   || 
					board[index2]=='P') &&(index2-index1==-9    || 
					index2-index1==-8   || index2-index1==-1    || 
					index2-index1==7    || index2-index1==8))
					return 1;
				else
					return 0;
			}
		}
		else if(sourceRow==8 && sourceCol!='a' && sourceCol!= 'h'){
			if((board[index2]==' '  || board[index2]=='R' || 
				board[index2]=='N'  || board[index2]== 'B'|| 
				board[index2]=='Q'  || board[index2]=='K' || 
				board[index2]=='P') &&(index2-index1==1   || 
				index2-index1==-1   || index2-index1==8   || 
				index2-index1==7 	|| index2-index1==9))
				return 1;
			else
				return 0;
	
	
		}
		else if(sourceRow==1 && sourceCol!='a' && sourceCol!= 'h'){
			if((board[index2]==' '  || board[index2]=='R'   || 
				board[index2]=='N'  || board[index2]== 'B'  ||
				board[index2]=='Q'  || board[index2]=='K'   || 
				board[index2]=='P') && (index2-index1==-9   ||
				index2-index1==-7   || index2-index1==-8    || 
				index2-index1==-1   || index2-index1==1))
				return 1;
			else
				return 0;
		}
		return 0;
	}
	
	
/* Büyük harflere sahip oyuncu şahı oynatacaksa */
	if(board[index1]=='K'){
		if((sourceCol>='b' && sourceCol<='g')&& (sourceRow>=2 && sourceRow<=7)){
			if((board[index2]==' '  || board[index2]=='r'  || 
				board[index2]=='n'  || board[index2]== 'b' || 
				board[index2]=='q'  || board[index2]=='k'  || 
				board[index2]=='p') && (index2-index1==1   || 
				index2-index1== 7   || index2-index1== 8   || 
				index2-index1==9    || index2-index1== -1  || 
				index2-index1==-9   || index2-index1== -8  || 
				index2-index1== -7)){
				return 1;}
			else
				return 0;
		}
		else if(sourceCol=='a'){
			if(index1==0){
					if((board[index2]==' ' 	|| board[index2]=='r'  || 
						board[index2]=='n'  || board[index2]== 'b' || 
						board[index2]=='q'  || board[index2]=='k'  || 
						board[index2]=='p') &&(index2-index1==1    || 
						index2-index1== 9   || index2-index1== 8 )) 
						return 1;
					else
						return 0;
			}
			else if(index1==56){
					if((board[index2]==' '  || board[index2]=='r'  || 
						board[index2]=='n'  || board[index2]== 'b' || 
						board[index2]=='q'  || board[index2]=='k'  || 
						board[index2]=='p') &&(index2-index1==1    || 
						index2-index1==-7   || index2-index1==-8 ))
						return 1;
					else
						return 0;
			}
			else{
					if((board[index2]==' '  || board[index2]=='r'  || 
						board[index2]=='n'  || board[index2]== 'b' || 
						board[index2]=='q'  || board[index2]=='k'  || 
						board[index2]=='p') &&(index2-index1==1    || 
						index2-index1== 9   || index2-index1== 8   || 
						index2-index1==-7   || index2-index1==-8 ))
						return 1;
					else
						return 0;
			}
	
		}
		else if(sourceCol=='h'){

			if(index1==7){
				if(((board[index2]==' '  || board[index2]=='r'  || 
					 board[index2]=='n'  || board[index2]== 'b' || 
					 board[index2]=='q'  || board[index2]=='k'  || 
					 board[index2]=='p') && (index2-index1==-1  || 
					 index2-index1==7    || index2-index1==8)))
					return 1;
				else
					return 0;
				}
			else if(index1==63){
				if((board[index2]==' '  || board[index2]=='r'  || 
					board[index2]=='n'  || board[index2]== 'b' || 
					board[index2]=='q'  || board[index2]=='k'  || 
					board[index2]=='p') &&(index2-index1==-1   || 
					index2-index1==-9   || index2-index1==-8))
					return 1;
				else
					return 0;
			}
					
			else{
				if((board[index2]==' '  || board[index2]=='r' || 
				    board[index2]=='n'  || board[index2]== 'b'|| 
					board[index2]=='q'  || board[index2]=='k' || 
					board[index2]=='p') &&(index2-index1==-9  || 
					index2-index1==-8   || index2-index1==-1  || 
					index2-index1==7    || index2-index1==8))
					return 1;
				else
					return 0;
			}
		}
		else if(sourceRow==8 && sourceCol!='a' && sourceCol!= 'h'){
			if((board[index2]==' '  || board[index2]=='r'  || 
				board[index2]=='n'  || board[index2]== 'b' || 
				board[index2]=='q'  || board[index2]=='k'  || 
				board[index2]=='p') &&(index2-index1==1    || 
				index2-index1==-1   || index2-index1==8    || 
				index2-index1==7    || index2-index1==9))
				return 1;
			else
				return 0;
	
	
		}
		else if(sourceRow==1 && sourceCol!='a' && sourceCol!= 'h'){
			if((board[index2]==' '  || board[index2]=='r' || 
				board[index2]=='n'  || board[index2]== 'b'|| 
				board[index2]=='q'  || board[index2]=='k' || 
				board[index2]=='p') && (index2-index1==-9 || 
				index2-index1==-7   || index2-index1==-8  || 
				index2-index1==-1   || index2-index1==1))
				return 1;
			else
				return 0;
		}
	}
	return 0;
}
	

/*---------------------------------------------------------------------------*/
/*			Function Implementations			   						     */
/*---------------------------------------------------------------------------*/
/* Function isPawnMovable	 							    			 	 */
/*  Bu fonksiyon, oyunun kurallarına göre, Piyon'un kaynak hücreden,istenilen*/ 
/*  hücreye gidip gidemeyeceğini kontrol edecek. Eğer gidiyorsa 1, 			 */
/*  gidemiyorsa 0, return edecek.   										 */         
/*---------------------------------------------------------------------------*/

int isPawnMovable (char *board, char sourceCol, int sourceRow, char targetCol, 
															   int targetRow){

	int index1,index2;
	int i;
	
	FindIndexInArray(sourceCol, sourceRow,targetCol, targetRow,&index1,&index2);
	
	
/* Küçük harflere sahip oyuncu piyonu oynatacaksa */
	if(board[index1]=='r' || board[index1]=='n' || board[index1]== 'b' || 
	   board[index1]=='q' || board[index1]=='k' || board[index1]=='p'){
	
		i=index1+ROW;
		if(index2==i){
			if(board[i]==' ')
				return 1;
			else
				return 0;
		}
		else if(index2==i+1){
			if(board[i+1]=='R' || board[i+1]=='N' || board[i+1]== 'B' || 
			   board[i+1]=='Q' || board[i+1]=='K' || board[i+1]=='P')
				return 1;
			else
				return 0;
		}
		else if(index2==i-1){
			if(board[i-1]=='R' || board[i-1]=='N' || board[i-1]== 'B' || 
			   board[i-1]=='Q' || board[i-1]=='K' || board[i-1]=='P')
				return 1;
			else
				return 0;
		}
	}
/* Büyük harflere sahip oyuncu piyonu oynatacaksa */
	if(board[index1]=='R' || board[index1]=='N' || board[index1]=='B' || 
	   board[index1]=='Q' || board[index1]=='K' || board[index1]=='P'){

		i=index1-ROW;
		if(index2==i){
			if(board[i]==' ')
				return 1;
			else
				return 0;
		}
		else if(index2==i+1){
			if(board[i+1]=='r' || board[i+1]=='n' || board[i+1]== 'b' || 
			   board[i+1]=='q' || board[i+1]=='k' || board[i+1]=='p')
				return 1;
			else
				return 0;
		}
		else if(index2==i-1){
			if(board[i-1]=='r' || board[i-1]=='n' || board[i-1]== 'b' || 
			   board[i-1]=='q' || board[i-1]=='k' || board[i-1]=='p')
				return 1;
			else
				return 0;
		}	
	}
		return 0;
}
