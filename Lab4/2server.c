#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main()
{
	int sockfd,r,snt,rec,ns,x;
	socklen_t len;
	struct sockaddr_in server, client;
	char buff[50];

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{	
		printf("\nSocket creation error.");
		exit(0);
	}

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

	rec = recv(ns,buff,sizeof(buff),0);
	if(rec==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(sockfd);
		close(ns);
		exit(0);
	}	
	int par[4];
	int err=0;

    par[3]=(buff[0]-'0')^(buff[2]-'0')^(buff[4]-'0')^(buff[6]-'0')^(buff[8]-'0')^(buff[10]-'0');
    par[2]=(buff[0]-'0')^(buff[1]-'0')^(buff[4]-'0')^(buff[5]-'0')^(buff[8]-'0')^(buff[9]-'0');
    par[1]=(buff[6]-'0')^(buff[4]-'0')^(buff[5]-'0')^(buff[7]-'0');
    par[0]=(buff[0]-'0')^(buff[1]-'0')^(buff[2]-'0')^(buff[3]-'0');
    
    printf("RECIEVED:");
    for(int i=0;i<11;i++)
    {
    	
    	printf("%d",(buff[i]-'0'));
    }
    int pwr=3;
        printf("\n");
    for(int i=0;i<4;i++)
    {
    	printf("%d",par[i]);
    }


    sprintf(buff,"%d",err);
    snt = send(ns,buff,sizeof(buff),0);
	if(snt==-1)
	{
		close(sockfd);
		printf("\nMessage Sending Failed");
		exit(0);
	}



	close(ns);
	close(sockfd);
	return 0;
}