$ cat exp4server.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#define port 5555
int main()
{
        int server_socket,nsfd;
        char b[1024];
        struct  sockaddr_in caddr,saddr;
        socklen_t caddrsize;
        server_socket=socket(AF_INET,SOCK_STREAM,0);
        memset(&saddr,0,sizeof(saddr));
        saddr.sin_family=AF_INET;
        saddr.sin_port=htons(port);
        saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
        bind(server_socket,(struct sockaddr *)&saddr,sizeof(saddr));
        if(listen(server_socket,5)==-1)
        {
                printf("error in listening");

        }
        caddrsize=sizeof(caddr);
        nsfd=accept(server_socket,(struct sockaddr *)&caddr,&caddrsize);
        printf("Client connected successfully\n");
        while(1)
        {
                bzero(b,1024);
                //printf("Client:")
                recv(nsfd,b,sizeof(b),0);
                printf("Client:%s\n",b);
                if(strncmp(b,"exit",4)==0)
                {
                        printf("disconnected");
                        break;
                }
                printf("Enter the message:\n");
                fgets(b,sizeof(b),stdin);
                send(nsfd,b,strlen(b),0);
                if(strncmp(b,"exit",4)==0)
                {
                        printf("disconnected");
                        break;
                        close(nsfd);
                        close(server_socket);
                }

        }
        return 0;
}

ASUS@DESKTOP-SFADVSU /cygdrive/e/cn lab
$ cat exp4client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define port 5555

int main()
{
        int client_socket,nsfd;
        char b[1024];
        //socklen_t caddrsize;
        struct sockaddr_in caddr;
        client_socket=socket(AF_INET,SOCK_STREAM,0);
        memset(&caddr,0,sizeof(caddr));
        caddr.sin_family=AF_INET;
        caddr.sin_port=htons(port);
        caddr.sin_addr.s_addr=inet_addr("127.0.0.1");
        connect(client_socket,(struct sockaddr *)&caddr,sizeof(caddr));
        while(1)
        {
                bzero(b,1024);
                printf("Enter the message\n");
                fgets(b,sizeof(b),stdin);
                send(client_socket,b,strlen(b),0);
                if (strncmp(b, "exit", 4) == 0)
                {
                        printf("Disconnected");
                        break;
                }

                recv(client_socket,b,sizeof(b),0);
                printf("server:%s\n",b);
                if (strncmp(b, "exit", 4) == 0)
                {
                        printf("Disconnected");
                        break;
                }
                /*printf("Enter the message\n");
                send(client_socket,b,strlen(b),0);
                if (strncmp(b, "exit", 4) == 0)
                {
                        printf("Disconnected");
                        break;
                }*/


        }
        return 0;
}

ASUS@DESKTOP-SFADVSU /cygdrive/e/cn lab
