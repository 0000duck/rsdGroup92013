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

#define PI 3.14159265359
#define scale 0.000195 //Conversion from pixel to meter in the image. Calculated by actual size in meters of the image divided by the resolution
#define offsetX -0.125 //Move the origo (0,0) position from the upper left corner to the center of the image
#define offsetY -0.07 //in both directions. The image size is 0.25 by 0.14 meters
#define blueMin   5000
#define blueMax   10000
#define redMin    14000
#define redMax    18000
#define yellowMin 22000//16000
#define yellowMax 30000//24000

using namespace std;
using namespace cv;

int conveyerStopped = 1;
int robReady = 0;

vector<string> list1;

string constructCommand(double xPos, double yPos, double angle, int slider){
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
	s << slider;
	temp2=s.str();
	temp.append(temp2);
	temp.append(")");

	return temp;
}

void colorFilter(const Mat& src, Mat& bw)
{
    assert(src.type() == CV_8UC3);
    Mat colors, red1, red2, yellow, blue, purple;
    GaussianBlur( src, src, Size(3, 3), 2, 2 );
  	inRange(src, Scalar(  0, 50, 75), Scalar(25, 255, 255), red1);	//Red lower
  	inRange(src, Scalar( 14, 200, 130), Scalar(34, 255, 255), yellow);	//Yellow
  	inRange(src, Scalar( 90, 5, 25), Scalar(155, 255, 255), blue);	//Blue

  	colors = red1 + yellow + blue;// + red2;

  	//Noise removal
  	Mat element = getStructuringElement(MORPH_RECT, Size(6, 6));
  	Mat element1 = getStructuringElement(MORPH_RECT, Size(12, 12));
  	dilate(colors,colors,element1);
  	erode(colors,bw,element);
}


void getBricks(Mat& imgEdge, Mat& imgROI, ros::Publisher configPub, ros::Publisher seenPub, ros::Publisher readyPub){
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
					list1.push_back(constructCommand(xPos, yPos, angle, slider));
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
					list1.push_back(constructCommand(xPos, yPos, angle, slider));
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
					list1.push_back(constructCommand(xPos, yPos, angle, slider));
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

		MESSAGES::order seen;
		seen.blue=blue;
		seen.red=red;
		seen.yellow=yellow;
		seenPub.publish(seen);



		while(!list1.empty()){
			std_msgs::String message;
			message.data=list1.back();
			configPub.publish(message);
			list1.pop_back();
		}
		std_msgs::String message;
		message.data="1";
		readyPub.publish(message);
		conveyerStopped=0;
		robReady=0;
}

void robRCallback(const std_msgs::String::ConstPtr& msg)
{
	robReady=atoi(msg->data.c_str());
}

void convStopCallback(const std_msgs::String::ConstPtr& msg)
{
	conveyerStopped=atoi(msg->data.c_str());
}


int main(int argc, char *argv[])
{
	ros::init(argc, argv, "vision");
	ros::NodeHandle h;
	ros::Publisher configPub = h.advertise<std_msgs::String>("newConfig", 20);
	ros::Publisher seenPub = h.advertise<MESSAGES::order>("visDetected", 20);
 	ros::Publisher readyPub = h.advertise<std_msgs::String>("visReady", 1);
 	ros::Subscriber robRSub = h.subscribe("robotReady", 10, robRCallback);
 	ros::Subscriber convStopSub = h.subscribe("conveyerStopped", 10, convStopCallback);

	system("v4l2-ctl --set-ctrl white_balance_temperature_auto=0");
	system("v4l2-ctl --set-ctrl brightness=50");
	system("v4l2-ctl --set-ctrl contrast=95");
	system("v4l2-ctl --set-ctrl saturation=100");
	system("v4l2-ctl --set-ctrl hue=0");
	system("v4l2-ctl --set-ctrl gamma=48");
	system("v4l2-ctl --set-ctrl white_balance_temperature=2800");
	system("v4l2-ctl --set-ctrl sharpness=7");
	system("v4l2-ctl --set-ctrl backlight_compensation=2");
	system("v4l2-ctl --set-ctrl exposure_auto=1");

	//ros::Subscriber sub = h.subscribe("newConfig", 10, configCallback);

	double x = -1;
	double y = -1;
	ros::Rate loop_rate(10);
	sleep(3);
	Mat frame;
	VideoCapture cap(-1); //Setup capturing device
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
	while(ros::ok()){

		cap >> frame; //grab a frame

		if(robReady==1 && conveyerStopped==1){
			Mat src, dst, imgROI, hsv, bw;
			std_msgs::String message;
			message.data="0";
			readyPub.publish(message);

			src = frame.clone(); //make a clone of the captured image
			//src=imread("Webcam.png",1);
			imwrite("Webcam.png",src);
			//src = imread("lego.png",1); //Use saved test image
			/*if(!vm.empty()){
				src=vm.back();
				vm.pop_back();
			}*/

			cvtColor(src,hsv,CV_BGR2HSV); //Convert to HSV

			colorFilter(hsv,bw);
			imwrite("bw.png", bw);
			getBricks(bw,src, configPub, seenPub, readyPub);
		}

		ros::spinOnce();
		loop_rate.sleep();
	}


	waitKey(0);
	return 0;
}
