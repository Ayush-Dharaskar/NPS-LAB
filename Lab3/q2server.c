#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
void swap(char * x, char * y) 
{
  char temp;
  temp = * x;
  * x = * y;
  * y = temp;
}
void permute(char * a, int l, int r) 
{
  int i;
  if (l == r)
    printf("%s\n", a);
  else 
  {
    for (i = l; i <= r; i++) 
    {
      swap((a + l), (a + i));
      permute(a, l + 1, r);
      swap((a + l), (a + i)); //backtrack
    }
  }
}
int main()
{
	int sockfd,rec,sent,port;
	struct sockaddr_in server, client;
	char buff[50];
	sockfd= socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) 
	{
	printf("\nSocket creation error.");
	exit(0);
	}
	printf("\nSocket created.\n");
	server.sin_family = AF_INET;
	server.sin_port = htons(3388);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	int r = bind(sockfd,(struct sockaddr *)&server,sizeof(server));
	if (r == -1) 
	{
		printf("\nBinding error.");
		exit(0);
	}	
	printf("\nSocket binded.\n");
	int ca = sizeof(client);
	while(1)
	{
		rec = recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&client,&ca);
		if (rec == -1) 
	    {
		    printf("\nMessage Recieving Failed");
		    close(sockfd);
		    exit(0);	
	    }
    printf("\nMessage Recieved: ");
    printf("%s", buff);
    if (!strcmp(buff, "stop"))
    	break;
    printf("\nPermutations of the string are: \n");
    permute(buff,0,strlen(buff)-1);
	}


	close(sockfd);
}
