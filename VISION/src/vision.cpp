#include "ros/ros.h"
#include "std_msgs/String.h"
#include "MESSAGES/order.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <strstream>



#define CAPTURE_DEVICE	0



#define PI 3.14159265359
#define scale 0.000195 //Conversion from pixel to meter in the image. Calculated by actual size in meters of the image divided by the resolution
#define offsetX -0.125 //Move the origo (0,0) position from the upper left corner to the center of the image
#define offsetY -0.07 //in both directions. The image size is 0.25 by 0.14 meters
#define blueMin    5000
#define blueMax   12000
#define redMin    17000
#define redMax    24000
#define yellowMin 27000//16000
#define yellowMax 36000//24000
#define RED 0
#define BLUE 1
#define YELLOW 2


using namespace std;
using namespace cv;

int conveyerStopped = 1;
int robReady = 0;
int wantedRed =0;
int wantedBlue=0;
int wantedYellow=0;
int currentOrder=-1;
int countPub=0;

struct sendCommand{
	string s;
	int color;
};


vector<sendCommand> list1;

string constructCommand(double xPos, double yPos, double angle, int color, int slider){
	ostringstream s;
	string temp="(";
	string temp2;

	s.str(string());
	s << xPos;
	temp2=s.str();
	temp.append(temp2);
	temp.append(", ");

	s.str(string());
	s << yPos;
	temp2=s.str();
	temp.append(temp2);
	temp.append(", 0, 0, 0, ");

	s.str(string());
	s << angle;
	temp2=s.str();
	temp.append(temp2);
	temp.append(", ");

	s.str(string());
	s << color;
	temp2=s.str();
	temp.append(temp2);
	temp.append(", ");

	return temp;
}

void colorFilter(const Mat& src, Mat& bw)
{
    assert(src.type() == CV_8UC3);
    Mat colors, red, yellow, blue;
    GaussianBlur( src, src, Size(3, 3), 2, 2 );
  	inRange(src, Scalar(  0, 50, 75), Scalar(25, 255, 255), red);	//Red lower
  	inRange(src, Scalar( 14, 200, 130), Scalar(34, 255, 255), yellow);	//Yellow
  	inRange(src, Scalar( 90, 5, 15), Scalar(160, 255, 255), blue);	//Blue

  	colors = red + yellow + blue;

  	//Noise removal
  	Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
  	Mat element1 = getStructuringElement(MORPH_RECT, Size(25, 25));
  	imwrite("colors.png", colors);
  	dilate(colors,colors,element1);
  	imwrite("dialate.png", colors);
  	erode(colors,bw,element);
}


void getBricks(Mat& imgEdge, Mat& imgROI, ros::Publisher seenPub){
		Mat imgCon;

	//Vectors for storing the connected components in:
		vector < vector <cv::Point> > contours, contours1;
		imgCon = imgEdge.clone(); //Take a copy of the edges for extracting the contours
		findContours(imgCon, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0)); //sizeLeft offset is needed because some of the image was cut out
		Mat overlayed = Mat::zeros(imgROI.size(),imgROI.type());
		drawContours(overlayed, contours, -1, Scalar(255,255,255), CV_FILLED, 8);  //
		overlayed &= imgROI;


		//Remove contours that is to small og big for being a LEGO brick
		for(int i=0; i<contours.size(); i++)
		{

			//if (contourArea(Mat(contours[i]))<yellowMax && contourArea(Mat(contours[i]))>blueMin)
			//{
				cout << "fafla: " << contourArea(Mat(contours[i])) << endl;
				contours1.push_back(contours[i]);
			//}
		}
		//cout << "Number of detected LEGO bricks: " << contours1.size() << endl;

		int color=0;
		RotatedRect rectangle;
		RotatedRect ellipse;
		int blue=0;
		int red=0;
		int yellow=0;
		int count = 0;
		for(int i=0; i<contours1.size(); i++)
		{
			cout << "Area of brick: " << contourArea(Mat(contours1[i])) << endl;
			int aera = int(contourArea(Mat(contours1[i])));
			rectangle = minAreaRect(Mat(contours1[i]));
			//ellipse = fitEllipse(Mat(contours1[i])); //Used since the rectangle.angle is only in the range 0...-90 degrees

			//the camera and the robot have different coordinatesystems, therefore the x and y positions are changed and they are both negated.
			double xPos = -(rectangle.center.y*scale+offsetY);
			double yPos = -(rectangle.center.x*scale+offsetX);
			//Angle is calculated from the fitted elipse in order to get the angle in the interval 0-180degrees, this is converted to radians, and PI/2 is subtracted to have the minimum rotation of the gripper tool
			//double angle = ellipse.angle*PI/180-PI;

			/*if(angle<-PI/2)
			{
			angle=angle+PI;
			}*/


			int slider=1;
			//constructCommand(xPos, yPos, angle, slider);

			sendCommand temp;
			if(aera<blueMax && aera>blueMin) //Blue
			{ //list.push_back("( 0.018 , 0.053 , 0 , 0 , 0 , -0.13, 1,)");
				color=1;
				double angle = rectangle.angle*PI/180-PI;
				if(angle<-PI/2)
					{
					angle=angle+PI;
					}
				cout << "Color: " <<color << " Center (m): " <<xPos <<","<< yPos << " Angle (rad): " << angle << endl;
				if(angle<PI/2 && angle>-PI/2){
					if(angle>PI/4)
						angle-=PI/2;
					temp.s=constructCommand(xPos, yPos, angle, BLUE,slider);
					temp.color=BLUE;
					list1.push_back(temp);
					blue++;
					count++;
				}
			}
			else if (aera<redMax && aera>redMin) //Red
			{
				color=2;
				ellipse = fitEllipse(Mat(contours1[i])); //Used since the rectangle.angle is only in the range 0...-90 degrees
				double angle = ellipse.angle*PI/180-PI;
				if(angle<-PI/2)
					{
					angle=angle+PI;
					}
				if(angle<PI/2 && angle>-PI/2){
					cout << "Color: " <<color << " Center (m): " <<xPos <<","<< yPos << " Angle (rad): " << angle << endl;
					temp.s=constructCommand(xPos, yPos, angle, RED,slider);
					temp.color=RED;
					list1.push_back(temp);
					red++;
					count++;
				}
			}
			else if (aera>yellowMin) //Yellow
			{
				color=3;
				ellipse = fitEllipse(Mat(contours1[i])); //Used since the rectangle.angle is only in the range 0...-90 degrees
				double angle = ellipse.angle*PI/180-PI;
				if(angle<-PI/2)
					{
					angle=angle+PI;
					}
				if(angle<PI/2 && angle>-PI/2){
					cout << "Color: " <<color << " Center (m): " <<xPos <<","<< yPos << " Angle (rad): " << angle << endl;
					temp.s=constructCommand(xPos, yPos, angle, YELLOW,slider);
					temp.color=YELLOW;
					list1.push_back(temp);
					yellow++;
					count++;
				}
			}
			else //Not a brick
			{
				cout << "False detection" << endl;
			}
		}
		cout << "Number of detected LEGO bricks: " << count << endl;

		if(count>0){
			MESSAGES::order seen;
			seen.blue=blue;
			seen.red=red;
			seen.yellow=yellow;
			seenPub.publish(seen);
		}

		if(count==0)
			currentOrder=1;

		conveyerStopped=0;
		robReady=0;
}


void reqPickOfBricks(ros::Publisher configPub, ros::Publisher readyPub){

	while(!list1.empty()){

		if(list1.back().color==RED){
			if(wantedRed>0){
				wantedRed--;
				std_msgs::String message;
				message.data=list1.back().s;

				ostringstream s;
				s.str(string());
				s << currentOrder;
				message.data.append(s.str());
				message.data.append(")");
				cout << message.data <<endl;

				configPub.publish(message);
				list1.pop_back();
				cout << "send r" << endl;

			}
			else{
				list1.pop_back();
				cout << "removed order" << endl;
			}
		}

		else if(list1.back().color==BLUE){
			if(wantedBlue>0){
				wantedBlue--;
				std_msgs::String message;
				message.data=list1.back().s;

				ostringstream s;
				s.str(string());
				s << currentOrder;
				message.data.append(s.str());
				message.data.append(")");
				cout << message.data <<endl;

				configPub.publish(message);
				list1.pop_back();
				cout << "send b" << endl;

			}
			else{
				list1.pop_back();
				cout << "removed order" << endl;
			}
		}

		else if(list1.back().color==YELLOW){
			if(wantedYellow>0){
				wantedYellow--;
				std_msgs::String message;
				message.data=list1.back().s;

				ostringstream s;
				s.str(string());
				s << currentOrder;
				message.data.append(s.str());
				message.data.append(")");
				cout << message.data <<endl;

				configPub.publish(message);
				list1.pop_back();
				cout << "send y" << endl;
			}
			else{
				list1.pop_back();
				cout << "removed order" << endl;
			}
		}
	}


	std_msgs::String message;
	message.data="1";
	readyPub.publish(message);

	currentOrder=-1;
}

void robRCallback(const std_msgs::String::ConstPtr& msg)
{
	robReady=atoi(msg->data.c_str());
}

void convStopCallback(const std_msgs::String::ConstPtr& msg)
{
	conveyerStopped=atoi(msg->data.c_str());
}
void chosenOCallback(const MESSAGES::order:: ConstPtr& wanted)
{
	wantedRed=wanted->red;
	wantedBlue=wanted->blue;
	wantedYellow=wanted->yellow;
	//currentOrder=1;
	currentOrder=wanted->slider;
}


int main(int argc, char *argv[])
{
	ros::init(argc, argv, "vision");
	ros::NodeHandle h;
	ros::Publisher configPub = h.advertise<std_msgs::String>("/newConfig", 20);
	ros::Publisher seenPub = h.advertise<MESSAGES::order>("/visDetected", 20);
 	ros::Publisher readyPub = h.advertise<std_msgs::String>("/visReady", 10);
 	ros::Subscriber pickup = h.subscribe("/chosenOrder", 10, chosenOCallback);
 	ros::Subscriber robRSub = h.subscribe("/robotReady", 10, robRCallback);
 	ros::Subscriber convStopSub = h.subscribe("/conveyerStopped", 10, convStopCallback);
	
 	std::string device;
 	if(CAPTURE_DEVICE == 1)
 	{
 		device = "--device=\"/dev/video1\"";
 	}
 	else if(CAPTURE_DEVICE == 0)
 	{
 		device = "--device=\"/dev/video0\"";
 	}

	system(("v4l2-ctl " + device + " --set-ctrl white_balance_temperature_auto=0").c_str());
	system(("v4l2-ctl " + device + " --set-ctrl brightness=50").c_str());
	system(("v4l2-ctl " + device + " --set-ctrl contrast=95").c_str());
	system(("v4l2-ctl " + device + " --set-ctrl saturation=100").c_str());
	system(("v4l2-ctl " + device + " --set-ctrl hue=0").c_str());
	system(("v4l2-ctl " + device + " --set-ctrl gamma=48").c_str());
	system(("v4l2-ctl " + device + " --set-ctrl white_balance_temperature=2800").c_str());
	system(("v4l2-ctl " + device + " --set-ctrl sharpness=7").c_str());
	system(("v4l2-ctl " + device + " --set-ctrl backlight_compensation=2").c_str());
	system(("v4l2-ctl " + device + " --set-ctrl exposure_auto=1").c_str());

	//ros::Subscriber sub = h.subscribe("newConfig", 10, configCallback);

	double x = -1;
	double y = -1;
	ros::Rate loop_rate(10);
	sleep(3);
	Mat frame;
	VideoCapture cap(CAPTURE_DEVICE); //Setup capturing device	- In ubuntu: Install guvcview  and run "uvcdynctrl -l"
	if(!cap.isOpened())  // check if we succeeded
		return -1;
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280); //Set resolution to 1280x720
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

	//Get input data from webcam or saved image
	/*bool camera = 1; //0=saved image 1=input from camera
	if(camera)
	{	
		Mat frame;
		VideoCapture cap(-1); //Setup capturing device
		if(!cap.isOpened())  // check if we succeeded
        return -1;

		cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280); //Set resolution to 1280x720
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
		cap >> frame; //grab a frame
		src = frame.clone(); //make a clone of the captured image 
		waitKey(33);
	}
	else
	{
		src = imread("lego.png",1); //Use saved test image
	}*/
	//imshow("Input image", src); //Show input imag from either camera or file
//	namedWindow("Webcam",0);

/*	vector<Mat> vm;
	vm.push_back(imlalaread("lego3.png",1));
	vm.push_back(imread("lego2.png",1));
	vm.push_back(imread("lego1.png",1));
	vm.push_back(imread("lego.png",1));*/
	int frameCount =0;

	while(ros::ok()){
		//cout << "start: "  << ros::Time::now() << endl;
		if(frameCount>2){
			cap >> frame; //grab a frame
			frameCount=0;
		}

		if(currentOrder!=-1)
			reqPickOfBricks(configPub, readyPub);

		if(robReady==1 && conveyerStopped==1){
			Mat src, dst, imgROI, hsv, bw;
		/*	std_msgs::String message;
			message.data="0";
			readyPub.publish(message);*/

			src = frame.clone(); //make a clone of the captured image
			//src=imread("Webcam.png",1);
			imwrite("raw.png",src);
			//src = imread("lego.png",1); //Use saved test image
			/*if(!vm.empty()){
				src=vm.back();
				vm.pop_back();
			}*/

			cvtColor(src,hsv,CV_BGR2HSV); //Convert to HSV

			colorFilter(hsv,bw);
			imwrite("bw.png", bw);
			getBricks(bw,src, seenPub);
		}

		ros::spinOnce();
		loop_rate.sleep();

		frameCount++;
	}


	return 0;
}
