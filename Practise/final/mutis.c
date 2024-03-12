#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections*/

int main()
{
    int s,r,recb,sntb,x,ns,a=0;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[100];
	char str[100];
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		perror("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");

	r=listen(s,1);
	if(r==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket listening.\n");
    int num=0,pid;
    int len1 = sizeof(client);
    while(1)
    {
        int ns = accept(s,(struct sockaddr*)&client,&len1);

        if(num == 2)
        {
            printf("greater than 2");
            exit(0);
        }

        num++;

        pid = fork();
        if(pid == 0)
        {
            printf("Child created");
            fflush(stdout);

            while(recv(ns,buff,sizeof(buff),0)>0)
            {

                printf("\n%s",buff);
                fflush(stdout);
            }
            
        }
        close(ns);
    }

}