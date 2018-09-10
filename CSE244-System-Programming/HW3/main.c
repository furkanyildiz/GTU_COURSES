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
int countWords(char* pathName,char* target);
/* Bu fonksiyon, aranılan kelimenin dosyada toplam kaç adet bulundugunu
hesaplar ve dosyaya yazar.
*/
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
void grepFromDirectory(char* path,char* targetWord, int fifopath,pid_t mainpid);
ssize_t r_write(int fd, void *buf, size_t size) {
	char *bufp;
	size_t bytestowrite;
	ssize_t byteswritten;
	size_t totalbytes;
	for (bufp = buf, bytestowrite = size, totalbytes = 0;
	bytestowrite > 0;
	bufp += byteswritten, bytestowrite -= byteswritten) {
		byteswritten = write(fd, bufp, bytestowrite);
		if ((byteswritten) == -1 && (errno != EINTR))
			return -1;
		if (byteswritten == -1)
			byteswritten = 0;
		totalbytes += byteswritten;
	}
	return totalbytes;
}
ssize_t r_read(int fd, void *buf, size_t size) {
	ssize_t retval;
	while (retval = read(fd, buf, size), retval == -1 && errno == EINTR) ;
	return retval;
}

int main(int argc, char *argv[]){

	char* target = argv[1];
	char* directory = argv[2];
	char path[PATH_MAX] ;
	char temp[PATH_MAX] ;
	int mainpid = getpid();
	int total =0;
	int num = 0;
	int f;
	int fiforead,fifowrite;
	FILE * fp;
	remove("log.log");
	getcwd(path,PATH_MAX);
	strcat(path,"/");
	strcat(path,directory);

	if (argc != 3) {
		perror("Usage: ./listdir <target word> <directory_name>:");
		return 1;
	}
	/* Eğer sonda '/' isareti yoksa koymaliyiz. */
	if(path[strlen(path)-1] != '/')
		strcat(path,"/");

	strcpy(temp,path);
	strcat(temp,"FIFOFILE");
	unlink(temp);

	if (mkfifo(temp, 0666) == -1) { /* create a named pipe */
		if (errno != EEXIST) {
			fprintf(stderr, "[%ld]:failed to create named pipe %s: %s\n",
			(long)getpid(), "FIFOFILE", strerror(errno));
		}
	}
	
	if ((fifowrite = open(temp, O_RDWR )) < 0)
		fprintf(stderr, "open error\n" );

	grepFromDirectory(path,target,fifowrite,mainpid);

	close(fifowrite);
	if ((fiforead = open(temp, O_RDONLY )) < 0)
		fprintf(stderr, "open error\n" );
	while ( (f = read(fiforead, &num,sizeof(int))) > 0)
		total +=num;

	close(fiforead);
	fp = fopen("log.log", "a+");

	fprintf(fp,"%d %s were found in total.\n",total, target );
    fclose(fp);
	unlink(temp);
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
int countWords(char* pathName,char* target){
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
		    fprintf(wptr,"%s:[%d,%d] %s first character is found.\n",filename,row,col,target);
		    fflush(wptr);
		}
		++col;
	}
    free(readed);
	fclose(fptr);
	fclose(wptr);
	return total;
}

pid_t r_wait(int *stat_loc) {
	int retval;
	while (((retval = wait(stat_loc)) == -1) && (errno == EINTR)) ;
		return retval;
}

void grepFromDirectory(char* path,char* targetWord, int fifopath, pid_t mainpid){
	pid_t childpid = 0;
	int fdp[2];
	struct dirent *direntp = NULL;
	char temp[PATH_MAX];
	int total2 = 0 ;
	int num = 0;
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

        if((direntp->d_type) == DT_REG)
			pipe(fdp);


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
				grepFromDirectory(temp,targetWord,fifopath,mainpid);
				
			}
			/* Regular dosya ise */
			else if((direntp->d_type) == DT_REG ){


				strcpy(temp,path);
				strcat(temp,direntp->d_name);
				total2 = countWords(temp,targetWord);
				close(fdp[0]);

				if(write(fdp[1], &total2, sizeof(total2)) <= 0)
					printf("Yazma hatalı!\n" );

				close(fdp[1]);

			}
			break;
		}
		else if(childpid > 0){

			/*oku dosyadaki counterleri topla*/
        	if((direntp->d_type) == DT_REG){

				close(fdp[1]);
				if (read(fdp[0],&num,sizeof(num)) > 0)

					write(fifopath,&num,sizeof(int));

				close(fdp[0]);
			}
		}
	}
	/* İsi biten processleri oldurmeliyiz. */
	if(mainpid != getpid())
		exit(0);

	/* Main process tüm childları beklemeli */
	while(wait(NULL) != -1);
	/* Acilan dosyaları kapatmalıyız.*/
	closedir(dirp);

}