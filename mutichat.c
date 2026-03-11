multichat server
client same as the tcp unidirectional client


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#define port 8080
#define MAX_CLIENTS 10

int cc=0;

void *hc(void * arg)
{
   int csock=*((int *)arg);
   free(arg);

   char b[1024];
   int id=++cc;
   while(1)
   {
      bzero(b,1024);
      recv(csock,b,sizeof(b),0);
      if(strncmp(b,"exit",4)==0){printf("client %d disconnected\n",id);close(csock);break;}
      printf("Client %d:%s",id,b);
    }
    return NULL;
}

void main()
{
   int ssock;
   struct sockaddr_in addr;
   ssock=socket(AF_INET,SOCK_STREAM,0);
   memset(&addr,0,sizeof(addr));
   addr.sin_family=AF_INET;
   addr.sin_port=htons(port);
   addr.sin_addr.s_addr=inet_addr("127.0.0.1");
   bind(ssock,(struct sockaddr*)&addr,sizeof(addr));
   printf("Binded\n");
   listen(ssock,MAX_CLIENTS);
   printf("Listening\n");
   while(1)
   {
      int *csock=malloc(sizeof(int));
      struct sockaddr_in caddr;
      socklen_t len=sizeof(caddr);

       *csock=accept(ssock,(struct sockaddr *)&caddr,&len);
       printf("New client connected\n");

        pthread_t tid;
        pthread_create(&tid,NULL,hc,(void *)csock);
        pthread_detach(tid);
   }
}
