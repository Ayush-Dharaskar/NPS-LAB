#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
int main(){
	int rec,sent;
  	char buff[50], buff2[50];
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{	printf("socket creation error");
		exit(0);
	}

	struct sockaddr_in c_addr;
	c_addr.sin_port = htons(6873);
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int r = connect(sockfd, (struct sockaddr*) &c_addr, sizeof(c_addr));
	if (r == -1) 
	{
		printf("\nConnection error.");
		exit(0);
	}
	printf("socket connected\n\n");

	printf("Orignal process PID:%d  PPID:%d",getpid(),getppid());

	int pid = fork();

	while(1)
	{
		if (pid != 0)//parent process
		{
			printf("Parent process PID:%d  PPID:%d",getpid(),getppid());
		
			rec = recv(sockfd,buff,sizeof(buff),0);

			if (rec == -1) 
			{
				printf("\nMessage Recieving Failed");
				close(sockfd);
				exit(0);
			}

			if(strcmp("BYE",buff)==0)
			{
				break;
			}
			printf("\nParent:%s",buff);
		}
		else
		{
			printf( "Child Process, PID : %d && PPID : %d\n" ,getpid() , getppid()) ;
			
			printf("\nChild:");
			scanf("%s",&buff2);

			sent = send(sockfd,buff2,sizeof(buff2),0);

			if(sent ==-1)
			{
				close(sockfd);
				printf("\nMessage Sending Failed");
				exit(0);
			}
			if (strcmp(buff2, "BYE") == 0)
        		break;

		}
	}
	close(sockfd);



}