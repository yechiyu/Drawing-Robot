#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
using namespace std;

#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define MAX_SIZE 32
void error(const char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     ifstream t("bishop.obj");
     string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     // Create a socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");

     // Fill in the address structure containing self address
     // Bind the socket to the address
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
              error("ERROR on binding");

     // Listen for connection
     listen(sockfd, 5);
     clilen = sizeof(cli_addr);
    
     while (1) {
	int fd;
    	double temp = 0;
    	char buf[MAX_SIZE];

	fd = open(TEMP_PATH, O_RDONLY);
    	if (fd < 0) {
        	fprintf(stderr, "failed to open thermal_zone0/temp\n");
        	return -1;
    	}
    
    	if (read(fd, buf, MAX_SIZE) < 0) {
        	fprintf(stderr, "failed to read temp\n");
        	return -1;
    	}
    
   	temp = atoi(buf) / 1000.0;
    	string tempstr = to_string(temp);	
     	// Accept a connection
     	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     	if (newsockfd < 0)
          	error("ERROR on accept");

     	bzero(buffer,256);

     	// Send data
     	n = write(newsockfd, tempstr.c_str(), tempstr.length());
     	if (n < 0) error("ERROR writing to socket");

     	// Receive data
     	n = read(newsockfd,buffer,255);
     	if (n < 0) error("ERROR reading from socket");
     	printf("Here is the reply: %s\n",buffer);

     	close(newsockfd);
     } 
     close(sockfd);
     return 0;
}
