//client.c
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
//#include<time.h>
#include<unistd.h>
//#define port 12000

int main()
{
        char b[1024];
        //struct sockaddr_in caddr;
        socklen_t caddrsize;
        int client_socket;


        client_socket=socket(AF_INET,SOCK_DGRAM,0);
        struct sockaddr_in caddr={AF_INET,htons(5555),{inet_addr("127.0.0.1")}};
        //bind(server_socket,(struct sockaddr *)&saddr,sizeof(saddr));
        caddrsize=sizeof(caddr);
        while(1)
        {
                bzero(b,1024);
                printf("Enter 'TIME' if you want the time from server else 'end'\n");
                fgets(b,sizeof(b),stdin);
                sendto(client_socket,b,strlen(b),0,(struct sockaddr *)&caddr,caddrsize);

                if(strncmp(b,"end",3)==0)
                {
                        printf("disconnected");
                        close(client_socket);
                        break;
                }

                recvfrom(client_socket,b,sizeof(b),0,(struct sockaddr *)&caddr,&caddrsize);
                //printf("receieved time request from %d:%s" ,inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
                //time_t now=time(NULL);
                //char * timestr=ctime(&now);
                //int timelen=strlen(timestr);
                //sendto(server_socket,timestr,timelen,0,(struct sockaddr *)&caddr,caddrsize);
                printf("Time is %s\n",b);


        }
        close(client_socket);
        return 0;

}




$ cat exp7server.c
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<time.h>
#include<unistd.h>
//#define port 12000

int main()
{
        char b[1024];
        struct sockaddr_in caddr;
        socklen_t caddrsize;
        int server_socket;

        server_socket=socket(AF_INET,SOCK_DGRAM,0);
        struct sockaddr_in saddr={AF_INET,htons(5555),{INADDR_ANY}};
        bind(server_socket,(struct sockaddr *)&saddr,sizeof(saddr));
        caddrsize=sizeof(caddr);
        while(1)
        {
                bzero(b,1024);
                recvfrom(server_socket,b,sizeof(b),0,(struct sockaddr *)&caddr,&caddrsize);
                //fgets(b,sizeof(b),stdin);
                if(strncmp(b,"TIME",4)==0)
                {
                printf("receieved time request from %s:%d\n" ,inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
                time_t now=time(NULL);
                char * timestr=ctime(&now);
                int timelen=strlen(timestr);
                sendto(server_socket,timestr,timelen,0,(struct sockaddr *)&caddr,caddrsize);
                printf("sent\n");
                }
                else if(strncmp(b,"end",3)==0)
                {
                        printf("disconnected");
                        break;
                        close(server_socket);
                }


        }
        close(server_socket);
        return 0;

}
