#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <linux/limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>

/* Verilen path konumundan sadece dosyanın adını return eder. Bulunan değerleri 
dosyaya yazdırırken dosya adı istendiğinden orada kullanıcalak.  
*/
char* returnTxt(char* str);
/*  Bu fonksiyon dosyada, aranan kelimenin uzunlugu kadar gezer, o kelimeyi
 	return eder, daha sonra dosyadaki imleci , okumaya basladigi yerin bir
 	adim ilerisine goturur. Boylece bu fonksiyonu cagirarak dosyada aranan 
 	kelimenin boyutu kadar gezip dururuz.
*/
char* readSomeCharacter(FILE * fptr,char* readed,int lengtofTarget, int* row,
																	int *col);
/* Bu fonksiyon readSomeCharacter'in return ettigi char arrayinin, target 
   array ile aynı olup olmadigini kontrol eder. Eger ayni ise ekrana
   dosyada bulunan kelimenin koordinatlarini row-col olarak basar.
*/
void countWords(char* pathName,char* target);
/* Bu fonksiyon, aranılan kelimenin dosyada toplam kaç adet bulundugunu
hesaplar ve dosyaya yazar.
*/
void totalFound(char * target);
/* Ders kitabından alındı. Ana processin tüm childlarını beklemesi için
gerekli bir fonksiyondur 
*/
pid_t r_wait(int *stat_loc);
/*
Bu fonksiyon verilen directorydeki her dosya ve klasor icin ayrı bir process
oluşturacak, main process oluşturulan döngünün devamını saglayıp tum
klasor ve dosyalar icin process olustucak, childlar ise dosyalarda
aranacak kelimeyi aramak icin gerekli fonksiyonlar cagiracak, klasorlerde
ise tekrar kendi fonksiyonunu cagiracak. Boylece tekrar kendi çocuğunu oluştu-
racak ve bu main processin torunu olacak. 
*/
void grepFromDirectory(char* path,char* targetWord);


int main(int argc, char *argv[]){

	char* target = argv[1];
	char* directory = argv[2];
	char path[PATH_MAX] ;
	getcwd(path,PATH_MAX);
	strcat(path,"/");
	strcat(path,directory);

	if (argc != 3) {
		perror("Usage: ./listdir <target word> <directory_name>:");
		return 1;
	}

	grepFromDirectory(path,target);
	totalFound(target);

	return 0;

}

char* readSomeCharacter(FILE * fptr,char* readed,int lengtofTarget,int* row,int *col){
	char temp; /* Kontrol etmek icin okunacak char */
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
	readed[index] = 0;
	fseek(fptr,-1*(count2),SEEK_CUR);
	fseek(fptr,-1*(lengtofTarget-1),SEEK_CUR);

	return readed;
}

char* returnTxt(char* str){
	char * position;

	position = strstr(str, ".txt");
	if (position == NULL)
		return NULL;

	while(*position != '/')
		--position;

	++position;

	str = position;
	return str;
}


void countWords(char* pathName,char* target){
    char ignorMe; 
    char *temp;
	FILE * fptr ,*wptr;
   	int total = 0 ;
	int row =1;
	int col = 1;
   	int size = strlen(target);
   	char * filename = returnTxt (pathName);
	char *readed = (char*)malloc(size+1) ;
	fptr = fopen(pathName, "r");
	wptr = fopen("log.log", "a+");

	if (fptr == NULL){
		perror("The file is not found!");
		exit(0);
	}
	if (wptr == NULL){
		perror("The file is not found!");
		exit(0);
	}
	for(ignorMe = fgetc(fptr); ignorMe != EOF; ignorMe = fgetc(fptr)){
		fseek(fptr,-1,SEEK_CUR);
		temp = readSomeCharacter(fptr,readed,size,&row,&col);
		if (strcmp(target,"") == 0)
		    break;

		if ( strcmp(target,temp) == 0 ){
			++total;
		    fprintf(wptr,"%s:[%d,%d] %s first character is found.\n",filename,
		    													row,col,target);
		    fflush(wptr);
		}
		++col;
	}
    free(readed);	
	fclose(fptr);
	fclose(wptr);

}

void totalFound(char * target){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    int count = 0;
    ssize_t read;
    char* found;
    fp = fopen("log.log", "a+");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        found = strstr(line,target);
        if ( found != NULL)
        	++count;
    }

    if (line)
        free(line);
    fprintf(fp,"%d %s were found in total.\n",count,target );
    fclose(fp);

}

pid_t r_wait(int *stat_loc) {
	int retval;
	while (((retval = wait(stat_loc)) == -1) && (errno == EINTR)) ;
		return retval;
}

void grepFromDirectory(char* path,char* targetWord){
	pid_t childpid = 0;
	struct dirent *direntp = NULL;
	char temp[PATH_MAX];
	DIR *dirp = NULL;
	if ((dirp = opendir(path)) == NULL) {
		perror ("Failed to open directory");
		return ;
	}
	while ((direntp = readdir(dirp)) != NULL){

		if (strcmp(direntp->d_name, ".") == 0 || 
			strcmp(direntp->d_name, "..") == 0 || 
        	direntp->d_name[strlen(direntp->d_name) - 1] == '~')

            continue;
		
		childpid = fork();

		if ( childpid < 0){
			perror("Failed to fork");
			return;
		}
		else if ( childpid == 0){
			/* Klasor ise */
			if((direntp->d_type) == DT_DIR){
				strcpy(temp,path);
				strcat(temp,direntp->d_name);
				strcat(temp,"/");
				grepFromDirectory(temp,targetWord);

			}
			/* Regular dosya ise */
			else if((direntp->d_type) == DT_REG ){

				strcpy(temp,path);
				strcat(temp,direntp->d_name);
				countWords(temp,targetWord);
				
			
			}
			break;
		}

	}
	/* Main process tüm childları beklemeli */
	while(r_wait(NULL) > 0);
	/* İsi biten processleri oldurmeliyiz. */
	if(childpid == 0)
		exit(0);
	
	/* Acilan dosyaları kapatmalıyız.*/
	closedir(dirp);
}
