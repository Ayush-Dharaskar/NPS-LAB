#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{	printf("socket creation error");
		exit(0);
	}
	struct sockaddr_in c_addr;
	c_addr.sin_port = htons(3388);
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = inet_addr("172.16.53.66");
	int r=connect(sockfd, (struct sockaddr*) &c_addr,sizeof(c_addr)),rece,sendd;
	if(r==-1){
		printf("\nconnection error");
		exit(0);
	}
	printf("\nSocket connected.\n");
    printf( "PID : %d && PPID : %d\n" ,getpid() , getppid()) ;
    int pid = fork();
    int snt,rec;
    char buff[20],buff1[20];

    while(1)
    {
        if (pid >0)
        {
            printf( " \nParent process PID : %d && PPID : %d\n" ,getpid() , getppid());
            rec = recv(sockfd,buff,sizeof(buff),0);
            if(rec==-1){
                printf("\n Failed to rec");
                close(sockfd);
               
                exit(0);
            }
            if (strcmp(buff, "BYE") == 0)
                break;
        }
        else
        {
            printf( "\nChild process PID : %d && PPID : %d\n" ,getpid() , getppid()) ;
  			printf("\nChild:");
  			scanf("%s",buff1);
  			snt=send(sockfd,buff1,sizeof(buff),0);
  			if(snt==-1){
  				printf("\n Failed to send");
  				close(sockfd);
  				exit(0);
  			}
  			if (strcmp(buff1, "BYE") == 0)
        	break;
        }

    }
    close(sockfd);
    exit(0);
}