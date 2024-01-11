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
	int sockfd,r,rec,sent,port;

	
	printf("Input port:");
	scanf("%d",&port);

	struct sockaddr_in server,client;
	char buff[50];
	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	if (sockfd == -1) {
    	printf("\nSocket creation error.");
    	exit(0);
  	}

  	printf("\nSocket created.");
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t len;
    len = sizeof(server);
    while(1)
    {
    	printf("\n\n Enter mssg (stop to close):");
    	scanf("%s",buff);
    	sent = sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server,len);
    	if(sent==-1)
    	{
    		close(sockfd);
    		printf("\nMessage sending Failed");
     		exit(0);
    	}
    	if(strcmp(buff,"stop")==0)
    		break;

    }
    close(sockfd);



}