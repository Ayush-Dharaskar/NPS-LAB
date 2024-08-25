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
  	printf("\nsocket is ready to accept\n");
    fflush(stdout);
    r = recv(ns, buff, sizeof(buff), 0);
    if (r < 0) {
        printf("recv failed");
        exit(1);
    }
    
    printf("%s\n",buff);
    //strcat(buff1,".txt");
   
    FILE *f = fopen(buff,"r");
    if(f != NULL)
    {
        strcpy(buff,"FIle found");
        
    }
    else{
        strcpy(buff,"file not found");
    }
    printf("%s\n",buff);
    if(send(ns,buff,sizeof(buff),0)<0)
    {
        printf("File send failed");
        exit(0);
    }
    char temp[50];
	int choice;
    fgets(temp,sizeof(temp),f);
    printf("%s\n",temp);
	while(1)
	{
		recv(ns,buff,sizeof(buff),0);
		recv(ns,&choice,sizeof(buff),0);

		if(choice == 1)
		{
			fputs(buff,f);
		}

	}
}