#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	socklen_t len;

	if(sockfd == -1)
	{	printf("socket creation error");
		exit(0);
	}
	printf("Socket created");
	struct sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_port = htons(1234);
	server.sin_addr.s_addr = htonl(INADDR_ANY);


    int opt =1;
	if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,  
          sizeof(opt)) < 0 )   
    {   
        perror("setsockopt");   
        exit(EXIT_FAILURE);   
    } 



	int r = bind(sockfd, (struct sockaddr * ) & server, sizeof(server));

	char buff[20],buff1[20];

	int sendd,rece;
	if (r == -1) 
  	{
    	printf("\nBinding error.");
    	exit(0);
  	}
  	printf("\nSocket binded.");
 	r = listen(sockfd, 1);
  	if (r == -1) 
  	{
    	close(sockfd);
    	exit(0);
  	}
  	printf("\nSocket listening.");
  	len = sizeof(client);
  	int ns = accept(sockfd, (struct sockaddr * ) & client, & len);
  	if(ns==-1){
  		close(sockfd);
  		exit(0);
  	}
  	printf("\nsocket is ready to accept");

    recv(ns,buff,sizeof(buff),0);
    printf("%s",buff);
    strcat(buff,".txt");
    printf("%s",buff);
    FILE *f = fopen(buff,"r");

    if(f ==NULL)
    {
        strcpy(buff,"\nFILE NOT FOUND");
        send(ns,buff,sizeof(buff),0);
        close(sockfd);
        exit(0);
    }
    else
    {
        strcpy(buff1,buff);
        strcpy(buff,"\nFILE FOUND");
        send(ns,buff,sizeof(buff),0);
    }
    printf("\n");
    // fgets(buff,sizeof(buff),f);
    printf("%s",buff);

    char temp[50];
    // fscanf(f,"%s",temp);
    // printf("INSIDE :%s",temp);
    while(fscanf(f,"%s",temp) == 1)
    {
        printf("INSIDE :%s\n",temp);
    }
    exit(0);

}