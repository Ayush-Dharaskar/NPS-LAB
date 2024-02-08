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
	int sockfd,r,snt,rec,x;
	struct sockaddr_in server;
	char buff[50];

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");


	server.sin_family=AF_INET;
	server.sin_port=htons(1234);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	r=connect(sockfd,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nConnection error.");
		exit(0);
	}
	printf("\nSocket connected.");
	
	printf("\n\n");
	printf("Enter data:");
	scanf("%s", buff);

	snt = send(sockfd,buff,sizeof(buff),0);
	if(snt==-1)
	{
		close(sockfd);
		printf("\nMessage Sending Failed");
		exit(0);
	}

	rec = recv(sockfd,buff,sizeof(buff),0);
		if(rec==-1)
	{
		printf("\nMessage Recieving Failed");	
		close(sockfd);
		exit(0);
	}
	printf("%s",buff);
}