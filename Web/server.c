#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

main(){
     int sock;
     struct sockaddr_in server,client;
     int recvd,snd;
     int structlength;
     char * server_ip = "128.168.10.1";/*server ip address*/
     int port = 8888;
     char recvbuf[2000],sendbuf[2000];  

     char str1[]="I have received:\n";

     memset((char *)&server,0,sizeof(server));
     server.sin_family = AF_INET;
     server.sin_addr.s_addr = inet_addr(server_ip);
     server.sin_port = htons(port);

     memset((char *)&client,0,sizeof(client));
     client.sin_family = AF_INET;
     client.sin_addr.s_addr = htonl(INADDR_ANY);
     client.sin_port = htons(port);
  
     if((sock = socket (AF_INET,SOCK_DGRAM,0)) < 0 ){
         printf("socket create error!\n");
         exit(1);
     }  
     structlength = sizeof(server);
     if( bind(sock,(struct sockaddr *) &server,structlength) < 0){
         printf("socket bind error!\n");
         perror("bind");
         exit(1);
     }

     while(1){
         structlength = sizeof(client);  
            
         printf("waiting.......\n");
         recvd = recvfrom(sock,recvbuf,sizeof(recvbuf),0,
             (struct sockaddr *) & client,&structlength);
         if(recvd < 0){
             perror("recvfrom");
             exit(EXIT_FAILURE);  
         }
         else{
             printf("received:%s\n",recvbuf);
        
             memset(sendbuf,0,strlen(sendbuf));
             memcpy(sendbuf,str1,strlen(str1));
                    
             snd = sendto(sock,sendbuf,strlen(str1),0,
             (struct sockaddr *) &client,structlength);

             if(snd < 0){
             perror("sendto");
             exit(1);
             }
             printf("sendok!\n");
         }          
     }        
     close(sock);
}