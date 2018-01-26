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
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define PERMS (mode_t)(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FLAGS (O_CREAT | O_EXCL)
#include <sys/time.h>
#define MILLION 1000000L
int size=0;
int indexOfThread = 0;
int max;
sem_t* semo;
sem_t* semo2;
struct timeval tpstart;
int mainpid;

typedef struct{

	char pathName[PATH_MAX];
	char* target;

}SearchWord;

int print(char* filename){

	int total = 23;
    FILE *fread, *fwrite;
    fread = fopen(filename, "r");
    fscanf(fread,"%d",&total);
    fclose(fread);
    return total;
}

void printAll(int error, int control){

    double timeOfProcess;
    long timedif;
    struct timeval tpend;

	int numOfDirectories = print("targetDirectories.txt");
	int numOfFiles = print("targetFiles.txt");
	int numOfLines = print("lines.txt");
	int numOfTargets = print("targetCounts.txt");
	if (gettimeofday(&tpend, NULL)) {
        fprintf(stderr, "Failed to get end time\n");
    }
    timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
    tpend.tv_usec - tpstart.tv_usec;
    timeOfProcess =  (double)timedif / 1000.0;

	printf("Total number of strings found:%d\n",numOfTargets );
	printf("Number of directories searched:%d\n",numOfDirectories+1 );
	printf("Number of files searched:%d\n",numOfFiles );
	printf("Number of lines searched: %d\n",numOfLines );
	printf("Number of cascade threads created: %d\n",max );
	printf("Number of search threads created:%d\n",numOfFiles );
	printf("Max # of threads running concurrently:%d\n",numOfDirectories+1 );
	printf("Total run time, in milliseconds. :%f\n",timeOfProcess );
	if(error == 999999)
		printf("Exit condition: Not TXT FILE");
	else if(control == 1)
		printf("Exit condition: Due to signal no: %d\n",error );
	else if(control == 2)
		printf("Exit condition: Due to error no: %d\n",error );
	else
		printf("Exit condition: normal\n" );

	remove("targetDirectories.txt");
	remove("targetFiles.txt");
	remove("lines.txt");
	remove("targetCounts.txt");
	remove("sonuc.txt");

}

void HandleSignal(int sig, siginfo_t *siginfo, void *context)
{
    int j,i;
    char path[1024];
    char itspath[1024];
	getcwd(path,1024);
    strcat(path,"/Log/");
    strcpy(itspath, path);
    FILE *pFile;
    time_t rawtime;
    struct tm * timeinfo;
   	switch(sig){


        case SIGINT:
			if(mainpid == getpid())
				printAll(sig,1);
			_exit(0);
		break;

		case SIGUSR1:
			if(mainpid == getpid())
				printAll(sig,0);
			_exit(0);
		break;
		case SIGUSR2:
			_exit(0);
		break;
		default:
			if(mainpid == getpid())
				printAll(sig,1);
			_exit(0);
		break;
   }
   _exit(0);
}



int countTxt(char* path){
	struct dirent *direntp = NULL;
	DIR *dirp = NULL;
	static int count = 0 ;
	int num;
	char temp[PATH_MAX];
	int num2 = 0;

	if ((dirp = opendir(path)) == NULL) {
		perror ("Failed to open directory in readd function!!");
		return -1;
	}
	while ((direntp = readdir(dirp)) != NULL){

		if (strcmp(direntp->d_name, ".") == 0 ||
			strcmp(direntp->d_name, "..") == 0 ||
        	direntp->d_name[strlen(direntp->d_name) - 1] == '~')
            continue;

		if ((direntp->d_type) == DT_DIR){
			strcpy(temp,path);
			strcat(temp,"/");
			strcat(temp,direntp->d_name);
			strcat(temp,"/");
			countTxt(temp);
		}
		else if((direntp->d_type) == DT_REG ){

			if(strcmp(&(direntp->d_name[strlen(direntp->d_name)-4]),".txt") == 0)
				count++;
				num2++;
		}
		if(num2 > max)
			max = num2;
	}

	return count;

}
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
void* countWords(void* param);
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
void grepFromDirectory(char* path,char* targetWord, pid_t mainpid,pthread_t *tids, int txtCount);
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

#define PERMS (mode_t)(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FLAGS (O_CREAT | O_EXCL)
int getnamed(char *name, sem_t **sem, int val) {
	while (((*sem = sem_open(name, FLAGS, PERMS, val)) == SEM_FAILED) && (errno == EINTR)) ;
	if (*sem != SEM_FAILED)
		return 0;
	if (errno != EEXIST)
		return -1;
	while (((*sem = sem_open(name, 0)) == SEM_FAILED) && (errno == EINTR)) ;
	if (*sem != SEM_FAILED)
		return 0;
	return -1;
}
void initilazeAFile(char* filename){
	FILE *fp;
	int num = 0;
	fp = fopen(filename,"w");
	fprintf(fp, "%d",num);
	fclose(fp);

}
void initilazeFiles(){

	char *lines = "lines.txt";
	char *sonuc = "sonuc.txt";
	char *directories = "targetDirectories.txt";
	char *files = "targetFiles.txt";
	char *targetsCount = "targetCounts.txt";

	remove(lines);
	remove(sonuc);
	remove(directories);
	remove(files);
	remove(targetsCount);

	initilazeAFile(lines);
	initilazeAFile(sonuc);
	initilazeAFile(directories);
	initilazeAFile(files);
	initilazeAFile(targetsCount);

}


int main(int argc, char *argv[]){

    if (gettimeofday(&tpstart, NULL)) {
        fprintf(stderr, "Failed to get start time\n");
        return 1;
    }
	char* target = argv[1];
	char* directory = argv[2];
	char path[PATH_MAX] ;
	mainpid = getpid();
	unsigned int value =1;
    double timeOfProcess;
    long timedif;
    struct timeval tpend;

	int total =0;
	int num = 0;
	int f;

	FILE * fp;
	remove("log.txt");
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

	initilazeFiles();

	struct sigaction new_action, old_action;

    new_action.sa_sigaction = HandleSignal;
    sigemptyset (&new_action.sa_mask);
    new_action.sa_flags = SA_SIGINFO;
	sigaction (SIGHUP, &new_action , NULL);
	sigaction (SIGINT, &new_action,NULL);
	sigaction (SIGQUIT, &new_action,NULL);
	sigaction (SIGILL, &new_action,NULL);
	sigaction (SIGABRT, &new_action,NULL);
	sigaction (SIGFPE, &new_action,NULL);
	sigaction (SIGSEGV, &new_action,NULL);
	sigaction (SIGPIPE, &new_action,NULL);
	sigaction (SIGALRM, &new_action,NULL);
	sigaction (SIGTERM, &new_action,NULL);
	sigaction (SIGCONT, &new_action,NULL);
	sigaction (SIGTSTP, &new_action,NULL);
	sigaction (SIGTTIN, &new_action,NULL);
	sigaction (SIGTTOU, &new_action,NULL);
	sigaction (SIGIOT, &new_action,NULL);
	sigaction (SIGSTKFLT, &new_action,NULL);
	sigaction (SIGIO, &new_action,NULL);
	sigaction (SIGPWR, &new_action,NULL);
	sigaction (SIGWINCH, &new_action,NULL);
	sigaction (SIGUNUSED, &new_action,NULL);
	sigaction (SIGPWR, &new_action,NULL);
	sigaction (SIGPWR, &new_action,NULL);
	sigaction (SIGUSR1, &new_action,NULL);
	sigaction (SIGUSR2, &new_action,NULL);

	int txtCount = countTxt(path);
	pthread_t *tids;
	tids = (pthread_t *)malloc(txtCount * sizeof(pthread_t));



	char* semname = "/semaphore";
	char* semname2 = "/semaphore2";

	if(getnamed(semname,&semo,1) == -1)
		kill(getpid(),SIGUSR2);

	if(getnamed(semname2,&semo2,1) == -1)
		kill(getpid(),SIGUSR2);

	grepFromDirectory(path,target,mainpid,tids,txtCount);
	sem_close(semo);
	sem_unlink(semname);
	sem_close(semo2);
	sem_unlink(semname2);
	free(tids);
	if (mainpid != getpid()){
		exit(0);
	}

	if (mainpid == getpid()){
		int total = 45;
		FILE *fp;

		FILE* fptr = fopen("targetCounts.txt","r");
		if(fptr == NULL){
			printAll(errno,2);
			kill(getpid(),SIGUSR2);
		}
		fscanf(fptr,"%d",&total);
		fclose(fptr);

		fp = fopen("log.txt", "a+");
		if (fp == NULL){
			printAll(errno,2);
			kill(getpid(),SIGUSR2);
		}
		fprintf(fp,"%d %s were found in total.\n",total, target );
		fclose(fp);
	}
	kill(getpid(),SIGUSR1);
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
void readAndIncrease(char* filename,int increment){

    int total = 23;
    FILE *fread, *fwrite;
    fread = fopen(filename, "r");
    fscanf(fread,"%d",&total);
    fclose(fread);
    indexOfThread = total;
    total+=increment;
    fwrite = fopen(filename,"w");
    fprintf(fwrite ,"%d",total);
    fclose(fwrite);

}
void* countWords(void* param){

    char ignorMe;
    char *temp;
	FILE * fptr ,*wptr;
   	long int total = 0 ;
	int row =1;
	int col = 1;
	SearchWord searched = *((SearchWord*)(param));
	char * target;
	target = searched.target;

   	int size = strlen(target);
   	char * filename = returnTxt (searched.pathName);
	char *readed = (char*)malloc(size+1) ;
	fptr = fopen(searched.pathName, "r");
	wptr = fopen("log.txt", "a+");
	char line[3000];
	int linenumber=0;;
    while (fgets(line, sizeof(line), fptr))
        linenumber++;

    readAndIncrease("lines.txt",linenumber);
    fclose(fptr);
	fptr = fopen(searched.pathName, "r");

	if (fptr == NULL){
		printAll(errno,2);
		kill(getpid(),SIGUSR2);
	}
	if (wptr == NULL){
		printAll(errno,2);
		kill(getpid(),SIGUSR2);
	}
	for(ignorMe = fgetc(fptr); ignorMe != EOF; ignorMe = fgetc(fptr)){
		fseek(fptr,-1,SEEK_CUR);

		temp = readSomeCharacter(fptr,readed,size,&row,&col);
		if (strcmp(target,"") == 0)
		    break;

		if ( strcmp(target,temp) == 0 ){
			++total;
		    fprintf(wptr,"ProcessID:%d - ThreadID:%ld  Filename:%s:[%d,%d] %s first character is found.\n",getpid(),pthread_self(),filename,row,col,target);
		    fflush(wptr);
		    readAndIncrease("targetCounts.txt",1);

		}
		++col;
	}
    free(readed);
	fclose(fptr);
	fclose(wptr);


	if (sem_post(semo) == -1){
		printAll(errno,2);
		kill(getpid(),SIGUSR2);
	}
	return ((long int *)total);
}

pid_t r_wait(int *stat_loc) {
	int retval;
	while (((retval = wait(stat_loc)) == -1) && (errno == EINTR)) ;
		return retval;
}

void readAndwrite(){

    int total = 23;
    FILE *fread, *fwrite;
    fread = fopen("sonuc.txt", "r");
    fscanf(fread,"%d",&total);
    fclose(fread);
    indexOfThread = total;
    ++total;
    fwrite = fopen("sonuc.txt","w");
    fprintf(fwrite ,"%d",total);
    fclose(fwrite);
}
void grepFromDirectory(char* path,char* targetWord, pid_t mainpid,pthread_t *tids, int txtCount){
	pid_t childpid = 0;
	struct dirent *direntp = NULL;
	char temp[PATH_MAX];
	int total2 = 0 ;
	int num = 0;
	DIR *dirp = NULL;
	void *count = 0;

	if ((dirp = opendir(path)) == NULL) {
		printAll(errno,2);
		kill(getpid(),SIGUSR2);
	}
	while ((direntp = readdir(dirp)) != NULL){

		if (strcmp(direntp->d_name, ".") == 0 ||
			strcmp(direntp->d_name, "..") == 0 ||
        	direntp->d_name[strlen(direntp->d_name) - 1] == '~')
            continue;

		if((direntp->d_type) == DT_DIR){
			while (sem_wait(semo2) == -1){
				if(errno != EINTR) {
					printAll(errno,2);
					pthread_exit(NULL);
					kill(getpid(),SIGUSR2);
				}
			}

			readAndIncrease("targetDirectories.txt",1);

			if (sem_post(semo2) == -1){
				printAll(errno,2);
				kill(getpid(),SIGUSR2);
			}

			childpid = fork();

			if(childpid == 0){
				strcpy(temp,path);
				strcat(temp,direntp->d_name);
				strcat(temp,"/");
				grepFromDirectory(temp,targetWord,mainpid,tids,txtCount);

			}
		}
		/* Text file ise eğer thread oluşturulacak  */
		else if((direntp->d_type) == DT_REG &&  (strcmp(&(direntp->d_name[strlen(direntp->d_name)-4]),".txt") == 0  || strchr(direntp->d_name,'.') == NULL)){

			while (sem_wait(semo) == -1){ /* Entry section */

				if(errno != EINTR) {
					printAll(errno,2);
					pthread_exit(NULL);
					kill(getpid(),SIGUSR2);
				}
			}
			readAndIncrease("targetFiles.txt",1);
			strcpy(temp,path);
			strcat(temp,direntp->d_name);
			SearchWord search;
			strcpy(search.pathName,temp);
			search.target = targetWord;
			readAndwrite();
			pthread_create(&tids[indexOfThread], NULL, countWords,&search);
		}
		else{
			printAll(999999,2);
			kill(getpid(),SIGUSR2);
		}

	}


	for(int i=0; i<txtCount; ++i){
		pthread_join(tids[i], &count);
	}

	/* Main process tüm childları beklemeli */
	while(wait(NULL) != -1);

	/* Acilan dosyaları kapatmalıyız.*/
	closedir(dirp);
}
