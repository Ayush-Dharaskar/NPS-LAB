#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define myport 1234

int main()
{
	int size;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);	//socket creation
	struct sockaddr_in	server_addr, c_addr;	
	
	//feeding values into the socket address structure
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(myport);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset( server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero) );
	
	bind( sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr) );
	
	//ready for listening
	listen(sockfd, 1);
	printf("The server is ready for listening.\n");
	size = sizeof(struct sockaddr);
	
	int afd = accept(sockfd, (struct sockaddr *) & c_addr, &size);
	int temp=0, n,rev=0;
	while(1)
	{
		recv(afd, &n, sizeof(n),0);
		while(n>0)
		{
			temp = n%10;
			rev = rev*10+ temp;
			n=n/10;
		}
		printf("Number :%d",rev);
		send(afd,&rev,sizeof(rev),0);

	}

}