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
#define FIFO_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define DEBUG 0
#define TXT "fifosfile.txt"
#define _ISOC99_SOURCE
#include <sys/time.h>
#define MILLION 1000000L
struct timeval tpstart;
static int msignal = 0;
static int matrixSize;
int count =0;
int pidSeeWhat[1000]; // pid's array of client's
int countOfSeeWhat = 0; // count of clients
pid_t serverPid ;
char MAINFIFO[PATH_MAX];
/**
    http://easy-learn-c-language.blogspot.com.tr/2013/02/numerical-methods-determinant-of-nxn.html
*/
double Determinant(double **matrix,int n)
{
    /* Conversion of matrix to upper triangular */
    int i,j,k;
    double det,ratio;

    double matrixCopy[n][n];
    for(i =0; i<n; ++i){
        for(j=0; j<n; ++j){
            matrixCopy[i][j] = matrix[i][j];
        }
    }

    for(i = 0; i < n; i++){

        for(j = 0; j < n; j++){

            if(j>i){

                ratio = matrixCopy[j][i]/matrixCopy[i][i];

                for(k = 0; k < n; k++){

                    matrixCopy[j][k] -= ratio * matrixCopy[i][k];

                }

            }

        }

    }

    det = 1; //storage for determinant

    for(i = 0; i < n; i++)
        det *= matrixCopy[i][i];
    return(det) ;
}


double createInvertibleMatrix(double ** matrix, int n){
  int i ,j ;
    srand(time(NULL));   

    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
        matrix[i][j] =  rand() %1000 -500;

    if( Determinant(matrix,n) == 0)
      return createInvertibleMatrix(matrix,n);
    else if (Determinant(matrix,n) == NAN)
      return createInvertibleMatrix(matrix,n);
    else
      return  Determinant(matrix,n);
}
static volatile sig_atomic_t doneflag = 0;
/* ARGSUSED */
static void setdoneflag(int signo) {
    doneflag = 1;
}

void HandleSignal(int sig, siginfo_t *siginfo, void *context)
{
    double ** matrix;
    int j,i;
    char path[1024];
    char pidOfClient[10];
    double timeOfMatrixGenerated;
    char writeLogInformations[1024];
    double detOfMatrix;
    int fifowrite;
    int childpid;
    time_t rawtime;
    struct tm * timeinfo;
    FILE * pFile;
    getcwd(path,1024);
    strcat(path,"/Log/timeServer.log");
    pFile = fopen (path, "a+");
    int contains = 0;

    switch(sig){
       
        case SIGUSR1:
            count++;
            childpid = fork();

            if(childpid == 0 ){
                sprintf(pidOfClient,"%ld",(long)siginfo->si_pid);
                getcwd(path,1024);
                strcat(path,"/Log/");
                strcat(path,pidOfClient);
                //unlink(path);
                long timedif;
                struct timeval tpend;


                matrix = (double **)malloc((2*matrixSize)*sizeof(double *));
                for (j=0;j<2*matrixSize;j++)
                    matrix[j] = (double *)malloc((2*matrixSize)*sizeof(double));
                perror("h2");
                detOfMatrix = createInvertibleMatrix(matrix,2*matrixSize);
                perror("h3");

                clock_t toc = clock();
                if (gettimeofday(&tpend, NULL)) {
                    fprintf(stderr, "Failed to get end time\n");
                }
                timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
                tpend.tv_usec - tpstart.tv_usec;
                timeOfMatrixGenerated =  (double)timedif / 1000.0;
                perror("h24");

                fprintf(pFile, "%f.ms\t",timeOfMatrixGenerated );
                fprintf(pFile, "%s\t",pidOfClient );
                fprintf(pFile, "%f\n",detOfMatrix );

                perror("h4");

                if (mkfifo(path, 0777) == -1) {
                    if (errno != EEXIST) {
                        fprintf(stderr, "[%ld]:failed to create named pipe %s: %s\n",
                        (long)getpid(), "FIFOFILE", strerror(errno));
                    }
                }
                int size = 2*matrixSize;
                if ((fifowrite = open(path, O_WRONLY /*| O_NONBLOCK */)) < 0)
                    fprintf(stderr, "open error\n" );
                if (write(fifowrite, &size, sizeof(int)) < 0)
                    fprintf(stderr, "write error\n" );
                for(i =0; i<2*matrixSize; ++i)
                    for(j=0; j<2*matrixSize; ++j)
                        if (write(fifowrite, &matrix[i][j], sizeof(double)) < 0)
                            fprintf(stderr, "write error\n" );

                close(fifowrite);
                for(i =0; i<2*matrixSize; ++i){
                    for(j=0; j<2*matrixSize; ++j)
                        fprintf(stderr, "%.2f   ",matrix[i][j] );
                    fprintf(stderr, "\n" );
                }
                fclose(pFile);
            fprintf(stderr, "ÖLDÜM:%d\n",getpid() );
                
                _exit(0);
            }


        break;
        case SIGINT:
            if(serverPid == getpid()){

                time ( &rawtime );
                timeinfo = localtime ( &rawtime );
                char * time = asctime (timeinfo);
                fprintf(pFile, "Control-C was pressed in server. %s \n",time);
                printf("\nControl-C was pressed: mypid = %d, mypgid = %d\n",
                getpid(), getpgid(getpid()));
                for(int i=0; i<countOfSeeWhat; ++i)
                    kill(pidSeeWhat[i],SIGUSR2);
                char fifofile[10];
                char fifofilewithPath[PATH_MAX];
                fclose(pFile);
                fprintf(stderr, "total signal received%d mainfifo:%s\n",count,MAINFIFO );
                unlink(MAINFIFO);
            }
            fprintf(stderr, "ÖLDÜM:%d\n",getpid() );
            _exit(0);
        break;
        case SIGUSR2:

            if(serverPid == getpid()){

                //her clıentın pidsinı 1 kere eklemeıyoz
                for(int i=0; i<countOfSeeWhat; ++i){

                    if(siginfo->si_pid == pidSeeWhat[i])
                        contains = 1;

                }
                if(!contains)
                    pidSeeWhat[countOfSeeWhat++] = siginfo->si_pid;
            }
        break;
        case SIGALRM:
            if(serverPid == getpid()){
                time ( &rawtime );
                timeinfo = localtime ( &rawtime );
                char * time = asctime (timeinfo);
                fprintf(stderr, "byeee\n" );
                fprintf(stderr, "total signal received%d\n",count );
                fprintf(pFile, "Kill signal has received %s\n",time);
                fclose(pFile);
                char fifofile[10];
                char fifofilewithPath[PATH_MAX];
                for(int i=0; i<countOfSeeWhat; ++i)
                    kill(pidSeeWhat[i],SIGUSR2);
                unlink(MAINFIFO);

            }
            fprintf(stderr, "ÖLDÜM:%d\n",getpid() );

            _exit(0);
        break;
    }
    fclose(pFile);

}

void deleteLog(){

    struct dirent *direntp = NULL;
    DIR *dirp = NULL;
    char temp[1024];
    char currentDirectory[1024];
    getcwd(currentDirectory,1024);
    strcat(currentDirectory,"/Log");
    if ((dirp = opendir(currentDirectory)) == NULL) {
        perror ("Failed to open directory");
    }

    while ((direntp = readdir(dirp)) != NULL){

        if (strcmp(direntp->d_name, ".") == 0 || 
            strcmp(direntp->d_name, "..") == 0 || 
            direntp->d_name[strlen(direntp->d_name) - 1] == '~')

            continue;


        if((direntp->d_type) == DT_REG){

            if(strcmp(direntp->d_name,"timeServer.log") == 0){
                strcat(currentDirectory,"/");
                strcat(currentDirectory,direntp->d_name);
                remove(currentDirectory);
            }

        }

            
    }
}

void timeServer(double milliseconds, int n, char * mainpipe){
    int j,i;
    double ** matrix;
    struct sigaction act;
    int count = 0;
    double sum = 0;
    double x;
    int returnSig;
    char path[PATH_MAX] ;
    char temp[PATH_MAX] ;
    int fifowrite;
    sigset_t oset;
    sigset_t sigset;
    act.sa_handler = setdoneflag; /* set up signal handler */
    act.sa_flags = 0;
    pid_t childpid = 0;
    int mypid;
    getcwd(path,PATH_MAX);
    strcat(path,"/");
    strcpy(temp,path);
    strcat(temp,"Log/");
    strcat(temp,mainpipe);
    strcpy(MAINFIFO,temp);
    unlink(temp);
    matrixSize = n;

    serverPid = getpid();
    deleteLog();

    if ((sigemptyset(&act.sa_mask) == -1) ||
    (sigaction(SIGINT, &act, NULL) == -1)) {
    perror("Failed to set SIGINT handler");
        return ;
    }
    struct sigaction new_action, old_action;


    sigset_t signal_set;

    if (gettimeofday(&tpstart, NULL)) {
        fprintf(stderr, "Failed to get start time\n");
    }


/* SIGSEGV will be received here */

    while (!doneflag) {
        sigemptyset(&signal_set);

        sigaddset(&signal_set, SIGUSR1);
        sigaddset(&signal_set, SIGUSR2);
        sigaddset(&signal_set, SIGALRM);

        sigprocmask(SIG_BLOCK, &signal_set, NULL);

        usleep(milliseconds * 1000);
        sigprocmask(SIG_UNBLOCK, &signal_set, NULL);


        if (mkfifo(temp, 0777) == -1) {
            if (errno != EEXIST) {
                fprintf(stderr, "[%ld]:failed to create named pipe %s: %s\n",
                (long)getpid(), "FIFOFILE", strerror(errno));
            }
        }

        mypid = getpid();
        if ((fifowrite= open(temp, O_WRONLY) < 0))
            fprintf(stderr, "open error\n" );
            int writed = write(fifowrite, &mypid, sizeof(int));
            if (DEBUG){
                if (writed < 0)
                    fprintf(stderr, "write error\n" );
                else if(writed == 0)
                    fprintf(stderr, "hiç bisi yazılmadı\n" );
                else
                    fprintf(stderr, "OK NO PROBLEM\n" );
            }
        close(fifowrite);


        new_action.sa_sigaction = HandleSignal;
        sigemptyset (&new_action.sa_mask);
        new_action.sa_flags = SA_SIGINFO;
        sigaction (SIGINT, &new_action , NULL);
        sigaction (SIGUSR1, &new_action,NULL);
        sigaction (SIGUSR2, &new_action,NULL);
        sigaction (SIGALRM, &new_action,NULL);
        
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main(int argc, char** argv) {

    if(argc != 4){
        fprintf(stderr, "Usage error! Please give me <ticks in msec> <size of matrix> <mainpipe> \n" );
        exit(0);
    }

    char* fifo = argv[3];
    double time = atof(argv[1]);
    int size = atoi(argv[2]);
    timeServer(time,size,fifo);

    return (0);
}
