#include <stdio.h>
#define BOARD_SIZE 8
#define ROW 8
#define COLUMN 8
void getPosition(char *col, int *row);
void printBoard(char *board);
int isValidCell(char col, int row);
int isPieceMovable(char *board, char sc, int sr, char tc, int tr);
int isInCheck(char* board);
int makeMove(char *board, char sc, int sr, char tc, int tr);
void FindIndexInArray(char sourceCol, int sourceRow, char targetCol,
 					  int targetRow, int *index1, int *index2);
void FindIndexInArray(char sourceCol, int sourceRow, char targetCol, 
					  int targetRow, int *index1, int *index2);
int isKnightMovable(char *board, char sourceCol, int sourceRow, 
					char targetCol, int targetRow);
int isRookMovable(char *board , char sourceCol, 
				  int sourceRow, char targetCol, int targetRow);
int isBishopMovable (char *board, char sourceCol, 
					 int sourceRow, char targetCol, int targetRow);
int isQueenMovable(char *board, char sourceCol, 
				   int sourceRow, char targetCol, int targetRow);
int isKingMovable(char *board , char sourceCol, 
				  int sourceRow, char targetCol, int targetRow);
int isPawnMovable (char *board, char sourceCol, 
				   int sourceRow, char targetCol, int targetRow);
void initBoard(char *board);		    
int isBlack(char currPlayer);
int isWhite(char currPlayer);
int getPlayer(char *board, char sc,int sr);
				   
int main() {
    char board [BOARD_SIZE*BOARD_SIZE], empty;
    int player = 1; /* 1 white, 0 black */
    char sc,tc; /* source/target cols */
    int sr,tr; /* source/target rows */
    int moveStatus = 0;
    int checkStatus = 0;
    char currPlayer;

	initBoard(board);

    do {
        printBoard(board);
        printf("%s player move > ", player ? "White" : "Black");
        getPosition(&sc,&sr);
        scanf("%c", &empty);
        getPosition(&tc,&tr);
        scanf("%c", &empty);
        currPlayer = getPlayer(board, sc,sr);

        if(!isValidCell(sc,sr)) {
            printf("Source position is invalid\n");
            continue;
        }
        if(!isValidCell(tc,tr)) {
            printf("Target position is invalid\n");
            continue;
        }
        if((isBlack(currPlayer) && player) ||
           (isWhite(currPlayer) && !player)) {
            printf("Illegal piece. \n");
            continue;
        }

        moveStatus = makeMove(board,sc,sr,tc,tr);
        switch(moveStatus) {
            case 0:
                printf("Invalid move!\n");
                break;
            case 1:
                printf("Your king is in check!\n");
                ++checkStatus;
                break;
            case 3:
                printf("Check!\n ");
            case 2:
                player = !player;
                checkStatus = 0;
                break;
        }
    } while(checkStatus < 2);
    printf("%s player WINS!\n", player ? "Black" : "White");
    return 0;
}
int isBlack(char currPlayer){
	if(currPlayer==0)
		return 1;
	return 0;
}
int isWhite(char currPlayer){
	if(currPlayer==1)
		return 1;
	return 0;
}
int getPlayer(char *board, char sc,int sr){
	char targetCol;
	int  targetRow;
	int index1,index2;
/*Aslında sadece index1(oynatmak istediğimiz taşın indexi, lazıma ama fonksiyonu
çağırabilemek için değer değişkenleride tanımlamalıyız. */
	FindIndexInArray(sc,sr,targetCol, targetRow,&index1,&index2);
	
	if(board[index1]<='z' && board[index1]>='a')
		return 0;
	else if(board[index1]<='Z' && board[index1]>='A')
		return 1;
	return 0;
}
void getPosition(char *col, int *row){
	scanf("%c %d",col,row);
}
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
}
void printBoard(char *board){

	int i;
	int rowsize;
	
	
	
	printf("  a b c d e f g h\n");
	printf("  - - - - - - - -\n");
	
	rowsize=ROW;
	for(i=0; i<BOARD_SIZE*BOARD_SIZE; i++){
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
int isValidCell(char col, int row){

	if((col>='a' && col<='h') && (row<9 && row>0))
	{
		return 1;
	}
	return 0;

}
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


int isInCheck(char* board){
	int index1,index2,i1;
	int Sol;
	int Sag;
	int Ust;
	int Alt;
	int SagAlt;
	int SolAlt;
	int SagUst;
	int SolUst;
	FindIndexInArray(sc, sr,tc, tr,&index1,&index2);

	printf("Bakalım ne vari1=%c   i2=%c ->%d ->%d",board[index1],board[index2],index1,index2);
	/*KÜÇÜK HARFLİ TAŞLARIN SAHİBİ OYUNCU İÇİN: */
	/* Siyah*/
	if(board[index1]=='k'){
		printf("ben küçük k\n");
		/*Sağ taraf kontrol */
		i1=index1;
		while(i1%8!=7 && board[i1+1]==' '){
			i1++;
		}
		if(i1%8==7) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			Sag= 0;
		else if(i1%8!=7){ 
			if(board[i1+1]>='a' && board[i1+1]>='z') /*Kendi taşı varsa */
				Sag= 0;
			else if(board[i1+1]>='A' && board[i1+1]>='Z') /*Rakip taşı varsa */
				Sag= 2; 
		}
		/*Sol taraf kontrol */
		i1=index1;
		while(i1%8!=0 && board[i1-1]==' '){
			i1--;
		}
		if(i1%8==0) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			Sol= 0;
		else if(i1%8!=0){
			if(board[i1-1]>='a' && board[i1-1]>='z') /*Kendi taşı varsa */
				Sol= 0;
			else if(board[i1-1]>='A' && board[i1-1]>='Z') /*Rakip taşı varsa */
				Sol= 2; 
		}
		/*Üst Düz Kontrol */
		i1=index1;
		while(i1-8>0 && board[i1-8]==' '){
			i1=i1-8;
		}
		if(i1<=7 && i1>=0) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			Ust= 0;
		else{
			if(board[i1-8]>='a' && board[i1-8]>='z') /*Kendi taşı varsa */
				Ust= 0;
			else if(board[i1-8]>='A' && board[i1-8]>='Z') /*Rakip taşı varsa */
				Ust= 2; 
		}
		/*Düz alt kontrol */
		i1=index1;
		while(i1+8>0 && board[i1+8]==' '){
			i1=i1+8;
		}
		if(i1<=63 && i1>=56) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			Alt= 0;
		else{
			if(board[i1+8]>='a' && board[i1+8]>='z') /*Kendi taşı varsa */
				Alt= 0;
			else if(board[i1+8]>='A' && board[i1+8]>='Z') /*Rakip taşı varsa */
				Alt= 2; 
		}
		/* Sağ üst çapraz Kontrol */
		i1=index1;
		while(i1-7>0 && board[i1-7]==' '){
			i1=i1-7;
		}
		if(i1<=7 && i1>=0) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			SagUst= 0;
		else{
			if(board[i1-7]>='a' && board[i1-7]>='z') /*Kendi taşı varsa */
				SagUst= 0;
			else if(board[i1-7]>='A' && board[i1-7]>='Z') /*Rakip taşı varsa */
				SagUst= 2; 
		}
		/*Sol üst çapraz Kontrol */
		i1=index1;
		while(i1-9>0 && board[i1-9]==' '){
			i1=i1-9;
		}
		if(i1<=7 && i1>=0) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			SolUst= 0;
		else{
			if(board[i1-9]>='a' && board[i1-9]>='z') /*Kendi taşı varsa */
				SolUst=  0;
			else if(board[i1-9]>='A' && board[i1-9]>='Z') /*Rakip taşı varsa */
				SolUst=  2; 
		}
		/*Sağ alt çapraz Kontrol */
		i1=index1;
		while(i1+9>0 && board[i1+9]==' '){
			i1=i1+9;
		}
		if(i1<=63 && i1>=56) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			SagAlt= 0;
		else{
			if(board[i1+9]>='a' && board[i1+9]>='z') /*Kendi taşı varsa */
				SagAlt= 0;
			else if(board[i1+9]>='A' && board[i1+9]>='Z') /*Rakip taşı varsa */
				SagAlt= 2; 
		}
		/*Sol alt çapraz Kontrol */
		i1=index1;
		while(i1+7<64 && board[i1+7]==' '){
			i1=i1+7;
		}
		if(i1<=63 && i1>=56) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			SolAlt= 0;
		else{
			if(board[i1+7]>='a' && board[i1+7]>='z') /*Kendi taşı varsa */
				SolAlt= 0;
			else if(board[i1+7]>='A' && board[i1+7]>='Z') /*Rakip taşı varsa */
				SolAlt= 2; 
		}
		printf("1\n");
		if(Sag==2 || Sol==2 || Ust==2 || Alt==2 || SagAlt==2 || 
		   SolAlt==2|| SagUst==2 || SolUst==2){
			printf("gir lan şuna\n");
			return 2;}
					printf("2\n");
	}
	/* BEYAZ OYUNCU*/
	if(board[index1]=='K'){
				printf("bende büyük K\n");
		/*Sağ taraf kontrol */
		i1=index1;
		while(i1%8!=7 && board[i1+1]==' '){
			i1++;
		}
		if(i1%8==7) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			Sag= 0;
		else if(i1%8!=7){ 
			if(board[i1+1]>='a' && board[i1+1]>='z') /*Kendi taşı varsa */
				Sag= 0;
			else if(board[i1+1]>='A' && board[i1+1]>='Z') /*Rakip taşı varsa */
				Sag= 1; 
		}
		/*Sol taraf kontrol */
		i1=index1;
		while(i1%8!=0 && board[i1-1]==' '){
			i1--;
		}
		if(i1%8==0) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			Sol= 0;
		else if(i1%8!=0){
			if(board[i1-1]>='a' && board[i1-1]>='z') /*Kendi taşı varsa */
				Sol= 0;
			else if(board[i1-1]>='A' && board[i1-1]>='Z') /*Rakip taşı varsa */
				Sol= 1; 
		}
		/*Üst Düz Kontrol */
		i1=index1;
		while(i1-8>0 && board[i1-8]==' '){
			i1=i1-8;
		}
		if(i1<=7 && i1>=0) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			Ust= 0;
		else{
			if(board[i1-8]>='a' && board[i1-8]>='z') /*Kendi taşı varsa */
				Ust= 0;
			else if(board[i1-8]>='A' && board[i1-8]>='Z') /*Rakip taşı varsa */
				Ust= 1; 
		}
		/*Düz alt kontrol */
		i1=index1;
		while(i1+8>0 && board[i1+8]==' '){
			i1=i1+8;
		}
		if(i1<=63 && i1>=56) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			Alt= 0;
		else{
			if(board[i1+8]>='a' && board[i1+8]>='z') /*Kendi taşı varsa */
				Alt= 0;
			else if(board[i1+8]>='A' && board[i1+8]>='Z') /*Rakip taşı varsa */
				Alt= 1; 
		}
		/* Sağ üst Kontrol */
		i1=index1;
		while(i1-7>0 && board[i1-7]==' '){
			i1=i1-7;
		}
		if(i1<=7 && i1>=0) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			SagUst= 0;
		else{
			if(board[i1-7]>='a' && board[i1-7]>='z') /*Kendi taşı varsa */
				SagUst= 0;
			else if(board[i1-7]>='A' && board[i1-7]>='Z') /*Rakip taşı varsa */
				SagUst= 1; 
		}
		/*Sol üst Kontrol */
		i1=index1;
		while(i1-9>0 && board[i1-9]==' '){
			i1=i1-9;
		}
		if(i1<=7 && i1>=0) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			SolUst= 0;
		else{
			if(board[i1-9]>='a' && board[i1-9]>='z') /*Kendi taşı varsa */
				SolUst=  0;
			else if(board[i1-9]>='A' && board[i1-9]>='Z') /*Rakip taşı varsa */
				SolUst=  1; 
		}
		/*Sağ alt Kontrol */
		i1=index1;
		while(i1+9>0 && board[i1+9]==' '){
			i1=i1+9;
		}
		if(i1<=63 && i1>=56) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			SagAlt= 0;
		else{
			if(board[i1+9]>='a' && board[i1+9]>='z') /*Kendi taşı varsa */
				SagAlt= 0;
			else if(board[i1+9]>='A' && board[i1+9]>='Z') /*Rakip taşı varsa */
				SagAlt= 1; 
		}
		/*Sol alt Kontrol */
		i1=index1;
		while(i1+7<64 && board[i1+7]==' '){
			i1=i1+7;
		}
		if(i1<=63 && i1>=56) /* Sona kadar gidip elaman bulmamamışsa direk return 0; */
			SolAlt= 0;
		else{
			if(board[i1+7]>='a' && board[i1+7]>='z') /*Kendi taşı varsa */
				SolAlt= 0;
			else if(board[i1+7]>='A' && board[i1+7]>='Z') /*Rakip taşı varsa */
				SolAlt= 1; 
		}
		if(Sag==1 || Sol==1 || Ust==1 || Alt==1 || SagAlt==1 || 
		   SolAlt==1|| SagUst==1 || SolUst==1)
			return 1;
		return 0;
	}
			printf("AQ\n");
	return 0;
}
int isPieceMovable(char *board, char sc, int sr, char tc, int tr){
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
/* Hareket etmek istediğimiz yerin ve hareket ettireceğimiz yerin satranç 
tahtasına göre geçerli adresler olup olmadıüını kontrol etecek, eğer ikiside
geçerliyse, gerekli işlemler yapılacak, herhangi biri bile geçersizse, direk 
return 0 edilecek.														*/
	m=isValidCell(sc,sr);
	n=isValidCell(tc,tr);

	if (m==1 && n==1){
	
		FindIndexInArray(sc, sr,tc, tr,&index1,&index2);
	
	/* OYNAMAK İSTEDİĞİMİZ TAŞ BOŞSSA */
		if(board[index1]==' '){
			return 0;
		}	
	
	/*KÜÇÜK HARFLİ TAŞLARIN SAHİBİ OYUNCU İÇİN: *//* Siyah renkli*/
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
					controller=isKnightMovable(board,sc,sr,tc, tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='r'){
					controller=isRookMovable(board,sc,sr,tc, tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='b'){
					controller=isBishopMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='q'){
					controller=isQueenMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
			
				else if(board[index1]=='k'){
					controller=isKingMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
			
				else if(board[index1]=='p'){
					controller=isPawnMovable(board,sc,sr,tc,tr);
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
					controller=isKnightMovable(board,sc,sr,tc,tr);
					if(controller==0) 
						return 0;
					else 
						return 1;	
				}
				if(board[index1]=='r'){
					controller=isRookMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='b'){
					controller=isBishopMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='q'){
					controller=isQueenMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='k'){
					controller=isKingMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='p'){
					controller=isPawnMovable(board,sc,sr,tc,tr);
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
					controller=isKnightMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;	
		
				}
				else if(board[index1]=='R'){
					controller=isRookMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='B'){
					controller=isBishopMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='Q'){
					controller=isQueenMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='K'){
					controller=isKingMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='P'){
					controller=isPawnMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
			}
			/*gideceği yer boşsa */
			else{
				if(board[index1]=='N'){
					controller=isKnightMovable(board,sc,sr,tc,tr);
				
					if(controller==0)
						return 0;
					else 
						return 1;	
		
				}
				else if(board[index1]=='R'){
					controller=isRookMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='B'){
					controller=isBishopMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='Q'){
					controller=isQueenMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='K'){
					controller=isKingMovable(board,sc,sr,tc,tr);
					if(controller==0)
						return 0;
					else 
						return 1;		
				}
				else if(board[index1]=='P'){
					controller=isPawnMovable(board,sc,sr,tc,tr);
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
int makeMove(char *board, char sc, int sr, char tc, int tr){

	int index1,index2;
	int CanItMove;
	char currPlayer;
	FindIndexInArray(sc,sr,tc,tr,&index1,&index2);
	
	CanItMove=isPieceMovable(board,sc,sr,tc,tr);
	currPlayer = getPlayer(board, sc,sr);
	if(CanItMove==0)
		return 0;
	else if(CanItMove==1){
		if(isBlack(currPlayer) && isInCheck(board)==2)
			return 1;
		else if(isWhite(currPlayer) && isInCheck(board)==1)
			return 1;
		board[index2]=board[index1]; 
		board[index1]=' ';
		if((isWhite(currPlayer) && isInCheck(board)==2) || 
		   (isBlack(currPlayer) && isInCheck(board)==1)){
			printf("wtf??");
			return 3;}
		else{
		printf("%d,%d\n",isInCheck(board),isWhite(currPlayer));
			return 2;
			}
	
	
	
	
	
	/*
		if(isBlack(currPlayer) && isInCheck(board)==2){
			board[index2]=board[index1]; 
			board[index1]=' ';
			if(isBlack(currPlayer) && isInCheck(board)==2)
				return 1;
			else if(isInCheck(board)==1)
				return 3;
			else
				return 2;
		}
		else if(isWhite(currPlayer) && isInCheck(board)==1){
			board[index2]=board[index1]; 
			board[index1]=' ';
			if(isBlack(currPlayer) && isInCheck(board)==2)
				return 1;
			else if(isInCheck(board)==2)
				return 3;
			else
				return 2;
		}
		board[index2]=board[index1]; 
		board[index1]=' ';
		if((isWhite(currPlayer) && isInCheck(board)==2) || 
		   (isBlack(currPlayer) && isInCheck(board)==1)){printf("wtf??");
			return 3;}
		else{printf("%d,%d\n",isInCheck(board),isWhite(currPlayer));
			return 2;}
			
	}
	*/


	}
	return 0;
}


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
	/* Source taşımızın olduğu yerin indexi ile gitmek istediği yerin indexi farkı i olmalı, (Sağ üst/sol üst/alt..) çapraza gidebilmesi için*/
	int i;		
	
	FindIndexInArray(sourceCol, sourceRow,targetCol, targetRow,&index1,&index2);

/*******KÜÇÜK TAŞLARA SAHİP OYUNUCU OYNACYAKSA**************** */
	if(board[index1]=='r' || board[index1]=='n' || board[index1]== 'b' || 
	   board[index1]=='q' || board[index1]=='k' || board[index1]=='p'){
	
	/* Sağ üst çapraza gidekse fil*/
		if((index1-index2+1)%7==1){
/* Source taşımızın olduğu yerin indexi ile gitmek istediği yerin indexi farkı 7 olmalı, Sağ üst çapraza gidebilmesi için*/
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
