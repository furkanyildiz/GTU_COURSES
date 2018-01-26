#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
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
#define FIFO_PERM (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH |O_WRONLY|O_NONBLOCK)
#define TXT "fifosfile.txt"
#define DEBUG 1
#define _ISOC99_SOURCE
#include <sys/time.h>
#define MILLION 1000000L

int msignal ;
int timeServerPid;
int size ;
struct MatrixInformation{

	int pidOfClient;
	double result1;
	double timeElaps1;
	double result2;
	double timeElaps2;

};

pid_t r_wait(int *stat_loc) {
	int retval;
	while (((retval = wait(stat_loc)) == -1) && (errno == EINTR)) ;
		return retval;
}
void seeWhat(char * mainpipe);
void doConvolution(double matrix[30][30], int size);
void inverse(double matrix[30][30], int size);
void cofactors15(double num[15][15], int f) ;
void trans15(double num[15][15], double fac[15][15], int r) ;
double determinant15(double a[15][15], int k) ;
void convolition(double in[15][15],double out[15][15],int size);
void sig_handler(int signo);
void trans(double num[30][30], double fac[30][30], int r) ;
void InverseMatrix(double num[30][30], int f) ;

void sig_handler(int signo)
{
    msignal = signo;
}

int is =0;
int numOfMatrix = 0;
int showResultPid;
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
    char temp[1024];
    getcwd(path,1024);
    strcat(path,"/Log/");
    sprintf(temp,"%d",getpid());
    strcat(path,temp);
   	switch(sig){
		case SIGUSR2:
            
            strcpy(temp,path);
            strcat(temp,"_results");
            fprintf(stderr, "SILLL:%s\n",temp );
            fprintf(stderr, "SILLL:%s\n",path );
            unlink(temp);
            unlink(path);
            _exit(0);
        break;
        case SIGUSR1:
        	showResultPid = siginfo->si_pid ;
        break;
        case SIGINT:
            strcpy(temp,path);
            strcat(temp,"_results");
            fprintf(stderr, "SILLL:%s\n",temp );
            fprintf(stderr, "SILLL:%s\n",path );
            unlink(path);
            unlink(temp);
            kill(timeServerPid,SIGALRM);
			kill(showResultPid,SIGALRM);
			_exit(0);
		break;
   }
}
int main(int argc, char** argv){
	char* fifo = argv[1];
	
	if(argc != 2){
        fprintf(stderr, "Usage error! Please give me <mainpipe> \n" );
        exit(0);
	}

	seeWhat(fifo);
}
/**
ALINTI
http://easy-learn-c-language.blogspot.com.tr/2013/02/numerical-methods-determinant-of-nxn.html
*/
double determinant(double  matrix[30][30],int n)
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


void seeWhat(char * mainpipe){
	char path[1024];
	char temp[1024];
	int fiforead;
    struct sigaction new_action, old_action;
    FILE * pFile;
    char filename[1024];
    int childpid1;
    int childpid2;
    char pid[10];
    sprintf(pid,"%d",getpid());


	while(1){
		strcpy(filename,"Log/seeWhat_");
		//strcat(filename,pid);
		//strcat(filename,"_");
		++is;
		getcwd(path,PATH_MAX);
		
		strcat(path,"/Log/");
		strcpy(temp,path);
		strcat(temp,mainpipe);
		//unlink(temp);
		// prepare sigaction

	    new_action.sa_sigaction = HandleSignal;
	    sigemptyset (&new_action.sa_mask);
	    new_action.sa_flags = SA_SIGINFO;
	    sigaction (SIGUSR2, &new_action , NULL);
	    sigaction (SIGINT, &new_action , NULL);
	    sigaction (SIGUSR1, &new_action , NULL);


	    fprintf(stderr, "seeWhatpid::%d, okunacak:%s\n", getpid(),temp);
	    if ((fiforead =  open(temp, O_RDONLY)) < 0){
	    	fprintf(stderr, "First you have to run server!\n" );
	    	exit(1);
	    }
	    int r = read(fiforead, &timeServerPid, sizeof(int));
	    if ( r <= 0)
	        fprintf(stderr, "read error\n" );


	    fprintf(stderr, "timeServerPid%d\n",timeServerPid);
	    //Time server'a seeWhat'ın pid'sini öğretmek için sinyal yolluyoruz
		kill(timeServerPid,SIGUSR2);
		//Time server'a matrix üretmesi için sinyal yolluyoruz.
		kill(timeServerPid,SIGUSR1);

	    char pidOfClient[10];
	    fprintf(stderr, "close:::::\n" );

	    //fiforead'i kapatınca calısmıyorr
	    
		sprintf(pidOfClient,"%d",getpid());
		strcat(path,pidOfClient);
		unlink(path);

	    int fiforead2;

	    while (((fiforead2 = open(path, O_RDONLY) ) == -1) && ((errno == ENOENT) || (errno == EADDRINUSE) || (errno == EBADF)  || (errno = EINTR) 
	    || errno == EMFILE || errno == ENFILE || errno == ENOBUFS || errno ==  EPIPE   || errno == ESTRPIPE ));




	    int result;
	    if((result = read(fiforead2, &size, sizeof(int))  ) <= 0)
	    	perror("size okumada hata");

	    double matrix[30][30];



	    int num,i,j;

	  	for(i =0; i<size; ++i)
	        for(j=0; j<size; ++j){
	        	result = read(fiforead2, &matrix[i][j], sizeof(double));
	        	if(result <= 0)
	        		fprintf(stderr, "okuma error\n" );
	        }
        close(fiforead2);
		  unlink(path);
	    for(i =0; i<size; ++i){
	        for(j=0; j<size; ++j)
	            fprintf(stderr, "%.2f   ",matrix[i][j] );
	        fprintf(stderr, "\n" );
    	}
    	char matrixnum[100000];
    	sprintf(matrixnum,"%d",numOfMatrix);
    	strcat(filename,matrixnum);
    	strcat(filename,".log");
    	fprintf(stderr, "filename:%s\n",filename );
    	pFile = fopen (filename, "a+");
        fprintf(pFile, "orijinal = [");

   		for(i =0; i<size; ++i){

	        for(j=0; j<size; ++j){
	        	if(j == size-1)
	            	fprintf(pFile, "%.3f",matrix[i][j] );
	            else
	            	fprintf(pFile, "%.3f ",matrix[i][j] );
	        }
        	if(i != size-1)
        		fprintf(pFile, ";");
    	}
        fprintf(pFile, "]\n");
        fclose(pFile);
    	double InversedMatrix[30][30] ;
    	double ConvolutedMatrix[30][30] ;

    	for(i =0; i<size; ++i){
	        for(j=0; j<size; ++j){
                InversedMatrix[i][j] = matrix[i][j];
                ConvolutedMatrix[i][j] = matrix[i][j];
	        }
	    }

		struct MatrixInformation createdMatrix;
		createdMatrix.pidOfClient = getpid();


	    int fdp[2];
	    int pid;
	    if(pipe(fdp)<0)
	    	fprintf(stderr, "pipe error\n" );
    	childpid1 = fork();
    	if(childpid1 == 0){

    		//Do Inverse operatıon
    		inverse(InversedMatrix,size);
	    	fprintf(stderr, "filename:%s\n",filename );
    		pFile = fopen (filename, "a+");
            long timedif;
			struct timeval tpend;
			struct timeval tpstart;
	        fprintf(pFile, "Inversed = [");

	   		for(i =0; i<size; ++i){

		        for(j=0; j<size; ++j){
		        	if(j == size-1)
		            	fprintf(pFile, "%.3f",InversedMatrix[i][j] );
		            else
		            	fprintf(pFile, "%.3f ",InversedMatrix[i][j] );
		        }
	        	if(i != size-1)
	        		fprintf(pFile, ";");
	    	}
	        fprintf(pFile, "]\n");
	        fclose(pFile);
	        if (gettimeofday(&tpstart, NULL)) {
				fprintf(stderr, "Failed to get start time\n");
            }
   			double result1 = determinant(matrix,size) - determinant(InversedMatrix,size);
   			fprintf(stderr, "rrrrrr1:%f   size:%d\n",result1,size );
   			fprintf(stderr, "dddmm1:%f\n",determinant(matrix,size) );
   			fprintf(stderr, "dddııı1:%f\n", determinant(InversedMatrix,size) );
			if (gettimeofday(&tpend, NULL)) {
				fprintf(stderr, "Failed to get end time\n");
			}
			timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
			tpend.tv_usec - tpstart.tv_usec;
        	//double timeElaps1 = (double)((toc - tic) / CLOCKS_PER_SEC)/1000;
        	double timeElaps1 =  (double)timedif / 1000.0;
        	//clock_t toc = clock();
        	//double timeElaps1 = (double)(toc - tic) / CLOCKS_PER_SEC;
   			fprintf(stderr, "ttttt1:%f\n",timeElaps1 );

    		close(fdp[0]);
    		write(fdp[1],&result1,sizeof(double));
    		write(fdp[1],&timeElaps1,sizeof(double));
    		close(fdp[1]);
	        break;	

    	}
		while(r_wait(NULL) > 0);
    	if(childpid1 > 0){

			close(fdp[1]);
			read(fdp[0],&createdMatrix.result1,sizeof(double));
			read(fdp[0],&createdMatrix.timeElaps1,sizeof(double));
			close(fdp[0]);
		}

    	if(childpid1 == 0)
			exit(0);
		  perror("1.fork");
	    fprintf(stderr, "1.fork%d\n",childpid1 );

    	if(childpid1>0){
		    int fdp[2];
		    int pid;
		    if(pipe(fdp)<0)
		    	fprintf(stderr, "pipe error\n" );
		    perror("2.fork öncesi");
    		childpid2 = fork();
		    fprintf(stderr, "2.fork%d\n",childpid2 );

    		if(childpid2 == 0){

    			//do 2d convolutıon operatıon 
    			doConvolution(ConvolutedMatrix,size);
    			pFile = fopen (filename, "a+");


		        fprintf(pFile, "2dConverted = [");

		   		for(i =0; i<size; ++i){

			        for(j=0; j<size; ++j){
			        	if(j == size-1)
			            	fprintf(pFile, "%.3f",ConvolutedMatrix[i][j] );
			            else
			            	fprintf(pFile, "%.3f ",ConvolutedMatrix[i][j] );
			        }
		        	if(i != size-1)
		        		fprintf(pFile, ";");
			    	}
		        fprintf(pFile, "]\n");
		        fclose(pFile);
		        long timedif;
				struct timeval tpend;
				struct timeval tpstart;
		        if (gettimeofday(&tpstart, NULL)) {
					fprintf(stderr, "Failed to get start time\n");
				}
	   			double result2 = determinant(matrix,size) - determinant(ConvolutedMatrix,size);

				if (gettimeofday(&tpend, NULL)) {
					fprintf(stderr, "Failed to get end time\n");
				}
				timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
				tpend.tv_usec - tpstart.tv_usec;
	        	double timeElaps2 =  (double)timedif / 1000.0;
	    		close(fdp[0]);
	    		write(fdp[1],&result2,sizeof(double));
	    		write(fdp[1],&timeElaps2,sizeof(double));
	    		close(fdp[1]);
	    		break;
    		}
			while(r_wait(NULL) > 0);

	    	if(childpid2 > 0){

				close(fdp[1]);
				read(fdp[0],&createdMatrix.result2,sizeof(double));
				read(fdp[0],&createdMatrix.timeElaps2,sizeof(double));
				close(fdp[0]);
			}

	    	if(childpid2 == 0)
				exit(0);

    	}
		
    	numOfMatrix++;

    	// FILL THE STRUCT

    	fprintf(stderr, "r1:%f\n", createdMatrix.result1);
    	fprintf(stderr, "t1:%f\n", createdMatrix.timeElaps1);
    	fprintf(stderr, "r2:%f\n", createdMatrix.result2);
    	fprintf(stderr, "t2:%f\n", createdMatrix.timeElaps2);
    	
        //WRITE THE STRCUT TO FIFO
        strcat(path,"_results");
        fprintf(stderr, "shwrslt icin path:%s\n",path );
        if (mkfifo(path, 0777) == -1) {
            if (errno != EEXIST) {
                fprintf(stderr, "[%ld]:failed to create named pipe %s: %s\n",
                (long)getpid(), "FIFOFILE", strerror(errno));
            }
        }
        int fifowrite;
        if ((fifowrite = open(path, O_RDWR)) < 0)
            fprintf(stderr, "open error\n" );
        if (write(fifowrite, &createdMatrix, sizeof(createdMatrix)) < 0)
            fprintf(stderr, "write error\n" );

        close(fifowrite);
        
	}
}
/**
	Matris işlemleri trans-inverse-convolution-determinant internetten alınmıştır.
*/
void trans(double num[30][30], double fac[30][30], int r) {
 
  int i, j;
  double b[30][30], inv[30][30], d;
 
  for (i = 0; i < r; i++) {
 
    for (j = 0; j < r; j++) {
 
      b[i][j] = fac[j][i];
 
    }
 
  }
 
  d = determinant(num, r);
 
  inv[i][j] = 0;
 
  for (i = 0; i < r; i++) {
 
    for (j = 0; j < r; j++) {
 
      inv[i][j] = b[i][j] / d;
 
    }
 
  }
 
 
  for (i = 0; i < r; i++) 
 
    for (j = 0; j < r; j++) 
 
      num[i][j] = inv[i][j];
 
 
}

void InverseMatrix(double num[30][30], int f) {
 
  double b[30][30], fac[30][30];
 int p, q, m, n, i, j;
 
  for (q = 0; q < f; q++) {
 
    for (p = 0; p < f; p++) {
 
      m = 0;
 
      n = 0;
 
      for (i = 0; i < f; i++) {
 
        for (j = 0; j < f; j++) {
 
          b[i][j] = 0;
 
          if (i != q && j != p) {
 
            b[m][n] = num[i][j];
 
            if (n < (f - 2))
 
                   n++; else {
 
              n = 0;
 
              m++;
 
            }
 
          }
 
        }
 
      }
 
      fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
 
    }
 
  }
 
	trans(num, fac, f);
 
}


// Matixin 4 e bölunmus halıyle ıslem yapmak ıcın yazılan fonksıyonlar

void cofactors(double num[30][30], int f) {
 
  double b[30][30], fac[30][30];
 int p, q, m, n, i, j;
 
  for (q = 0; q < f; q++) {
 
    for (p = 0; p < f; p++) {
 
      m = 0;
 
      n = 0;
 
      for (i = 0; i < f; i++) {
 
        for (j = 0; j < f; j++) {
 
          b[i][j] = 0;
 
          if (i != q && j != p) {
 
            b[m][n] = num[i][j];
 
            if (n < (f - 2))
 
                   n++; else {
 
              n = 0;
 
              m++;
 
            }
 
          }
 
        }
 
      }
 
      fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
 
    }
 
  }
 
  trans(num, fac, f);
 
}
///////////////////15lıkler///////////////////
/**
http://easy-learn-c-language.blogspot.com.tr/2013/02/numerical-methods-determinant-of-nxn.html
*/
double determinant15(double  matrix[15][15],int n)
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

void trans15(double num[15][15], double fac[15][15], int r) {
 
  int i, j;
  double b[15][15], inv[15][15], d;
 
  for (i = 0; i < r; i++) {
 
    for (j = 0; j < r; j++) {
 
      b[i][j] = fac[j][i];
 
    }
 
  }
 
  d = determinant15(num, r);
 
  inv[i][j] = 0;
 
  for (i = 0; i < r; i++) {
 
    for (j = 0; j < r; j++) {
 
      inv[i][j] = b[i][j] / d;
 
    }
 
  }
 

  for (i = 0; i < r; i++) 
 
    for (j = 0; j < r; j++) 
 
      num[i][j] = inv[i][j];
 
}
void cofactors15(double num[15][15], int f) {
 
  double b[15][15], fac[15][15];
 int p, q, m, n, i, j;
 
  for (q = 0; q < f; q++) {
 
    for (p = 0; p < f; p++) {
 
      m = 0;
 
      n = 0;
 
      for (i = 0; i < f; i++) {
 
        for (j = 0; j < f; j++) {
 
          b[i][j] = 0;
 
          if (i != q && j != p) {
 
            b[m][n] = num[i][j];
 
            if (n < (f - 2))
 
                   n++; else {
 
              n = 0;
 
              m++;
 
            }
 
          }
 
        }
 
      }
 
      fac[q][p] = pow(-1, q + p) * determinant15(b, f - 1);
 
    }
 
  }
 
  trans15(num, fac, f);
 
}
///////////////////////////////////////



void inverse(double matrix[30][30], int size){


  double m1[15][15],m2[15][15],m3[15][15],m4[15][15];

    int i;
    for(i=0; i<size/2; ++i){

        int k=0;
        for(int j=0; j<size; ++j){

            if( j<size/2)
                m1[i][j] = matrix[i][j];
            else
                m2[i][k++] = matrix[i][j];
        }
    }
    int m = 0;
    for(; i<size; ++i){
        int k=0;
        int y=0;
        for(int j=0; j<size; ++j){


            if( j<size/2)
                m3[m][j] = matrix[i][j];
            else
                m4[m][k++] = matrix[i][j];

        }
        m++;

    }

  cofactors15(m1,size/2);
  cofactors15(m2,size/2);
  cofactors15(m3,size/2);
  cofactors15(m4,size/2);

    int n=0;
    int k=0;
    int l=0;
  for(int i=0; i<size; ++i){

    int m=0;
    for(int j=0; j<size; ++j){


      if(j<size/2 && i<size/2)
        matrix[i][j] = m1[i][j];
      
      else if(j>= size/2 && i<size/2)
        matrix[i][j] = m2[i][m++];

      else if(j<size/2 && i>=size/2){

        matrix[i][j] = m3[n][j];

        if(j == size/2 -1)
          ++n;

      }

      else if(j>=size/2 && i>=size/2){

        matrix[i][j] = m4[k][l++];

        if(l == size/2){
          ++k;
          l=0;
        }
      }


    }

  }
}
/**
	Alıntı:	http://www.songho.ca/dsp/convolution/convolution.html
*/
void convolition(double in[15][15],double out[15][15],int size){

  double kernel[3][3] = {{0.0,0.0,0.0},{0.0,1.0,0.0}, {0.0,0.0,0.0}};
  int kCols =3;
  int kRows =3;
  int rows = size;
  int cols = size;
  // find center position of kernel (half of kernel size)
  int kCenterX = kCols / 2;
  int kCenterY = kRows / 2;
  int mm,nn,ii,jj;
  for(int i=0; i < rows; ++i)              // rows
  {
    for(int j=0; j < cols; ++j)          // columns
    {
      for(int m=0; m < kRows; ++m)     // kernel rows
      {
        mm = kRows - 1 - m;      // row index of flipped kernel

        for(int n=0; n < kCols; ++n) // kernel columns
        {
          nn = kCols - 1 - n;  // column index of flipped kernel

          // index of input signal, used for checking boundary
          ii = i + (m - kCenterY);
          jj = j + (n - kCenterX);

          // ignore input samples which are out of bound
          if( ii >= 0 && ii < rows && jj >= 0 && jj < cols ){
              out[i][j] += in[ii][jj] * kernel[mm][nn];

          }
        }
      }
    }
	}

}


void doConvolution(double matrix[30][30], int size){


  double m1[15][15],m2[15][15],m3[15][15],m4[15][15];
  double o1[15][15],o2[15][15],o3[15][15],o4[15][15];

  for(int i=0; i<15; ++i){
  	for(int j=0; j<15; ++j){
  		o1[i][j] = 0.0;
  		o2[i][j] = 0.0;
  		o3[i][j] = 0.0;
  		o4[i][j] = 0.0;

  	}
  }

	int i;
  for(i=0; i<size/2; ++i){

    int k=0;
    for(int j=0; j<size; ++j)

      if( j<size/2)
        m1[i][j] = matrix[i][j];
      else
        m2[i][k++] = matrix[i][j];
  }
  int m = 0;
  for(; i<size; ++i){
    int k=0;
    int y=0;
    for(int j=0; j<size; ++j){


      if( j<size/2)
        m3[m][j] = matrix[i][j];
      else
        m4[m][k++] = matrix[i][j];

    }
      m++;

  }

  convolition(m1,o1,size/2);
  convolition(m2,o2,size/2);
  convolition(m3,o3,size/2);
  convolition(m4,o4,size/2);


    int n=0;
    int k=0;
    int l=0;
  for(int i=0; i<size; ++i){

    int m=0;
    for(int j=0; j<size; ++j){


      if(j<size/2 && i<size/2)
        matrix[i][j] = o1[i][j];
      
      else if(j>= size/2 && i<size/2)
        matrix[i][j] = o2[i][m++];

      else if(j<size/2 && i>=size/2){

        matrix[i][j] = o3[n][j];

        if(j == size/2 -1)
          ++n;

      }

      else if(j>=size/2 && i>=size/2){

        matrix[i][j] = o4[k][l++];

        if(l == size/2){
          ++k;
          l=0;
        }
      }
    }
  }
}