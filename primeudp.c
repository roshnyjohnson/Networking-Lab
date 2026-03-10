$ cat primeclient.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

int main()
{

        char buff[256];
        int num;
        socklen_t caddrsize;
        int client_socket;
        client_socket=socket(AF_INET,SOCK_DGRAM,0);
        struct sockaddr_in caddr={AF_INET,htons(5555),inet_addr("127.0.0.1")};
        caddrsize=sizeof(caddr);


        printf("\nEnter a number:\n");
        scanf("%d",&num);
        sendto(client_socket,&num,sizeof(num),0,(struct sockaddr *)&caddr,caddrsize);

        recvfrom(client_socket,buff,sizeof(buff),0,(struct sockaddr *)&caddr,&caddrsize);
        printf(buff);

        close(client_socket);
        return 0;

}




$ cat prime.c
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
        server_socket=socket(AF_INET,SOCK_DGRAM,0);
        struct sockaddr_in saddr={AF_INET,htons(5555),INADDR_ANY},caddr;

        bind(server_socket,(struct sockaddr *)&saddr,sizeof(saddr));
        socklen_t caddrsize=sizeof(caddr);

        recvfrom(server_socket,&num,sizeof(num),0,(struct sockaddr *)&caddr,&caddrsize);
        for (i=2;i<num/2;i++)
        {
                if(num%i==0)
                {
                        printf("%d is a composite number\n",num);
                        flag=1;
                        break;

                }
        }
        if (flag==0){
        printf("The number is prime");

        snprintf(buffer,255,"\n the factors are %d and 1",num);
        sendto(server_socket,buffer,sizeof(buffer),0,(struct sockaddr *)&caddr,caddrsize);
        }
        close(server_socket);
}

