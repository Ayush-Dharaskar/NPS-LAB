#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>

int main()
{
int sockfd,r,rec,snt,ns,x;
	socklen_t len;
	struct sockaddr_in server, client;
	char buff[50];

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{	
		printf("\nSocket creation error.");
		exit(0);
	}

	// printf("\nSocket created.");
	// printf("INPUT port number: ");
	// scanf("%d", &x);

	server.sin_family=AF_INET;
	server.sin_port=htons(1234);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	int opt =1;
	if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,  
          sizeof(opt)) < 0 )   
    {   
        perror("setsockopt");   
        exit(EXIT_FAILURE);   
    } 


	r = bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}

	printf("\nSocket binded.");

	r=listen(sockfd,1);
	if(r==-1)
	{
		close(sockfd);
		exit(0);
	}
	printf("\nSocket listening.\n");

	len=sizeof(client);

	ns=accept(sockfd,(struct sockaddr*)&client, &len);
	if(ns==-1)
	{
		close(sockfd);
		exit(0);
	}
	printf("\nSocket accepting.\n");

	rec=recv(ns,buff,sizeof(buff),0);
	if(rec==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(sockfd);
		close(ns);
		exit(0);
	}	
	printf("\nFile Name Recieved!\n");

	char buff2[50];
	if(access(buff, F_OK )!= -1)
	{
		strcpy(buff2,buff);
		strcpy(buff,"File Exists");
	}
	else
	{
		strcpy(buff,"File does not exist!");    
	}

	snt = send(ns,buff,sizeof(buff),0);

    if (send(ns, buff, sizeof(buff), 0) == -1) {
        printf("\nMessage Sending Failed");
        close(sockfd);
        close(ns);
        exit(1);
    }
    if (strcmp(buff, "File does not exist") == 0) {
        close(sockfd);
        close(ns);
        exit(1);
    }
}