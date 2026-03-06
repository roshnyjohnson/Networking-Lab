//client.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>


int main()

{
        int client_socket;
        int tot=0;
        char buff[1024],reply[1024];
        client_socket=socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in saddr={AF_INET,htons(5555),inet_addr("127.0.0.1")};
        connect(client_socket,(struct sockaddr *)&saddr,sizeof(saddr));
         srand(time(0));

        while(tot<8)
        {
                if(read(client_socket,buff,sizeof(buff))>0)
                {
                        char id=buff[strlen(buff)-1];
                        printf("\nRecieved %s\n",buff);

                        if(rand()%4>2)
                        {
                                printf("\npacket dropped.Sending NACK %c\n",id);
                                sprintf(buff,"nACK %c",id);
                        }
                        else{
                                printf("oK Sending Ack %c\n",id);
                                sprintf(buff,"ACK %c",id);
                                tot++;
                        }
                        write(client_socket,buff,sizeof(buff));
                }
        }
        close(client_socket);
}



//server.c

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<string.h>
#include<arpa/inet.h>

int main(){

        int server_socket,client_socket;
        char buff[1024],reply[1024];
        server_socket=socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in saddr={AF_INET,htons(5555),INADDR_ANY},caddr;
        bind(server_socket,(struct sockaddr *)&saddr,sizeof(saddr));
        listen(server_socket,5);
        client_socket=accept(server_socket,NULL,NULL);
        int tot=0,j,k,win=3;
        struct timeval tv={2,0};
        setsockopt(client_socket,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
        while(tot<8)
        {
                for(j=tot;j<win+tot&&j<8;j++){
                        sprintf(buff,"Packet %d",j);
                        printf("Sending %s\n",buff);
                        write(client_socket,buff,sizeof(buff));


                }
                for(k=0;k<win&&tot<8;k++)
                {
                        int n=read(client_socket,buff,sizeof(buff));

                        if(n<=0){
                                printf("TIMEOUT !Retrsnsmitting packet %d",tot);
                                sprintf(buff,"Packet %d",tot);
                                k--;
                                write(client_socket,buff,sizeof(buff));

                        }
                        else if(buff[0]=='n')
                        {
                                printf("Recieved NACK for %s \nResending\n",buff);
                                int nack_id=buff[strlen(buff)-1]-'0';
                                sprintf(buff,"Packet %d",nack_id);
                                k--;
                                write(client_socket,buff,sizeof(buff));

                        }
                        else{
                                printf("Successfully Recieved %s\n",buff);
                                tot++;
                        }
                }
        }
        close(client_socket);
        close(server_socket);
}

