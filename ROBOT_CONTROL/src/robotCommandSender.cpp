// rosnode to send commands to robot
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
#include <vector>

using namespace std;
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "robotCommandSender");
	ros::NodeHandle h;
	
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
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
    		sizeof(serv_addr)) < 0){
            error("ERROR on binding");
    	 	std::cout << "5"<< std::endl;
    }

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
    				(struct sockaddr *) &cli_addr,
    				&clilen);
    if (newsockfd < 0){
         error("ERROR on accept");
    }

    bzero(buffer,256);

    ros::Rate loop_rate(10);

    vector<string> list;

    list.push_back("( 0.05 , 0.00 , 0 , 0 , 0 , 0, 1,)");
    list.push_back("( 0.00 , 0.05 , 0 , 0 , 0 , 0.78, 2,)");
    list.push_back("( -0.05 , 0.00 , 0 , 0 , 0 , 1.57, 1,)");
    list.push_back("( 0.00 , -0.05 , 0 , 0 , 0 , -0.78, 2,)");
    int ready =1;

    while (ros::ok())
    {
    	if(ready==1){
			if(!list.empty()){
				string temp = list.back();
				list.pop_back();
				std::cout << temp << std::endl;
				const char* msg = temp.c_str();
				//const char* msg ="( 0.05 , 0.05 , 0 , 0 , 0 , 0, 1,)";
				n = write(newsockfd,msg,strlen(msg));
				// const char* msg ="( -0.431 , -0.607 , 0.066 , 1.06 , -2.9 , 0.03 )";

				if (n < 0) error("ERROR writing to socket");

				//sleep(2);
				//const char* msg1 ="( 0.05 , 0.05 , 0 , 0 , 0 , 0, 2)";
				//n = write(newsockfd,msg1,strlen(msg1));
				ready=false;
			}
    	}

    	n=read(newsockfd,buffer,5);
    	//cout << n << endl;
    	//cout << buffer << endl;
     	cout << buffer << endl;
    	ready=atoi(buffer);

		ros::spinOnce();
		loop_rate.sleep();
    }

	/*n=0;
	bzero(buffer,256);
	while(true){	
     		sleep(2);
    		n = read(newsockfd,buffer,5);
 		ROS_INFO("%s", buffer);
		//cout << buffer << endl;
		//cout << n << endl;
		if(n>0){
			const char* msg1 ="( 0.05 , 0.05 , 0 , 0 , 0 , 0, 2)";
			n = write(newsockfd,msg1,strlen(msg1));
			std::cout << "lala2"<< std::endl;
			break;
		}
	}*/

    cout << "a" << endl;
    close(newsockfd);
    cout << "b" << endl;

    close(sockfd);
    return 0;
}
