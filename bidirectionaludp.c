$ cat exp6client.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define port 5555
int main()
{
        int client_socket,nsfd;
        char b[1024];
        struct sockaddr_in saddr,caddr;
        socklen_t saddrsize;

        client_socket=socket(AF_INET,SOCK_DGRAM,0);
        memset(&saddr,0,sizeof(saddr));
        saddr.sin_port=htons(port);
        saddr.sin_family=AF_INET;
        saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
       // bind(client_socket,(struct sockaddr *)&saddr,sizeof(saddr));
        saddrsize=sizeof(saddr);
        while(1)
        {
                /*bzero(b,1024);
                recvfrom(server_socket,b,sizeof(b),0,(struct sockaddr*)&caddr,&caddrsize);
                 if(strncmp(b,"exit",4)==0)
                {
                        close(server_socket);
                        printf("Disconnected\n");
                        break;
                }

                printf("client:%s\n",b);*/

                bzero(b,1024);
                printf("enter the message:");
                fgets(b,sizeof(b),stdin);
                sendto(client_socket,b,strlen(b),0,(struct sockaddr*)&saddr,saddrsize);
                if(strncmp(b,"exit",4)==0)
                {
                        close(client_socket);
                        printf("Disconnected\n");
                        break;
                }
                bzero(b,1024);
                recvfrom(client_socket,b,sizeof(b),0,(struct sockaddr*)&saddr,&saddrsize);
                if(strncmp(b,"exit",4)==0)
                {
                        close(client_socket);
                        printf("Disconnected\n");
                        break;
                }

                printf("server:%s\n",b);


        }
        return 0;
}

ASUS@DESKTOP-SFADVSU /cygdrive/e/cn lab
$ cat exp6server.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define port 5555

//printf("program starts\n");
int main()
{
        printf("program starts\n");

        int server_socket,nsfd;
        char b[1024];
        struct sockaddr_in saddr,caddr;
        socklen_t caddrsize;

        server_socket=socket(AF_INET,SOCK_DGRAM,0);
        if(server_socket<0)
        {
                printf("socket creation failed\n");
        }
        else
        {
                printf("success socket creation\n");
        }
        memset(&saddr,'\0',sizeof(saddr));
        saddr.sin_port=htons(port);
        saddr.sin_family=AF_INET;
        saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
        if(bind(server_socket,(struct sockaddr *)&saddr,sizeof(saddr))<0)
        {
                printf("Error in binding");
        }

        caddrsize=sizeof(caddr);
        while(1)
        {
                bzero(b,1024);
                int n=recvfrom(server_socket,b,sizeof(b),0,(struct sockaddr*)&caddr,&caddrsize);
                if(n<0)
                {
                        printf("recieved failed");
                }
                printf("client:%s\n",b);
                if(strncmp(b,"exit",4)==0)
                {
                        close(server_socket);
                        printf("Disconnected\n");
                        break;
                }

                //printf("client:%s\n",b);

                bzero(b,1024);
                printf("enter the message:");
                fgets(b,sizeof(b),stdin);
                sendto(server_socket,b,strlen(b),0,(struct sockaddr*)&caddr,caddrsize);
                if(strncmp(b,"exit",4)==0)
                {
                        close(server_socket);
                        printf("Disconnected\n");
                        break;
                }
        }
        return 0;
}

