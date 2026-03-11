$ cat exp1client.c
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
# define port 5555

int main()
{
        int client_socket;
        char b[1024];
        struct sockaddr_in addr;
        client_socket=socket(AF_INET,SOCK_STREAM,0);
        printf("created");
        memset(&addr,0,sizeof(addr));
        addr.sin_port=htons(port);
        addr.sin_family=AF_INET;
        addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        connect(client_socket,(struct sockaddr *)&addr,sizeof(addr));
        while(1)
        {
                bzero(b,1024);
                printf("enter the message:\n");
                fgets(b,sizeof(b),stdin);
                send(client_socket,b,strlen(b),0);
                if(strncmp("exit",b,4)==0)
                {

                        printf("disconnected");
                        break;
                }
        }
        return 0;
}

ASUS@DESKTOP-SFADVSU /cygdrive/e/cn lab
$ cat exp1server.c
#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#define port 5555
int main()
{

int server_socket,client_socket;
struct sockaddr_in addr;
char b[1024];
socklen_t addrsize;

server_socket=socket(AF_INET,SOCK_STREAM,0);
memset(&addr,0,sizeof(addr));
addr.sin_family=AF_INET;
addr.sin_port=htons(port);
addr.sin_addr.s_addr=inet_addr("127.0.0.1");
bind(server_socket,(struct sockaddr *)&addr,sizeof(addr));
addrsize=sizeof(addr);
printf("connected successfully at %d",port);
listen(server_socket,5);
printf("listening");
client_socket=accept(server_socket,(struct sockaddr *)&addr,&addrsize);
while(1)
{
        bzero(b,1024);
        recv(client_socket,b,sizeof(b),0);
        printf("Client:%s \n",b);
        if(strncmp(b,"exit",4)==0)
        {
                close(server_socket);
                close(client_socket);
                exit(0);
                break;
        }
}
return 0;
}




ASUS@DESKTOP-SFADVSU /cygdrive/e/cn lab
