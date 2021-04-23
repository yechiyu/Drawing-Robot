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
        
int speeds = 70;
bool dir1,dir2;
double speed1,speed2;
        // string url = "../img/1.jpg";

int counts1 = 0; //the encoders give motor positions in counts
int counts2 = 0;

double targetX; // target x
double targetY;  // target y

double la = 0;
double lb = 0;

string filename1 = "";

#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define MAX_SIZE 32
void error(const char *msg){
    perror(msg);
    exit(1);
}

double currrentX, currrentY, initialX, initialY;
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


	 string fileAddr = "/var/www/html/WebUI/storeImg/";
	 string filenamed = "";
        
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
             string buffered = buffer; 
             
             if (buffered.substr(0,2) == "Le" ){
                 cout << "This commond is:"<< buffered << endl;
             }else if (buffered.substr(0,2) == "Ri" ){
                 cout << "This commond is:"<< buffered << endl;
             }else if (buffered.substr(0,2) == "Up" ){
                cout << "This commond is:"<< buffered << endl;
             }else if (buffered.substr(0,2) == "Do" ){
                cout << "This commond is:"<< buffered << endl;
             }else if (buffered.substr(0,2) == "dr" ){
                cout << "Now starting drawing it:"<< endl;
		cout << "la is :"<< la << endl;
		cout << "lb is :"<< la << endl;
		cout << "file directory is :"<< fileAddr+filenamed << endl;
             }else if (buffered.substr(0,2) == "St" ){
                cout << "This commond is:"<< buffered << endl;
             }else if (buffered.substr(0,2) == "Pl" ){
                cout << "This commond is:"<< buffered << endl;
             }else if (buffered.substr(0,2) == "la" ){
		string buferedla = buffered.substr(2);
		la = atof(buferedla.c_str());
                cout << "input la:"<< la << endl;
             }else if (buffered.substr(0,2) == "lb" ){
		string buferedlb = buffered.substr(2);
		lb = atof(buferedlb.c_str());
                cout << "input lb:"<< lb << endl;
             }else{
		 filenamed = buffered;
                 cout << "file name:"<< buffered << endl;
             }

             close(newsockfd);
         }
         close(sockfd);
         return 0;
}
