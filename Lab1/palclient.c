// Q1 TCP program to send an array of numbers to the server and choose from 4 options to do the required stuff
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define myport 1234
int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{	printf("socket creation error");
		exit(0);
	}
	struct sockaddr_in c_addr;
	c_addr.sin_port = htons(myport);
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(c_addr.sin_zero, '\0', sizeof(c_addr.sin_zero));
	
	int size = sizeof(struct sockaddr);
	connect(sockfd, (struct sockaddr*) &c_addr, sizeof(c_addr));
	int opt,n;
	while(1)
	{
		printf("Enter number:");
		scanf("%d",&n);
		send(sockfd,&n,sizeof(n),0);
		recv(sockfd,&n,sizeof(n),0);
		printf("Number :%d",n);
		printf("Continue?1/0");
		scanf("%d",&opt);
		send(sockfd,&opt,sizeof(opt),0);
		if
		close(sockfd);
		exit(0);
	}
}