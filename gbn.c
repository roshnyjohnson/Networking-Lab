$ cat gbnclient.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>
#include<sys/select.h>

int main()
{

        int client_socket;
        client_socket=socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in caddr={AF_INET,htons(5555),inet_addr("127.0.0.1")};
        connect(client_socket,(struct sockaddr *)&caddr,sizeof(caddr) );
        int base=0;int next=0,ack;
        while(base<5)
        {
                while(next<base+4&&next<5)
                {
                        printf("Sending frame %d\n",next);
                        send(client_socket,&next,sizeof(next),0);
                        next++;
                }
                fd_set readfds;
                struct timeval tv={2,0};
                FD_ZERO(&readfds);
                FD_SET(client_socket,&readfds);

                int activity=select(client_socket+1,&readfds,NULL,NULL,&tv);
                if(activity>0)
                {
                        recv(client_socket,&ack,sizeof(ack),0);
                        printf("\nRecieved acknowledgemnt %d\n ",ack);
                        base=ack+1;

                }
                else{
                        printf("Timeout,resending frame %d",base);
                        next=base;
                }
        }
        //int end=-1;
        //send(client_socket,&end,sizeof(end),0);
        close(client_socket);
        return 0;
}






$ cat gbnserver.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<time.h>

int main()
{

        int loss,server_socket,client_socket;
        //struct sockaddr_in addr;
        socklen_t addrsize;
        int frame,ack,expected=0;
        srand(time(NULL));
        server_socket=socket(AF_INET,SOCK_STREAM,0);
        if(server_socket<0)
        {
                printf("Error in creating server socket!\n");
                return 0;
        }
        printf("Server socket created successfully!\n");
        struct sockaddr_in addr={AF_INET,htons(5555),INADDR_ANY};
        addrsize=sizeof(addr);
        bind(server_socket,(struct sockaddr*)&addr,sizeof(addr));
        listen(server_socket,5);
        client_socket=accept(server_socket,(struct sockaddr *)&addr,&addrsize);
        while(1)
        {
                recv(client_socket,&frame,sizeof(frame),0);
                //if(frame==-1)
                //{
        //              break;
        //      }
                printf("\nRecieved frame %d\n",frame);
                if(frame==expected)
                {

                        loss=rand()%3;
                        if(loss==0)
                        {
                                printf("lost frame %d",frame );
                        }
                        else{
                                ack=frame;
                                printf("sending ACK %d",ack);
                                send(client_socket,&ack,sizeof(ack),0);
                                expected++;
                        }

                }
                else{
                        ack=expected-1;
                        printf("\nOut of order.sending last nack %d\n",ack);
                        send(client_socket,&ack,sizeof(ack),0);

                }
        }
        close(client_socket);
        close(server_socket);

}

