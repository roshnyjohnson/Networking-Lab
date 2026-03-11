#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int server_socket;
    int r1,c1,r2,c2;
    int A[10][10],B[10][10],C[10][10];

    struct sockaddr_in saddr,caddr;
    socklen_t caddrsize=sizeof(caddr);

    server_socket=socket(AF_INET,SOCK_DGRAM,0);

    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(5555);
    saddr.sin_addr.s_addr=INADDR_ANY;

    bind(server_socket,(struct sockaddr*)&saddr,sizeof(saddr));

    recvfrom(server_socket,&r1,sizeof(r1),0,(struct sockaddr*)&caddr,&caddrsize);
    recvfrom(server_socket,&c1,sizeof(c1),0,(struct sockaddr*)&caddr,&caddrsize);
    recvfrom(server_socket,&r2,sizeof(r2),0,(struct sockaddr*)&caddr,&caddrsize);
    recvfrom(server_socket,&c2,sizeof(c2),0,(struct sockaddr*)&caddr,&caddrsize);

    recvfrom(server_socket,A,sizeof(A),0,(struct sockaddr*)&caddr,&caddrsize);
    recvfrom(server_socket,B,sizeof(B),0,(struct sockaddr*)&caddr,&caddrsize);

    for(int i=0;i<r1;i++)
        for(int j=0;j<c2;j++)
        {
            C[i][j]=0;
            for(int k=0;k<c1;k++)
                C[i][j]+=A[i][k]*B[k][j];
        }

    sendto(server_socket,C,sizeof(C),0,(struct sockaddr*)&caddr,caddrsize);

    close(server_socket);
}



//server
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int server_socket;
    int r1,c1,r2,c2;
    int A[10][10],B[10][10],C[10][10];

    struct sockaddr_in saddr,caddr;
    socklen_t caddrsize=sizeof(caddr);

    server_socket=socket(AF_INET,SOCK_DGRAM,0);

    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(5555);
    saddr.sin_addr.s_addr=INADDR_ANY;

    bind(server_socket,(struct sockaddr*)&saddr,sizeof(saddr));

    recvfrom(server_socket,&r1,sizeof(r1),0,(struct sockaddr*)&caddr,&caddrsize);
    recvfrom(server_socket,&c1,sizeof(c1),0,(struct sockaddr*)&caddr,&caddrsize);
    recvfrom(server_socket,&r2,sizeof(r2),0,(struct sockaddr*)&caddr,&caddrsize);
    recvfrom(server_socket,&c2,sizeof(c2),0,(struct sockaddr*)&caddr,&caddrsize);

    recvfrom(server_socket,A,sizeof(A),0,(struct sockaddr*)&caddr,&caddrsize);
    recvfrom(server_socket,B,sizeof(B),0,(struct sockaddr*)&caddr,&caddrsize);

    for(int i=0;i<r1;i++)
        for(int j=0;j<c2;j++)
        {
            C[i][j]=0;
            for(int k=0;k<c1;k++)
                C[i][j]+=A[i][k]*B[k][j];
        }

    sendto(server_socket,C,sizeof(C),0,(struct sockaddr*)&caddr,caddrsize);

    close(server_socket);
}
