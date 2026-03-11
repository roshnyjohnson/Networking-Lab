//client


                
$ cat exp8client.c
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include<string.h>
#include<unistd.h>

typedef struct{

        int seq_no,ack_no;
        char data[1024];
}Frame;

int main()
{
        int n,server_socket,seq=0,i=0;
        //struct sockaddr_in caddr;
        Frame frame;
        server_socket=socket(AF_INET,SOCK_DGRAM,0);
        struct sockaddr_in saddr={AF_INET,htons(5555),{inet_addr("127.0.0.1")}};
        struct timeval tv={2,0};
        //bind(server_socket,(struct sockaddr *)&saddr,sizeof(saddr));

        socklen_t saddrsize=sizeof(saddr);
        setsockopt(server_socket,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
        while(i<5)
        {
                frame.seq_no=seq;
                sprintf(frame.data,"Packet %d",i);
                sendto(server_socket,&frame,sizeof(Frame),0,(struct sockaddr *)&saddr,sizeof(saddr));
                printf("Sent frame:%d with data:%s\n",seq,frame.data);
//              sendto(server_socket,&frame,sizeof(Frame),0,(struct sockaddr *)&caddr,caddrsize);


                n=recvfrom(server_socket,&frame,sizeof(Frame),0,(struct sockaddr *)&saddr,&saddrsize);
                if(n<0)
                {
                        printf("TIMEOUT, retransmitting...\n");

                }
                else if(frame.ack_no==seq)
                {
                        printf("ACK %d recieved.Move to next packet\n",seq);
                        seq=1-seq;
                        i++;
                }
//                sendto(server_socket,&frame,sizeof(Frame),0,(struct sockaddr *)&caddr,caddrsize);
                sleep(1);

        }
        close(server_socket);
        return 0;
}


ASUS@DESKTOP-SFADVSU /cygdrive/e/cn lab
$ cat exp8server.c
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<time.h>
#include<string.h>
#include<unistd.h>

typedef struct{

        int seq_no,ack_no;
        char data[1024];
}Frame;

int main()
{
        int server_socket,exp_seq=0;
        struct sockaddr_in caddr;
        Frame frame;
        server_socket=socket(AF_INET,SOCK_DGRAM,0);
        struct sockaddr_in saddr={AF_INET,htons(5555),{INADDR_ANY}};
        bind(server_socket,(struct sockaddr *)&saddr,sizeof(saddr));
        socklen_t caddrsize=sizeof(caddr);
        while(1)
        {
                recvfrom(server_socket,&frame,sizeof(Frame),0,(struct sockaddr *)&caddr,&caddrsize);
                if ((rand()%10)<4)
                {
                        printf("\nerror occured. the packet is dropped");
                        continue;
                }
                printf("Recieved frame:%d with data:%s\n",frame.seq_no,frame.data);
                if(frame.seq_no==exp_seq)
                {
                        printf("Accepted the frame,sending ACK %d\n",exp_seq);
                        frame.ack_no=exp_seq;
                        exp_seq=1-exp_seq;
                }
                else{
                        printf("Duplicate->resending ACK %d\n",frame.seq_no);
                        frame.ack_no=frame.seq_no;

                }
                sendto(server_socket,&frame,sizeof(Frame),0,(struct sockaddr *)&caddr,caddrsize);


        }
        close(server_socket);
        return 0;
}

