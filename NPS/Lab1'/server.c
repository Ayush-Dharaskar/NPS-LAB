#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>

int main()
{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);	//socket creation
	struct sockaddr_in	server_addr, c_addr;	
	
	//feeding values into the socket address structure
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset( server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero) );
	
	bind( sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr) );
	
	//ready for listening
	listen(sockfd, 10);
	printf("The server is ready for listening.\n");
	int size = sizeof(struct sockaddr);
	
	int afd = accept(sockfd, (struct sockaddr *) & c_addr, &size);
	int buffer[10];

	int choice, sz, temp;
	int odd[10] = {0};
	int even[10] = {0};
	int a =0, b = 0;
	int ele=0;

    while(1)
    {
        recv(afd,buffer,sizeof(buffer),0);
        recv(afd, &sz, sizeof(sz), 0);
		recv(afd, &choice, sizeof(choice), 0);
        switch(choice)
        {
            case 1:// have to sort asc
					for(int i=0 ; i<sz-1 ; i++)
					{
						for(int j=0 ; j<sz-1-i ; j++)
						{
							if(buffer[j]>buffer[j+1])
							{
								temp = buffer[j];
								buffer[j] = buffer[j+1];
								buffer[j+1] = temp;
							}
						}
					}
					for(int i=0 ; i<sz ; i++)
						printf("%d ", buffer[i]);

                    fflush(stdout);
					send(afd, buffer, 40, 0);
					break;

            case 5:
                close(sockfd);
                exit(0);
        }
    }


}