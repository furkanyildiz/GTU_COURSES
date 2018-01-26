#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#define _GNU_SOURCE
#include <string.h>
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
#define LOGFILE "showResults.log"
char workingClients[9999][200];
int workingClientsCount = 0;
int mainpid = 0;
struct MatrixInformation{

	int pidOfClient;
	double result1;
	double timeElaps1;
	double result2;
	double timeElaps2;

};
int isItContain(char arr[9999][200],int size, char target[200]){

	for(int i=0; i<size; ++i){
		if(strcmp(arr[i],target) == 0){

			return 1;
		}
	}

	return 0;
}

int updateList(char pidOfClients[][200]){
	FILE * pFile;
    char * line ;
    size_t len = 0;
    ssize_t read;
	char *token ;
	char path[1024];
	getcwd(path,1024);
    strcat(path,"/Log/timeServer.log");
    //acılana kadar whila sok
    pFile = fopen (path, "r");
    int countOfClients = 0;
    char currentClient[200];
    while ((read = getline(&line, &len, pFile)) != -1) {

	    token = strtok(line, "\t");
	    int i = 0;
	    token = strtok(NULL, "\t");
		if( token == NULL)
			break;
    	if(isItContain(pidOfClients,countOfClients,token) == 0   && token != NULL){
    		strcpy(currentClient,token);
    		strcpy(pidOfClients[countOfClients++],currentClient );

    	}
    }

    fclose(pFile);
    return countOfClients;

}
void HandleSignal(int sig, siginfo_t *siginfo, void *context)
{
    int j,i;
    char path[1024];
    char itspath[1024];
	getcwd(path,1024);
    strcat(path,"/Log/");
    strcpy(itspath, path);
    strcat(itspath,LOGFILE);
    FILE *pFile;
    time_t rawtime;
    struct tm * timeinfo;
   	switch(sig){
		case SIGALRM:
			if(mainpid == getpid()){

    			pFile = fopen (itspath, "a+");
                time ( &rawtime );
                timeinfo = localtime ( &rawtime );
                char * time = asctime (timeinfo);
                fprintf(pFile, "Kill signal has received %s\n",time);    			
				fclose(pFile);

				for(int i=0; i<workingClientsCount; ++i)
				{	
					getcwd(path,1024);
					strcat(path,"/Log/");
					strcat(path,workingClients[i]);
					strcat(path,"_results");
					unlink(path);	
				}
			}
            _exit(0);
        break;
        case SIGINT:
        	if(mainpid == getpid()){
    			pFile = fopen (itspath, "a+");
				time ( &rawtime );
                timeinfo = localtime ( &rawtime );
                char * time = asctime (timeinfo);
                fprintf(pFile, "Control-C was pressed in showResults. %s \n",time);
				fclose(pFile);
				for(int i=0; i<workingClientsCount; ++i)
					kill(atoi(workingClients[i]),SIGINT);

				for(int i=0; i<workingClientsCount; ++i)
				{	
					getcwd(path,1024);
					strcat(path,"/Log/");
					strcat(path,workingClients[i]);
					strcat(path,"_results");
					unlink(path);	
				}

			}
			_exit(0);
		break;
   }
   _exit(0);
}
int main(int argc, char** argv) {

    if(argc != 1){
        fprintf(stderr, "Usage error!\n" );
        exit(0);
    }


	struct MatrixInformation createdMatrix;

    char pidOfClients[9999][200];
    int countOfClients;
	char path[1024];
	char itspath[1024];
	int childpid;
	getcwd(path,1024);
    strcat(path,"/Log/");
    strcpy(itspath, path);
    strcat(itspath,LOGFILE);
	FILE* pFile;
	mainpid = getpid();
	createdMatrix.pidOfClient = getpid();
	createdMatrix.result1 = 23.23;
	createdMatrix.timeElaps1 = 23.23;
	createdMatrix.result2 = 23.23;
	createdMatrix.timeElaps2 = 23.23;

    struct sigaction new_action;

	while(1){

		new_action.sa_sigaction = HandleSignal;
		sigemptyset (&new_action.sa_mask);
		new_action.sa_flags = SA_SIGINFO;
		sigaction (SIGALRM, &new_action , NULL);
		sigaction (SIGINT, &new_action , NULL);
		
	    countOfClients = updateList(pidOfClients);
	    getcwd(path,1024);
	    strcat(path,"/Log/");
		for(int i=0; i<countOfClients; ++i){
			
			if(isItContain(workingClients,workingClientsCount,pidOfClients[i]) == 0){
				strcpy(workingClients[workingClientsCount++], pidOfClients[i]);
				//Cliente show Resultun pidsini göndermek lazım, client kapanınca showResultta kapnaması için
				kill(atoi(pidOfClients[i]),SIGUSR1);

				childpid = fork();

				if(childpid == 0){
					while(1){
					    getcwd(path,1024);
					    strcat(path,"/Log/");
						strcat(path,pidOfClients[i]);
						strcat(path,"_results");
					    int fiforead;
					   	if ((fiforead = open(path, O_RDWR)) < 0)
					        fprintf(stderr, "open error\n" );

				        if (read(fiforead, &createdMatrix.pidOfClient, sizeof(int)) < 0)
				            fprintf(stderr, "read error\n" );       
				        if (read(fiforead, &createdMatrix.result1, sizeof(double)) < 0)
				            fprintf(stderr, "read error\n" );       
				        if (read(fiforead, &createdMatrix.timeElaps1, sizeof(double)) < 0)
				            fprintf(stderr, "read error\n" );       
				        if (read(fiforead, &createdMatrix.result2, sizeof(double)) < 0)
				            fprintf(stderr, "read error\n" );       
				        if (read(fiforead, &createdMatrix.timeElaps2, sizeof(double)) < 0)
				            fprintf(stderr, "read error\n" );
					    close(fiforead);


					    fprintf(stderr, "%.5d\t%.5f\t%.5f\n",createdMatrix.pidOfClient,createdMatrix.result1,createdMatrix.result2);

		    			pFile = fopen (itspath, "a+");
		                fprintf(pFile, "PID:%d\n",createdMatrix.pidOfClient );
		                fprintf(pFile, "Result1:%.5f\t\tTimeElaps1:%.5fms\n",createdMatrix.result1,createdMatrix.timeElaps1 );
		                fprintf(pFile, "Result2:%.5f\t\tTimeElaps2:%.5fms\n\n",createdMatrix.result2,createdMatrix.timeElaps2 );
		 

		    			fclose(pFile);
					}
				}

			}
		}
	}
	return 0;
}