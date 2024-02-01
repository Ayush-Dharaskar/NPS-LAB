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
	printf("Type File Name: ");
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

	printf("\n");
	printf("%s", buff);
	printf("\n\n");
	if(strcmp(buff,"File does not exist!")==0)
	{
		close(sockfd);
		exit(0);
	}

	int ch =0;
	char temp[50];
	int i=0;
	while(1)
	{
		printf("1.Append to file\n2.Search file");
		scanf("%d",&ch);

		switch(ch)
		{
		case 1:
			printf("Enter string to append:");
			scanf("%s",temp);
			buff[0]=ch;
			buff[1]=strlen(temp);
			i=0;
			for(i=0;i<strlen(temp);i++)
			{
				buff[i+2] = temp[i];
			}
			buff[i+2] ='\0';

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
				close(sockfd);
				printf("\nMessage Sending Failed");
				exit(0);
			}
			break;

		case 2:
			printf("Enter word to search:");
			scanf("%s",temp);
			buff[0]=ch;
			buff[1]=strlen(temp);
			i=0;
			for(i=0;i<strlen(temp);i++)
			{
				buff[i+2] = temp[i];
			}
			buff[i+2] ='\0';
			snt = send(sockfd,buff,sizeof(buff),0);
			if(snt==-1)
			{
				close(sockfd);
				printf("\nMessage Sending Failed");
				exit(0);
			}
			rec = recv(sockfd,buff,sizeof(buff),0);
			printf("%s",buff);
			if(rec==-1)
			{
				close(sockfd);
				printf("\nMessage Sending Failed");
				exit(0);
			}
			break;

		}
	}

}