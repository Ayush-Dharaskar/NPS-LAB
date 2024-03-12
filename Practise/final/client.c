#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
    int sockfd,rec,snt,r,x;

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
    printf("ENTer file:");
    scanf("%s",buff);

    send(sockfd,buff,sizeof(buff),0);
    recv(sockfd,buff,sizeof(buff),0);
    
    printf("%s\n",buff);


}