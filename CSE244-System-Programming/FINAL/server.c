#define DEBUG 0
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
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
#define PERM (S_IRUSR | S_IWUSR)
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
int mainpid;
int *newsock;
sem_t semlock;
sem_t semlock2;
int sockfd;
pthread_t* tids;
int size = 0;
pthread_mutex_t server_lock = PTHREAD_MUTEX_INITIALIZER;
int pool_size;

typedef struct{
	double **a;
	double **b;
	int p; //number of row
	int m; //number of col
	double *x[3];
}Informations;
/*
typedef struct{
	double matrix[100][100];
	double b[100][100];

}Matrixs;
*/
typedef struct{
	double *a;
	double *b;
	double *x[3];
	int p; //number of row
	int m; //number of col
	int flag;
}Solve;


typedef struct{
	double *matrix;
	double *b;
	int flag;

}Matrixs;

void createMatrix(double **matrix, int row,int column){
  	int i ,j ;
    srand(time(NULL));
	fprintf(stderr, "create matrixxxxxxxxxxxx row:%d col%d\n",row,column );

    for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			matrix[i][j] =  rand() %10000 -50;

	fprintf(stderr, "created matrix\n" );

}
void createMatrixx(double matrix[][100], int row,int column){
  	int i ,j ;
    srand(time(NULL));
	fprintf(stderr, "create matrixxxxxxxxxxxx row:%d col%d\n",row,column );

    for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			matrix[i][j] =  rand() %10000 -50;

	fprintf(stderr, "created matrix\n" );

}
void createMatrixxx(double *matrix, int row,int column){
  	int i ,j ;
    srand(time(NULL));

    for(i=0;i<row*column;i++)
		matrix[i] =  rand() %1000 -50;
}

double determinant(double **matrix,int n)
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
void getCofactor(double **A, double **temp, int p, int q, int n)
{
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 // Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(double **A,double **adj, int size)
{
    if (size == 1)
    {
        adj[0][0] = 1;
        return;
    }
 
    // temp is used to store cofactors of A[][]
    double sign = 1;
    double **temp = (double **)malloc(size*sizeof(double *));
	for (int j=0;j<size;j++)
		temp[j] = (double *)malloc( size *sizeof(double));;
 
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size; j++)
        {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, size);
 
            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;
 
            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(determinant(temp, size-1));
        }
    }
	for(int i=0; i<size; ++i)
		free(temp[i]);
    free(temp);
}
 


// Function to calculate and store inverse, returns false if
// matrix is singular
int inverse(double **A, double **inverse, int size)
{
    // Find determinant of A[][]

    double det = determinant(A, size);
    if (det == 0)
    {
        return 0;
    }
 
    // Find adjoint
    double **adj = (double **)malloc(size*sizeof(double *));
	for (int j=0;j<size;j++)
		adj[j] = (double *)malloc( size *sizeof(double));
    adjoint(A, adj,size);

    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<size; i++)
        for (int j=0; j<size; j++)
            inverse[i][j] = adj[i][j]/(double)(det);
	for(int i=0; i<size; ++i)
		free(adj[i]);
 	free(adj);


    return 1;
}
/*
   Transpose of a square matrix, do it in place
*/
void transpose(double** A, double** B, int row,int col)
{
    int i, j;
    for (i = 0; i < col; i++)
        for (j = 0; j < row; j++)
            B[i][j] = A[j][i];
        
}

// a*b = c
void multipication(double** a, double **b, double** c, int row, int col){
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < row; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < col; k++)
            {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
}


void multipication2(double** a, double **b, double** c, int row1, int row2, int col1, int col2){
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < row2; k++)
            {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
}
void subtraction(double**a, double **b,double **c,int row, int col){
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			c[i][j]=a[i][j]-b[i][j];
}
double** foo(Informations matrixs)
{


	double ** transposeOfA = (double **)malloc(matrixs.m*sizeof(double *));
	for (int j=0;j<matrixs.m;j++)
		transposeOfA[j] = (double *)malloc( matrixs.p *sizeof(double));

	double ** AmultAT = (double **)malloc(matrixs.m*sizeof(double *));
	for (int j=0;j<matrixs.m;j++)
		AmultAT[j] = (double *)malloc( matrixs.m *sizeof(double));

	double ** inverseAmultAT = (double **)malloc(matrixs.m*sizeof(double *));
	for (int j=0;j<matrixs.m;j++)
		inverseAmultAT[j] = (double *)malloc( matrixs.m *sizeof(double));

	double ** result = (double **)malloc(matrixs.m*sizeof(double *));
	for (int j=0;j<matrixs.m;j++)
		result[j] = (double *)malloc( matrixs.p *sizeof(double));
	double ** result2 = (double **)malloc(matrixs.m*sizeof(double *));
	for (int j=0;j<matrixs.m;j++)
		result2[j] = (double *)malloc( 1 *sizeof(double));

	transpose(matrixs.a, transposeOfA,matrixs.p,matrixs.m);

	multipication(transposeOfA, matrixs.a,AmultAT,matrixs.m,matrixs.p);

	inverse(AmultAT,inverseAmultAT,matrixs.m);
	multipication2(inverseAmultAT, transposeOfA,result, matrixs.m, matrixs.m,matrixs.m, matrixs.p);

	multipication2(result, matrixs.b,result2,matrixs.m,matrixs.p,matrixs.p,1);

	if(DEBUG){

		fprintf(stderr, "üretilen çözüm psude ile:\n" );

		for(int i=0; i<matrixs.m; ++i){
			for(int j=0; j<1; ++j)
				printf("%f  ",result2[i][j] );
			printf("\n");
		}
	}

	for(int i=0; i<matrixs.m; ++i)
		free(transposeOfA[i]);
	free(transposeOfA);

	for(int i=0; i<matrixs.m; ++i)
		free(AmultAT[i]);
	free(AmultAT);

	for(int i=0; i<matrixs.m; ++i)
		free(inverseAmultAT[i]);
	free(inverseAmultAT);

	for(int i=0; i<matrixs.m; ++i)
		free(result[i]);
	free(result);

	return result2;

}

// thread function.
void* pseudo_inverse(void * arg){

	Informations *matrixs = (Informations *)arg;
	double** x2 = foo(*matrixs);

	//double *x = malloc(sizeof(double)*matrixs->m);
	matrixs->x[0] = malloc(sizeof(double)*matrixs->p);

	for(int i=0; i<matrixs->m; ++i)
		matrixs->x[0][i] = x2[i][0];

	for(int i=0; i<matrixs->m; ++i)
		free(x2[i]);
	free(x2);
	//return x;
}

void* SVD(void * arg){

	Informations *matrixs = ((Informations *)arg);
	double** x2 = foo(*matrixs);
	matrixs->x[1] = malloc(sizeof(double)*matrixs->p);

	double *x = malloc(sizeof(double)*matrixs->m);
	for(int i=0; i<matrixs->m; ++i)
		matrixs->x[1][i] = x2[i][0];

	for(int i=0; i<matrixs->m; ++i)
		free(x2[i]);
	free(x2);
	return x;
}

void* QR(void * arg){


	Informations* matrixs = ((Informations *)arg);
	double** x2 = foo(*matrixs);
	matrixs->x[2] = malloc(sizeof(double)*matrixs->p);

	double *x = malloc(sizeof(double)*matrixs->m);
	for(int i=0; i<matrixs->m; ++i)
		matrixs->x[2][i] = x2[i][0];

	for(int i=0; i<matrixs->m; ++i)
		free(x2[i]);
	free(x2);
	return x;
	

}

int detachandremove(int shmid, void *shmaddr) {
int error = 0;
if (shmdt(shmaddr) == -1)
	error = errno;
if ((shmctl(shmid, IPC_RMID, NULL) == -1) && !error)
	error = errno;
if (!error)
	return 0;
errno = error;
return -1;
}

void doprocessing (int sock) {
   int n;
   char buffer[256];
   bzero(buffer,256);

	n = read(sock,buffer,255);

   char * num1 = strtok(buffer, " ");
   char * num2 = strtok(NULL, " ") ;

   int m = atoi(num1);
   int p = atoi(num2);
   if(DEBUG)
   	fprintf(stderr, "n1: %s  n2: %s  m:%d p:%d\n",num1,num2,m,p );

	if (n < 0) {
		perror("ERROR reading from socket");
		exit(1);
	}
   


	int shid;
	int key = pthread_self();
	int size_maxtix_a = sizeof(double)*m*p;
	int size_maxtix_b = sizeof(double)*p;
	shid = shmget(key, sizeof(Matrixs)+size_maxtix_a+size_maxtix_b, PERM | IPC_CREAT | IPC_EXCL);
	void *ptr =  shmat(shid, NULL, 0);

	Matrixs * matrixs = ptr;


	matrixs->matrix = (ptr + sizeof(Matrixs));
	matrixs->b = (ptr + sizeof(Matrixs) + size_maxtix_a );
	matrixs->flag = 0;


	key = pthread_self()+2;
	size_maxtix_a = sizeof(double)*m*p;
	size_maxtix_b = sizeof(double)*p;
	int size_maxtix_x = sizeof(double)*p*3;
	int shid2 = shmget(key, sizeof(Solve)+size_maxtix_a+size_maxtix_b+size_maxtix_x, PERM | IPC_CREAT | IPC_EXCL);
	void *ptr2 =  shmat(shid2, NULL, 0);

	Solve * solved = ptr2;


	solved->a = (ptr2 + sizeof(Solve));
	solved->b = (ptr2 + sizeof(Solve) + size_maxtix_a );
	solved->x[0] = (ptr2 + sizeof(Solve) + size_maxtix_a + size_maxtix_b  );
	solved->x[1] = (ptr2 + sizeof(Solve) + size_maxtix_a + size_maxtix_b + sizeof(double)  );
	solved->x[2] = (ptr2 + sizeof(Solve) + size_maxtix_a + size_maxtix_b + 2*sizeof(double) );
	solved->flag = 0;


	int p1,p2,p3;
	p1 = fork();
	if(p1<0)
		fprintf(stderr, "fork error\n" );
	if(p1>0){ //main process
		p2 = fork();
		if(p2<0)
			fprintf(stderr, "fork error\n" );
		if(p2>0){ // main process
			p3 = fork();
			if(p3<0)
				fprintf(stderr, "fork error\n" );
		}
	}
	if(DEBUG)
		fprintf(stderr, "p2 pid:%d\n",p2 );

	if(p1 == 0){ //generate
	 	pthread_mutex_lock(&server_lock);
		createMatrixxx(matrixs->matrix,p,m);

		createMatrixxx(matrixs->b,p,1);
		matrixs->flag = 1;
	
		for(int i=0; i<p*m; ++i){
			n = write(sock,&(matrixs->matrix[i]),sizeof(double));
			if(DEBUG)
				printf("p1 m::%f  ",matrixs->matrix[i] );
		}
		for(int i=0; i<p*1; ++i){
			n = write(sock,&(matrixs->b[i]),sizeof(double));
			if(DEBUG)
				printf("p2 bbbbbb:%f  ",matrixs->b[i] );
		}

		pthread_mutex_unlock(&server_lock);
	}
	if(p2 == 0){ //solve
	 	pthread_mutex_lock(&server_lock);
		while(matrixs->flag == 1){
			if(DEBUG){
				fprintf(stderr, "p22222222222222222222222222222222:%d p:%d   m:%d\n",getpid(),p,m );


				for(int i=0; i<p*m; ++i){
					fprintf(stderr,"p2:%f  ",matrixs->matrix[i] );
				}
				printf("b matrixi in p2:\n");
				for(int i=0; i<p*1; ++i){
					fprintf(stderr,"p2:%f  ",matrixs->b[i] );
				}
			}

			double ** A = (double **)calloc(p,sizeof(double *));
			for (int j=0;j<p;j++)
				A[j] = (double *)calloc(m,sizeof(double));

			double ** B = (double **)calloc(p,sizeof(double *));
			for (int j=0;j<p;j++)
				B[j] = (double *)calloc(1,sizeof(double));

			int f = 0;
			// 2 boyutlu matrixe çaviriliyor shared memoryden okunan datalar.
			for(int i=0; i<p; ++i){
				for(int j=0; j<m; ++j){
					A[i][j] = matrixs->matrix[f++];
				}
			}
			solved->p = p;
			solved->m = m;

			for(int i=0;i<p*m; ++i)
				solved->a[i] = matrixs->matrix[i];

			for(int i=0;i<p; ++i)
				solved->b[i] = matrixs->b[i];


			f = 0;
			for(int i=0; i<p; ++i){
				for(int j=0; j<1; ++j){
					B[i][j] = matrixs->b[f++];
				}
			}

			matrixs->flag = 0;


			if(DEBUG){
				fprintf(stderr, "AAAAAAAAA:\n" );
				for(int i=0; i<p; ++i){
					for(int j=0; j<m; ++j){
						fprintf(stderr, "A:%f ",A[i][j] );
						
					}
					fprintf(stderr, "\n" );
				}
					fprintf(stderr, "\n" );

				fprintf(stderr, "BBBBBBBBBBb:\n" );
				for(int i=0; i<p; ++i){
					for(int j=0; j<1; ++j){
						fprintf(stderr, "B:%f ",B[i][j] );
						
					}
					fprintf(stderr, "\n" );
				}
					fprintf(stderr, "\n" );

			}


			pthread_t tidss[3];

			Informations *infoptr = (Informations *)malloc(sizeof(Informations ));
			infoptr->a = A;
			infoptr->b = B;
			infoptr->p = p;
			infoptr->m = m;

			pthread_create(&tidss[0], NULL, pseudo_inverse,infoptr);
			pthread_create(&tidss[1], NULL, QR,infoptr);
			pthread_create(&tidss[2], NULL, SVD,infoptr);
			pthread_join(tidss[0],NULL);
			pthread_join(tidss[1],NULL);
			pthread_join(tidss[2],NULL);
			if(DEBUG){
				for(int i=0; i<m; ++i)
					fprintf(stderr,"x:::%f ",infoptr->x[0][i]);
				for(int i=0; i<m; ++i)
					fprintf(stderr,"x2:::%f ",infoptr->x[1][i]);
				for(int i=0; i<m; ++i)
					fprintf(stderr,"x3:::%f ",infoptr->x[2][i]);
			}

			for(int i=0;i<m; ++i)
				solved->x[0][i] = infoptr->x[0][i];
			for(int i=0;i<m; ++i)
				solved->x[1][i] = infoptr->x[1][i];
			for(int i=0;i<m; ++i)
				solved->x[2][i] = infoptr->x[2][i];


			FILE *fp;
			char  a[100];
			sprintf(a, "%d", getpid());
			char  b[100];
			sprintf(b, "%ld", pthread_self());
			char c[1024];
			strcat(c,"Logs/server_");
			strcat(c,a);
			strcat(c,"_");
			strcat(c,b);
			strcat(c,".log");
			fp = fopen(c, "a+");
		    fprintf(fp, "A = [");

				for(int i =0; i<p; ++i){

		        for(int j=0; j<m; ++j){
		        	if(j == m-1)
		            	fprintf(fp, "%.3f",A[i][j] );
		            else
		            	fprintf(fp, "%.3f ",A[i][j] );
		        }
		    	if(i != p-1)
		    		fprintf(fp, ";");
			}
		    fprintf(fp, "]\n");

		    fprintf(fp, "B= [");

				for(int i =0; i<p; ++i){

		        	fprintf(fp, "%.3f ",B[i][0] );
		        	if(i!=p-1)
		    			fprintf(fp, ";");
			}
		    fprintf(fp, "]\n");

		    fprintf(fp, "x1= [");

				for(int i =0; i<m; ++i){

		        	fprintf(fp, "%.3f ",infoptr->x[0][i] );
		        	if(i!=m-1)
		    			fprintf(fp, ";");
			}
		    fprintf(fp, "]\n");

		    fprintf(fp, "x2= [");

				for(int i =0; i<m; ++i){

		        	fprintf(fp, "%.3f ",infoptr->x[1][i] );
		        	if(i!=m-1)
		    			fprintf(fp, ";");
			}
		    fprintf(fp, "]\n");


		    fprintf(fp, "x3= [");

				for(int i =0; i<m; ++i){

		        	fprintf(fp, "%.3f ",infoptr->x[2][i] );
		        	if(i!=m-1)
		    			fprintf(fp, ";");
			}
		    fprintf(fp, "]\n");

			fclose(fp);



			//QR(infoptr);
	/*
			for(int i=0; i<m; ++i)
				fprintf(stderr, "x:%f\n",x[i] );
	*/
			//foo(info);
			solved->flag = 1;

			if(DEBUG)
				fprintf(stderr, "--------------------------------------------------------------FOO SONLANDI:%d\n",getpid() );


			for(int i=0; i<p; ++i)
				free(A[i]);
			free(A);
			if(DEBUG)
				fprintf(stderr, " matrix A  free edildi. \n" );
		

			for(int i=0; i<p; ++i)
				free(B[i]);
			free(B);

			if(DEBUG)
				fprintf(stderr, "matrix B free edildi.\n" );
	

		}
		pthread_mutex_unlock(&server_lock);

	}

	if(p3 == 0){ //verify
		if(DEBUG)
			fprintf(stderr, "p3:%d\n" ,getpid());
		while(solved->flag == 1){
			double ** A = (double **)calloc(p,sizeof(double *));
			for (int j=0;j<p;j++)
				A[j] = (double *)calloc(m,sizeof(double));

			double ** B = (double **)calloc(p,sizeof(double *));
			for (int j=0;j<p;j++)
				B[j] = (double *)calloc(1,sizeof(double));



			int f = 0;
			// 2 boyutlu matrixe çaviriliyor shared memoryden okunan datalar.
			for(int i=0; i<p; ++i){
				for(int j=0; j<m; ++j){
					A[i][j] = solved->a[f++];
				}
			}
			 f = 0;
			for(int i=0; i<p; ++i){
				B[i][0] = solved->b[f++];
			}
		if(DEBUG){
			fprintf(stderr, "//////////////////////////////////////AAAAAAAAA p3:\n" );
			for(int i=0; i<p; ++i){
				for(int j=0; j<m; ++j){
					fprintf(stderr, "%f ",A[i][j] );
					
				}
				fprintf(stderr, "\n" );
			}
			fprintf(stderr, "\n" );
			fprintf(stderr, "//////////////////////////////////////BBBBBBBBB p3:\n" );
			for(int i=0; i<p; ++i){
				for(int j=0; j<1; ++j){
					fprintf(stderr, "%f ",B[i][j] );
					
				}
				fprintf(stderr, "\n" );
			}
			fprintf(stderr, "\n" );
			fprintf(stderr, "//////////////////////////////////////BBBBBBBBB p3x:\n" );

			for(int i=0;i<m; ++i)
				fprintf(stderr,"p3 x:%f ",solved->x[0][i]);

		}
			solved->flag = 0;

			double ** x1 = (double **)malloc(m*sizeof(double *));
			for (int j=0;j<m;j++)
				x1[j] = (double *)malloc(1*sizeof(double));
			


			double ** x2 = (double **)calloc(m,sizeof(double *));
			for (int j=0;j<m;j++)
				x2[j] = (double *)calloc(1,sizeof(double));



			double ** x3 = (double **)calloc(m,sizeof(double *));
			for (int j=0;j<m;j++)
				x3[j] = (double *)calloc(1,sizeof(double));

	

			double ** r1 = (double **)malloc(p*sizeof(double *));
			for (int j=0;j<p;j++)
				r1[j] = (double *)malloc(1*sizeof(double));



			double ** e1 = (double **)malloc(p*sizeof(double *));
			for (int j=0;j<p;j++)
				e1[j] = (double *)malloc(1*sizeof(double));


			double ** transposeOfe = (double **)malloc(1*sizeof(double *));
			for (int j=0;j<1;j++)
				transposeOfe[j] = (double *)malloc(p*sizeof(double));


			for(int i=0; i<m; ++i)
				x1[i][0]=solved->x[0][i];

			multipication2(A,x1,r1,p,m,m,1);


			subtraction(r1,B,e1,p,1);
			
			
			transpose(e1,transposeOfe,p,1);
			double ** sonucc = (double **)calloc(1,sizeof(double *));
			for (int j=0;j<1;j++)
				sonucc[j] = (double *)calloc(1,sizeof(double));
			multipication2(transposeOfe,e1,sonucc,1,p,p,1);
			double sonuc = sqrt(sonucc[0][0]/10000);


			multipication2(A,x2,r1,p,m,m,1);
			subtraction(r1,B,e1,p,1);
			transpose(e1,transposeOfe,p,1);
			multipication2(transposeOfe,e1,sonucc,1,p,p,1);


			 sonuc = sqrt(sonucc[0][0]/10000);

			multipication2(A,x3,r1,p,m,m,1);
			subtraction(r1,B,e1,p,1);
			transpose(e1,transposeOfe,p,1);
			multipication2(transposeOfe,e1,sonucc,1,p,p,1);


			 sonuc = sqrt(sonucc[0][0]/10000);


			free(sonucc[0]);
			free(sonucc);
	/*		for(int i=0; i< m ; +i)
				free(x1[i]);
			free(x1);
			*/


/*
			for(int i=0; i< m ; +i)
				free(x2[i]);
			free(x2);

			for(int i=0; i< m ; +i)
				free(x3[i]);
			free(x3);
*/
	/*		for(int i=0; i< p ; +i)
				free(r1[i]);
			free(r1);
			fprintf(stderr, "444444444444444444444\n" );
*/
		/*	for(int i=0; i<  p; +i)
				free(e1[i]);
			free(e1);
			*/

			free(transposeOfe[0]);
			free(transposeOfe);


			for(int i=0; i<p; ++i)
				free(A[i]);
			free(A);
			for(int i=0; i<p; ++i)
				free(B[i]);
			free(B);


			
		}
	}

	if(DEBUG)
		fprintf(stderr, "**************main process waiting\n" );

	while(wait(NULL) != -1);

	detachandremove(shid, (void *)matrixs);
	detachandremove(shid2, (void *)solved);

	if(getpid() != mainpid)
		exit(0);

	//free(ptr);
	if(DEBUG)
		fprintf(stderr, "main process:%d\n",getpid() );
   
}
void* serverFonk(void* param){
	if(DEBUG)
		fprintf(stderr, "Working thread:%ld\n",pthread_self() );
	//		pthread_mutex_lock(&client_lock);

	//int newsockfd =  *((int *)(param));
	int newsockfd;
	while(1 ){ //request gelene kadar bekler
		newsockfd = accept(sockfd, NULL, NULL);
		++size;

	/*	if (sem_post(&semlock) == -1) 
			fprintf(stderr, "Thread failed to unlock semaphore\n");
	*/	//free(param);
		//close(sockfd);
		doprocessing(newsockfd);
		
		//pthread_mutex_unlock(&client_lock);
	}
	return NULL;
}
void * serverFonkPerAReq(void* param){
	if(DEBUG)
		fprintf(stderr, "Working thread:%ld\n",pthread_self() );
	int newsockfd =  *((int *)(param));
/*	if (sem_post(&semlock) == -1) 
		fprintf(stderr, "Thread failed to unlock semaphore\n");
*/	free(param);
	doprocessing(newsockfd);

	return NULL;
}

void  INThandler(int sig)
{
	fprintf(stderr, "CTRL^C catched!");
	if(pool_size!=0){
		if(getpid() == mainpid){
			kill(getpid(),sig);
			exit(1);
		}

		for(int i=0; i<size; ++i)
			pthread_join(tids[i],NULL);
		

		free(tids);
	}
	exit(0);
}

int main( int argc, char *argv[] ) {
	int  portno, clilen, newsockfd ;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	signal(SIGINT, INThandler);
	mainpid = getpid();
   	int n, pid;
	if (argc != 3) {
	  fprintf(stderr,"usage %s <port #, id> <thpool size, k >\n",argv[0]);
	  exit(0);
	}
	portno = atoi(argv[1]);
	pool_size = atoi(argv[2]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(1);
	}
   
	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		exit(1);
	}

	listen(sockfd,100);
	clilen = sizeof(cli_addr);

	if(pool_size<0){
		fprintf(stderr, "k must equal or bigger than zero!\n" );
		exit(1);
	}
	else if(pool_size == 0){ //create thread for each request
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		size = 0;
		while(1){

			newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); //request gelene kadar bekler

			if (newsockfd < 0) {
				perror("ERROR on accept");
				exit(1);
			}

			pthread_t tidss;
			newsock = malloc(sizeof(int));
			*newsock = newsockfd;
			++size;
			pthread_create(&tidss, &attr, serverFonkPerAReq,newsock);
		}

	}

	else{ //thread pool

		fprintf(stderr, "thread poola girdi k:%d\n",pool_size );
		//pthread_t tids[k]; //k sayısı kadar thread oluşturulacak.
		tids = malloc(sizeof(pthread_t) * pool_size);

		int i = 0;
		size = 0;
		for(i=0; i<pool_size; ++i)
  			pthread_create(&tids[i], NULL, serverFonk,NULL);
		
		while(1){
/*
			if(size == pool_size){
				pool_size*=2;
				fprintf(stderr,"size arttırıldı\n");
				tids = realloc(tids, sizeof(pthread_t) *pool_size);
				//tids = newpointer;
			}

			if(i<pool_size){
  				pthread_create(&tids[i], NULL, serverFonk,NULL);
  				++i;
  			}*/
		}
	}
	//detachandremove(shid,(void *)infos);
}