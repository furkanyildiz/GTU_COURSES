#define DEBUG 0
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
#include <math.h>
 int  portno;
//pthread_mutex_t client_lock = PTHREAD_MUTEX_INITIALIZER;
int m; //columns
int p; //rows
sem_t semlock;
int callSocket(char *hostname, unsigned short portnum)
{
	struct sockaddr_in sa;
	struct hostent *hp;
	int a, s;
	if ((hp= gethostbyname(hostname)) == NULL) { /* do we know the host's */
	errno= ECONNREFUSED; /* address? */
	return(-1); /* no */
	} /* if gethostname */
	memset(&sa,0,sizeof(sa));
	memcpy((char *)&sa.sin_addr,hp->h_addr,hp->h_length); /* set address */
	sa.sin_family= hp->h_addrtype;
	sa.sin_port= htons((u_short)portnum);
	if ((s= socket(hp->h_addrtype,SOCK_STREAM,0)) < 0) /* get socket */
		return(-1);
	if (connect(s,(struct sockaddr *)&sa,sizeof sa) < 0) { /* connect */
		close(s);
		return(-1);
	} /* if connect */
	return(s);
}


void* clientFonk(void* param){
    double *timeOfMatrixGenerated = (double *)malloc(sizeof(double));
    long timedif;
    struct timeval tpend;
	struct timeval tpstart;

    if (gettimeofday(&tpstart, NULL)) {
        fprintf(stderr, "Failed to get end time\n");
    }

    if(DEBUG)
		fprintf(stderr, "client Working thread:%ld\n",pthread_self() );

	int sockfd;
	while (sem_wait(&semlock) == -1)
		if(errno != EINTR) {
			fprintf(stderr, "Thread failed to lock semaphore\n");
			return NULL;
		}

	sockfd = callSocket("localhost", portno);
	if (sockfd < 0) {
	  perror("ERROR connecting");
	  exit(1);
	}
	if (sem_post(&semlock) == -1) 
		fprintf(stderr, "Thread failed to unlock semaphore\n");

	//semlock = *((sem_t*)(param));
	//int sockfd = *((int*)(param)); 

	int n;
	char buffer[256];
	bzero(buffer,256);

	
	char num1[256];
	char num2[256];
	bzero(num1,256);
	bzero(num2,256);

	sprintf(num1, "%d", m);
	sprintf(num2, "%d", p);

	strcat(buffer, num1);
	strcat(buffer, " ");
	strcat(buffer,num2);

	//fgets(buffer,255,stdin);

	n = write(sockfd, buffer, strlen(buffer));

	if (n < 0) {
	  perror("ERROR writing to socket");
	  exit(1);
	}

	bzero(buffer,256);




	double ** A = (double **)calloc(p,sizeof(double *));
	for (int j=0;j<p;j++)
		A[j] = (double *)calloc(m,sizeof(double));

	double * B = (double *)calloc(p,sizeof(double));



	for(int i=0; i<p; ++i)
		for(int j=0; j<m; ++j)
			n = read(sockfd, &A[i][j], sizeof(double));

	for(int i=0; i<p; ++i)
		n = read(sockfd, &B[i], sizeof(double));

	if(DEBUG){
		fprintf(stderr, "AAAAAAAAA:\n" );
		for(int i=0; i<p; ++i){
			for(int j=0; j<m; ++j)
				fprintf(stderr, "A:%f ",A[i][j] );
			
			fprintf(stderr, "\n" );
		}


		

		fprintf(stderr, "BBBBBBBBBBb:\n" );
		for(int i=0; i<p; ++i){
			fprintf(stderr, "B:%f ",B[i] );
				
		}
			fprintf(stderr, "\n" );
	}

	FILE *fp;
	char  a[100];
	sprintf(a, "%d", getpid());
	char  b[100];
	sprintf(b, "%ld", pthread_self());
	char c[1024];
	strcat(c,"Logs/clients_");
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
    fprintf(fp, "]\n\n");

    fprintf(fp, "B= [");

		for(int i =0; i<p; ++i){

        	fprintf(fp, "%.3f ",B[i] );
        	if(i!=p-1)
    			fprintf(fp, ";");
	}
    fprintf(fp, "]\n");

	fclose(fp);

	for(int i=0; i<p; ++i)
		free(A[i]);
	free(A);
	free(B);


	if (n < 0) {
	  perror("ERROR reading from socket");
	  exit(1);
	}



  	if (gettimeofday(&tpend, NULL)) {
        fprintf(stderr, "Failed to get end time\n");
    }
    timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
    tpend.tv_usec - tpstart.tv_usec;
    *timeOfMatrixGenerated =  (double)timedif / 1000.0;

	return timeOfMatrixGenerated;

}
void  INThandler(int sig)
{
    time_t rawtime;
    struct tm * timeinfo;
	fprintf(stderr, "CTRL^C yakalandı:%d\n",sig );
	time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    char * time2 = asctime (timeinfo);
	FILE *fp;
	char  a[100];
	sprintf(a, "%d", getpid());
	char  b[100];
	sprintf(b, "%ld", pthread_self());
	char c[1024];
	strcat(c,"Logs/clients_");
	strcat(c,a);
	strcat(c,"_");
	strcat(c,b);
	strcat(c,".log");
	fp = fopen(c, "a+");
    fprintf(fp, "Kill signal has received %s\n",time2);
    fclose(fp);
	exit(0);
}

int main(int argc, char *argv[]) {
   int  n;

		int sizeofClients = 0;
   
   char buffer[256];
   
   if (argc != 5) {
      fprintf(stderr,"usage %s <#of columns of A, m> <#of rows of A, p> <#of clients, q> < port no>\n",argv[0]);
      exit(0);
   }
	signal(SIGINT, INThandler);
   
   m = atoi(argv[1]);
   p = atoi(argv[2]);
   int q = atoi(argv[3]);
   portno = atoi(argv[4]);
   
	pthread_t tids[q]; //q sayısı kadar thread oluşturulacak.

	if (sem_init(&semlock, 0, 1) == -1) {
		perror("Failed to initialize semaphore");
		return 1;
	}
	for(int current_thread_num=0; current_thread_num<q; ++current_thread_num){
  		pthread_create(&tids[current_thread_num], NULL, clientFonk,NULL);
  		++sizeofClients;
  		fprintf(stderr, "Number of clients currently being server: %d\n",sizeofClients );
	}
	double * time;
	double timeArr[q];
	int size = 0;
	for(int i=0; i<q; ++i){
		if(pthread_join(tids[i], (void **) &time) != 0)
			perror("JOIN ERROR");
		timeArr[i] = *time;
		free(time);
	}
	double avg = 0.0;
	double sum = 0.0;
	for(int i=0; i<q; ++i){
		sum += timeArr[i];
	}
	avg = sum/q;
	sum = 0.0;
	for(int i=0; i<q; ++i){
		sum += pow(timeArr[i] - avg, 2);
	}
	sum = sum / q-1;
	double standertDevition = sqrt(sum);

	FILE *fp;
	char  a[100];
	strcpy(a,"Logs/clients.log");
	fp = fopen(a, "w+");
    fprintf(fp, "average connection time :%f ms and the standard deviation:%f ms\n",avg,standertDevition);
    fclose(fp);

	return 0;
}