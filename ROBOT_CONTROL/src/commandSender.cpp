/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include "ros/ros.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

using namespace std;
void error(const char *msg)
{
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
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0){
        error("ERROR opening socket");
        std::cout << "2"<< std::endl;
     }
     std::cout << "3"<< std::endl;

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     std::cout << "4"<< std::endl;
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0){
              error("ERROR on binding");
     	 	 std::cout << "5"<< std::endl;
     }
     std::cout << "6"<< std::endl;

     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);
     if (newsockfd < 0){
          error("ERROR on accept");
     	 std::cout << "7"<< std::endl;
     }

     bzero(buffer,256);
     std::cout << "8"<< std::endl;

     //n = read(newsockfd,buffer,255);
     if (n < 0){
    	 error("ERROR reading from socket");
    	 std::cout << "9"<< std::endl;
     }

     std::cout << "lala"<< std::endl;

     const char* msg ="( -0.42083 , -0.060095 , 0.0027 , 1.85 , -2.42 , 0024 )";
     /*char *tmp = strchr(msg, '\0');
     std::cout << "lala"<< std::endl;

     if (tmp) *tmp = '\0';*/
      	 n = write(newsockfd,msg,strlen(msg));
     if (n < 0) error("ERROR writing to socket");

     std::cout << "1"<< std::endl;

     sleep(2);
     std::cout << "2"<< std::endl;

     const char* msg1 ="( -0.0435 , -0.0346 , 0.0027 , 2.28 , -2.1 , 098 )";
     n = write(newsockfd,msg1,strlen(msg1));
     std::cout << "lala2"<< std::endl;


     close(newsockfd);
     close(sockfd);
     return 0;
}
