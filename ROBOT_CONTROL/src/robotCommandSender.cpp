// rosnode to send commands to robot
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "MESSAGES/order.h"
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
bool sysPause = false;

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

void pauseCallback(const std_msgs::Bool::ConstPtr& msg)
{
	sysPause=msg->data;
}

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "robotCommandSender");
	ros::NodeHandle h;
 	ros::Publisher readyPub = h.advertise<std_msgs::String>("/robotReady", 10);
 	ros::Subscriber sub = h.subscribe("/newConfig", 10, configCallback);
 	ros::Subscriber convStopSub = h.subscribe("/conveyerStopped", 10, convStopCallback);
 	ros::Subscriber pauSub = h.subscribe("/systemPause", 10, pauseCallback);
 	ros::Publisher failPub = h.advertise<MESSAGES::order>("/failedPickup", 20);

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

    ros::Rate loop_rate(5);



    //list.push_back("( 0.032 , -0.032 , 0 , 0 , 0 , 0.09, 1,)");
    //list.push_back("( 0.018 , 0.053 , 0 , 0 , 0 , -0.13, 1,)");
    //list1.push_back("( 0.022 , -0.007 , 0 , 0 , 0 , 1.28, 1,)");
    //list1.push_back("( 0.011 , 0.053 , 0 , 0 , 0 , 1.54, 1,)");
    //list1.push_back("( -0.028 , -0.03 , 0 , 0 , 0 , 0.2 , 1,)");
    //list1.push_back("( -0.035 , 0.058 , 0 , 0 , 0 , -0.4 , 1,)");
    int ready = 1;
    int failColor=-1;
    int failOrder=-1;
	std_msgs::String message;
//	message.data="0";
	///readyPub.publish(message);


	while (ros::ok())
	{
		if(conveyerStopped==1 && (sysPause==false)){
			if(!list1.empty()){
				if(ready==1){
					message.data="0"; // conveyer may not move
					readyPub.publish(message);
					string temp = list1.back();
					list1.pop_back();
					temp.append("\n");
					const char* msg = temp.c_str();
					n = write(newsockfd,msg,strlen(msg));
					cout<< "wrote: " << msg << endl;
					cout << "picked up: " << atoi(temp.substr(temp.size()-6,1).c_str()) << " , " << atoi(temp.substr(temp.size()-3,1).c_str()) << endl;
				    failColor=atoi(temp.substr(temp.size()-6,1).c_str());
				    failOrder=atoi(temp.substr(temp.size()-3,1).c_str());
					if (n < 0) error("ERROR writing to socket");

					ready=0;
				}
			}
			else{
				if(ready==1){
					cout << "conveyor move" << endl;
					conveyerStopped=0;
					message.data="1"; // conveyer may move
					readyPub.publish(message);
				}
			}
		}


		n=read(newsockfd,buffer,5);

		ready=atoi(buffer);

		cout << buffer << " , " << ready << endl;

		//bzero(buffer,256);

		if(ready==3){
			cout << "FAIL" << endl;
			string temp = ("(1)");
			temp.append("\n");
			const char* msg = temp.c_str();
			n = write(newsockfd,msg,strlen(msg));

			MESSAGES::order fail;
			if(failColor==0){
				fail.red=1;
				fail.blue=0;
				fail.yellow=0;
			}
			else if(failColor==1){
				fail.red=0;
				fail.blue=1;
				fail.yellow=0;
			}
			else if(failColor==2){
				fail.red=0;
				fail.blue=0;
				fail.yellow=1;
			}
			fail.slider=failOrder;
			failPub.publish(fail);
		}
	    failColor=-1;
	    failOrder=-1;

		ros::spinOnce();
		loop_rate.sleep();
	}



    cout << "a" << endl;
    close(newsockfd);
    cout << "b" << endl;

    close(sockfd);
    return 0;
}
