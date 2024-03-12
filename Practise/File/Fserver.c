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

    r = recv(ns, buff, sizeof(buff), 0);
    if (r < 0) {
        printf("recv failed");
        exit(1);
    }
    

    //strcat(buff1,".txt");
    printf("\nFile Received:%s",buff);
    FILE *f;
    if((f = fopen(buff,"r")) != NULL)
    {
        strcpy(buff1,buff);
        strcpy(buff, "File Exists");
    }
    else
    {
        strcpy(buff,"File does not exist");
    }

    if (send(ns, buff, sizeof(buff), 0) == -1) {
        printf("\nMessage Sending Failed");
        close(sockfd);
        close(ns);
        exit(1);
    }
    
    FILE *alpha = fopen("Alpha.txt","w");
    FILE *num = fopen("number.txt","w");
    FILE *spec = fopen("spec.txt","w");

    char temp[50];
    fgets(temp,sizeof(temp),f);
    printf("%s\n",temp);
    int sum=0;
    for(int i=0;temp[i] != '\0';i++)
    {
        if(temp[i]>='a' && temp[i]<'z')
        {
            fputc(temp[i],alpha);
            sum += temp[i];
        }

    }

    fputs("hello",alpha);

}