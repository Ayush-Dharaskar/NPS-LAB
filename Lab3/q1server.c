#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>

int main()
{
	int sockfd,rec,sent,a=0;
	char buff[50],buff2[50];
	struct sockaddr_in server,client;
	sockfd = socket(AF_INET, SOCK_STREAM,0);

	if (sockfd == -1) 
	{
	printf("\nSocket creation error.");
	exit(0);
	}
	printf("\nSocket created.");
	server.sin_family = AF_INET;
	server.sin_port = htons(6873);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	int r = bind(sockfd, (struct sockaddr * ) & server, sizeof(server));
	if (r == -1) 
	{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded");
	r = listen(sockfd,1);
	if (r == -1) 
	{
		close(sockfd);
		exit(0);
	}
	socklen_t len =sizeof(client);
	printf("\nSocket listening.");
	int afd = accept(sockfd,(struct sockadder *)&client,&len);
	if (afd == -1) 
  	{
    	close(sockfd);
    	exit(0);
  	}
	printf("\nSocket accepting.\n");
	printf( "Original Process, PID : %d && PPID : %d\n" ,getpid() , getppid()) ;
	int pid = fork();
	while(1)
	{
		if(pid!=0)
		{
			printf( "Parent Process, PID : %d && PPID : %d\n" ,getpid() , getppid( )) ;
     		printf("\n\nParent: ");
     	 	scanf("%s", buff2);
     	 	sent = send(afd,buff2,sizeof(buff2),0);
			if (sent == -1) 
			{
				printf("\nMessage Sending Failed");
				close(sockfd);
				close(afd);
				exit(0);
			}
			if (strcmp(buff2, "BYE") == 0)
				break;

		}
		else
		{
			printf( "Child Process, PID : %d && PPID : %d\n" ,getpid() , getppid()) ;
			rec = recv(afd,buff,sizeof(buff),0);
			if (rec == -1) 
			{
				printf("\nMessage Recieving Failed");
				close(sockfd);
				close(afd);
				exit(0);
			}
			if (strcmp(buff, "BYE") == 0)
				break;
			printf("\nChild: ");
			printf("%s\n", buff);
		}
	}
	close(afd);
	close(sockfd);
	}
