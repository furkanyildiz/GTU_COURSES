#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Bu fonksiyon dosyada, aranan kelimenin uzunlugu kadar gezer, o kelimeyi
 	return eder, daha sonra dosyadaki imleci , okumaya basladigi yerin bir
 	adim ilerisine goturur. Boylece bu fonksiyonu cagirarak dosyada aranan 
 	kelimenin boyutu kadar gezip dururuz.
*/
char* readSomeCharacter(FILE * fptr,char* readed,int lengtofTarget,int* row,
																	int *col){

	char temp;
	int index = 0; /* doldurulup return edilecek, stringin indexi*/
    int count = 0; /* okunan tüm karakterlerin sayısı */
    int count2 = 0; /* impute edilen karakterlerin sayısı */
    int flag = 0; /* '\n' karakterini bir kere okumak icin tutulan flag */

    /* imlec imputer uzerinde olmamali */
	for (temp=fgetc(fptr); ( temp=='\n'|| temp=='\t' || temp== ' ');
														temp=fgetc(fptr) ){
		if ( temp=='\n'){
			*col = 1;
			++(*row);
		}
		else
			++(*col);
	}
	/* Fazla okunan karakter geri verilmeli. */
	fseek(fptr,-1,SEEK_CUR);


	while( index != lengtofTarget ){
        temp = fgetc(fptr);
    	++count;

        if (temp == EOF)
        	return "";	
        

        if(temp != '\n' && temp!='\t' && temp!= ' '){
            readed[index++] = temp;
            flag = 1;
        }
        else 
        	++count2;    
     	if (temp == '\n' && flag ==0){
            ++(*row);
            *col = 0;
            flag = 1;
     	}
	}
	readed[index] = '\0';
	fseek(fptr,-1*(count2),SEEK_CUR);
	fseek(fptr,-1*(lengtofTarget-1),SEEK_CUR);

	return readed;
}
/* Bu fonksiyon readSomeCharacter'in return ettigi char arrayinin, target 
   array ile aynı olup olmadigini kontrol eder. Eger ayni ise ekrana
   dosyada bulunan kelimenin koordinatlarini row-col olarak basar.

*/
void countWords(FILE* fptr , char* target){
    char ignorMe; 
    char *temp;
   	int total = 0 ;
	int row =1;
	int col = 1;
   	int size = strlen(target);
	char *readed = (char*)malloc(size+1) ;
	for(ignorMe = fgetc(fptr); ignorMe != EOF; ignorMe = fgetc(fptr)){
		fseek(fptr,-1,SEEK_CUR);
		temp = readSomeCharacter(fptr,readed,size,&row,&col);
		if (strcmp(target,"") == 0)
		    break;

		if ( strcmp(target,temp) == 0 ){
			++total;
		    printf("%s found in row: %d , col: %d\n",target,row,col);
		}
		++col;
	}
    printf("Totally %d, %s found\n",total,target);
    free(readed);	
}
int main(int argc, char *argv[]){

    char* filename= argv[2];
	char* target = argv[1];
	FILE * fptr;
	if (argc != 3){
		printf("You have to run like './list string  <filename>'\n");
		exit(0);
	}

	fptr = fopen(filename, "r");
	if (fptr == NULL){
		printf("The file is not found!\n");
		exit(0);
	}

	countWords(fptr,target);
	fclose(fptr);
	return 0;

}
