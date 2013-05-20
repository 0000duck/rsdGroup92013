// rosnode to send commands to robot
#include "ros/ros.h"
#include "std_msgs/String.h"
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

vector<string> list1;
int conveyerStopped = 1;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void configCallback(const std_msgs::String::ConstPtr& msg)
{
	list1.push_back(msg->data);
	std::cout << "rec" << list1.back() << endl;
}

void convStopCallback(const std_msgs::String::ConstPtr& msg)
{
	conveyerStopped=atoi(msg->data.c_str());
}

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "robotCommandSender");
	ros::NodeHandle h;
 	ros::Publisher readyPub = h.advertise<std_msgs::String>("robotReady", 1);
 	ros::Subscriber sub = h.subscribe("newConfig", 10, configCallback);
 	ros::Subscriber convStopSub = h.subscribe("conveyerStopped", 10, convStopCallback);
	
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



    //list.push_back("( 0.032 , -0.032 , 0 , 0 , 0 , 0.09, 1,)");
    //list.push_back("( 0.018 , 0.053 , 0 , 0 , 0 , -0.13, 1,)");
    //list1.push_back("( 0.022 , -0.007 , 0 , 0 , 0 , 1.28, 1,)");
    //list1.push_back("( 0.011 , 0.053 , 0 , 0 , 0 , 1.54, 1,)");
    //list1.push_back("( -0.028 , -0.03 , 0 , 0 , 0 , 0.2 , 1,)");
    //list1.push_back("( -0.035 , 0.058 , 0 , 0 , 0 , -0.4 , 1,)");
    int ready = 2;
	std_msgs::String message;
//	message.data="0";
	///readyPub.publish(message);

    while (ros::ok())
    {
    	if(conveyerStopped==1){
			if(!list1.empty()){
				if(ready==1){
					cout << "write" << endl;
					message.data="0"; // conveyer may not move
					//ROS_INFO("%s", message.data.c_str());
					readyPub.publish(message);
					string temp = list1.back();
					list1.pop_back();
					temp.append("\n");
					const char* msg = temp.c_str();
					//const char* msg ="( 0.05 , 0.05 , 0 , 0 , 0 , 0, 1,)";
					n = write(newsockfd,msg,strlen(msg));

					if (n < 0) error("ERROR writing to socket");

					ready=0;
				}
			}
			else{
				conveyerStopped=0;
				if(ready==2){
					message.data="1"; // conveyer may move
					readyPub.publish(message);
				}
			}
    	}
		n=read(newsockfd,buffer,5);

		ready=atoi(buffer);
		cout << "GUIUHJHIOFGYIOG " << ready << endl;

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
