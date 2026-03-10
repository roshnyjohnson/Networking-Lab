$ cat factorialserver.c
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main()

{
        int num,i;
        int flag=0;
        char buffer[256];

        int server_socket,client_socket;
        server_socket=socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in saddr={AF_INET,htons(5555),INADDR_ANY},caddr;

        bind(server_socket,(struct sockaddr *)&saddr,sizeof(saddr));
        socklen_t caddrsize=sizeof(caddr);
        listen(server_socket,5);

        client_socket=accept(server_socket,(struct sockaddr *)&caddr,&caddrsize);

        recv(client_socket,&num,sizeof(num),0);
        int fact=1;
        for(i=1;i<=num;i++)
        {
                fact*=i;
        }
        printf("The fact  is %d",fact);

        //snprintf(,255,"\n the factors are %d and 1",num);
        send(client_socket,&fact,sizeof(fact),0);
        close(server_socket);
        close(client_socket);
}





$ cat factorialclient.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

int main()
{

        //char buff[256];
        int num;
        //socklen_t caddrsize;
        int client_socket;
        client_socket=socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in caddr={AF_INET,htons(5555),inet_addr("127.0.0.1")};
        //caddrsize=sizeof(caddr);
        int fact;
        connect(client_socket,(struct sockaddr *)&caddr,sizeof(caddr));


        printf("\nEnter a number:\n");
        scanf("%d",&num);
        send(client_socket,&num,sizeof(num),0);

        recv(client_socket,&fact,sizeof(fact),0);
        printf("The factorial is %d\n",fact);

        close(client_socket);
        return 0;

}
