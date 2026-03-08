//gcc exp12server.c -o server
//gcc exp12client.c -o client
//./server
//./client


//client.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

int main(){
        int server_socket;
        server_socket=socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in  saddr={AF_INET,htons(8888),inet_addr("127.0.0.1")};
        connect(server_socket,(struct sockaddr *)&saddr,sizeof(saddr));
        char buff[1024],fname[256];


        printf("Enter the filename\n");
        scanf("%s",fname);
        send(server_socket,fname,strlen(fname),0);

        int n=recv(server_socket,buff,sizeof(buff)-1,0);buff[n]='\0';
        printf("%s",buff);
        close(server_socket);

}
//server.c


#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
        int server_socket,client_socket;
        server_socket=socket(AF_INET,SOCK_STREAM,0);
        if(server_socket<0){
                perror("Socket error");
                exit(1);
        }
        struct sockaddr_in saddr={AF_INET,htons(8888),INADDR_ANY},caddr;
        //socklen_t caddrsize;

        if(bind(server_socket,(struct sockaddr *)&saddr,sizeof(saddr))<0)
        {perror("bind failed");}
        listen(server_socket,5);
        printf("Server started on port 5555\n");

        char  buff[1024],content[2048],fname[256];
        while(1)
        {
                client_socket=accept(server_socket,NULL,NULL);
                printf("Client connected\n");
                if(fork()==0){
                        close(server_socket);
                        int n=recv(client_socket,fname,sizeof(fname)-1,0);fname[n]='\0';
                        if(n<=0){
                                exit(0);
                        }
                        FILE *fp =fopen(fname,"r");
                        if (fp!=NULL)
                        {
                                n=fread(content,1,2047,fp);content[n]='\0';
                                snprintf(buff,sizeof(buff),"[PID: %d]:The content of the file %s is \n %s",getpid(),fname,content);
                                fclose(fp);
                        }
                        else{

                                 snprintf(buff,sizeof(buff),"[PID:%d]:No file exits in the said name",getpid());
                        }
                        send(client_socket,buff,strlen(buff),0);
                        printf("[PID :%d] Response sent\n",getpid());
                        close(client_socket);
                        exit(0);
                }
                        close(client_socket);
                        //exit(0);
        }
        close(client_socket);
}



