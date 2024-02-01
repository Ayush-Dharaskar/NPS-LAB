#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

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
	// strcpy(buff2,buff);
	// strcat(buff,".txt");

	// FILE *f;
	// if((f = fopen(buff,"r"))!= NULL)
	// {
		
	// 	strcpy(buff,"File Exists");
	// }
	// else
	// {
	// 	strcpy(buff,"File not found");
	// }

	snt = send(ns,buff,sizeof(buff),0);

	if(snt==-1)
	{
		printf("\nMessage Sending Failed");
		close(sockfd);
		close(ns);
		exit(0);
	}
	if(strcmp(buff,"File does not exist!")==0)
	{
		close(sockfd);
		close(ns);
		exit(0);
	}

	rec = recv(ns,buff,sizeof(buff),0);


		int ch = buff[0];
		int n = buff[1];
		char str[50];
		for(int i=0;i<n;i++)
		{
			str[i]=buff[i+2];
		}
		FILE * f;
		int count=0;
		
		char convert[100];
		switch(ch)
		{
		case 1:
			
			// strcat(buff2,".txt");
			f = fopen(buff2,"a");
			fputs(str,f);
			fputs("\n",f);

			strcpy(buff,"Append successful!");
			snt = send(ns,buff,sizeof(buff),0);
			if(snt==-1)
			{
				close(sockfd);
				printf("\nMessage Sending Failed");
				exit(0);
			}
			break;

		case 2:
			char word[100];
			f = fopen(buff2,"a");
			while(fscanf(f,"%s",word) != EOF)
			{
				if (strcmp(str,word)==0)
				{
					count++;
				}
			}
			printf("VALUE OF COUNT:%d",count);
			sprintf(convert,"%d",count);
			strcpy(buff,"Instances of word found:");
			strcat(buff,convert);
			strcat(buff,"\n");
			snt = send(ns,buff,sizeof(buff),0);
			if(snt==-1)
			{
				close(sockfd);
				printf("\nMessage Sending Failed");
				exit(0);
			}


		}

	



}