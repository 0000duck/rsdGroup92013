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
#define blueMin   3500
#define blueMax   8800
#define redMin    9000
#define redMax    15000
#define yellowMin 16000
#define yellowMax 24000

using namespace std;
using namespace cv;

int conveyerStopped = 0;

vector<string> list1;

Mat colorFilter(const Mat& src)
{
    assert(src.type() == CV_8UC3);
    Mat colors, red1, red2, yellow, blue;
    inRange(src, Scalar(  0, 150, 150), Scalar(20, 255, 255), red1);	//Red lower
	inRange(src, Scalar( 20, 150, 150), Scalar(34, 255, 255), yellow);	//Yellow
	inRange(src, Scalar( 87, 150, 150), Scalar(120, 255, 255), blue);	//Blue
	inRange(src, Scalar(170, 150, 150), Scalar(179, 255, 255), red2);	//Red higher
	colors = red1 + yellow + blue + red2;
    return colors;
	//Fejler for billede 23+24+28+31+33
	//Under a strict controlled light environment color detection alone would be perfect and should be used instead of edge detection.
	//Remember to use morphology to clean up noise
}

void findMarkerLocation(Mat& gray, double& x, double& y){
	//Extracting the circle for syncronizing the position of the conveyor
	Mat imgCircle;
	imgCircle = gray.clone();
	imgCircle = imgCircle(Range(200,500), Range(1150, gray.cols));
	GaussianBlur( imgCircle, imgCircle, Size(7, 7), 2, 2 );
	vector<Vec3f> circles;
	HoughCircles(imgCircle, circles, CV_HOUGH_GRADIENT, 2, 500, 10, 50,10,50);
	for( size_t i = 0; i < circles.size(); i++ )
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// draw the circle center
		circle( imgCircle, center, 3, Scalar(0,255,0), -1, 8, 0 );
		// draw the circle outline
		circle( imgCircle, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
//	//imshow("Circle part",imgCircle);
}

Mat detectEdges(Mat& gray, Mat& imgEdge){
	//Edge detection
		GaussianBlur(gray, gray, Size(5, 5), 2, 2); //Blur the image to remove noise
		cout << "1" << endl;
		Canny(gray, imgEdge, 10,50,3); //Find the edges PARAMETER 3 AND 4 MUST BE CALIBRATED
	//	//imshow("Edge detection", imgEdge);
		cout << "2" << endl;

		//Remove unwanted edges typical from the surface of the conveyor
		Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
		Mat element1 = getStructuringElement(MORPH_RECT, Size(12, 12)); //MORPH_CROSS
		cout << "3" << endl;

		dilate(imgEdge,imgEdge,element);
		dilate(imgEdge,imgEdge,element);
		cout << "4" << endl;

		//imshow("Dialate",imgEdge);
		erode(imgEdge,imgEdge,element1);
		erode(imgEdge,imgEdge,element1);
		cout << "5" << endl;

	//	//imshow("Morphology result", imgEdge);
		bitwise_not(imgEdge,imgEdge); //Invert the image for findcontours

		return imgEdge;
}

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

void getBricks(Mat& imgEdge, Mat& imgROI, ros::Publisher configPub, ros::Publisher seenPub, ros::Publisher readyPub){
		Mat imgCon;

	//Vectors for storing the connected components in:
		vector < vector <cv::Point> > contours, contours1;
		imgCon = imgEdge.clone(); //Take a copy of the edges for extracting the contours
		findContours(imgCon, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0)); //sizeLeft offset is needed because some of the image was cut out
		Mat overlayed = Mat::zeros(imgROI.size(),imgROI.type());
		drawContours(overlayed, contours, -1, Scalar(255,255,255), CV_FILLED, 8);  //
		overlayed &= imgROI;
		//imshow("overlayed", overlayed);
		cout << "Number of detected LEGO bricks: " << contours.size() << endl;

		//Values found by the typical min/max size for the different brick type/color


		//Remove contours that is to small og big for being a LEGO brick
		for(unsigned int i=0; i<contours.size(); i++)
		{
			if (contourArea(Mat(contours[i]))<yellowMax && contourArea(Mat(contours[i]))>blueMin)
			{
				contours1.push_back(contours[i]);
			}
		}

		int color=0;
		RotatedRect rectangle;
		RotatedRect ellipse;

		int blue=0;
		int red=0;
		int yellow=0;

		for(unsigned int i=0; i<contours1.size(); i++)
		{
			cout << "Area of brick: " << contourArea(Mat(contours1[i])) << endl;
			int aera = int(contourArea(Mat(contours1[i])));
			rectangle = minAreaRect(Mat(contours1[i]));
			ellipse = fitEllipse(Mat(contours1[i])); //Used since the rectangle.angle is only in the range 0...-90 degrees

			//the camera and the robot have different coordinatesystems, therefore the x and y positions are changed and they are both negated.
			double xPos = -(rectangle.center.y*scale+offsetY);
			double yPos = -(rectangle.center.x*scale+offsetX);
			//Angle is calculated from the fitted elipse in order to get the angle in the interval 0-180degrees, this is converted to radians, and PI/2 is subtracted to have the minimum rotation of the gripper tool
			double angle = ellipse.angle*PI/180-PI;

			if(angle<-PI/2)
			{
			angle=angle+PI;
			}


			int slider=1;
			//constructCommand(xPos, yPos, angle, slider);

			if(aera<blueMax && aera>blueMin) //Blue
			{ //list.push_back("( 0.018 , 0.053 , 0 , 0 , 0 , -0.13, 1,)");
				color=1;
				cout << "Color: " <<color << " Center (m): " <<xPos <<","<< yPos << " Angle (rad): " << angle << endl;
				list1.push_back(constructCommand(xPos, yPos, angle, slider));
				blue++;
			}
			else if (aera<redMax && aera>redMin) //Red
			{
				color=2;
				cout << "Color: " <<color << " Center (m): " <<xPos <<","<< yPos << " Angle (rad): " << angle << endl;
				list1.push_back(constructCommand(xPos, yPos, angle, slider));
				red++;
			}
			else if (aera<yellowMax && aera>yellowMin) //Yellow
			{
				color=3;
				cout << "Color: " <<color << " Center (m): " <<xPos <<","<< yPos << " Angle (rad): " << angle << endl;
				list1.push_back(constructCommand(xPos, yPos, angle, slider));
				yellow++;
			}
			else //Not a brick
			{
				cout << "False detection" << endl;
			}
		}

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
}

void robRCallback(const std_msgs::String::ConstPtr& msg)
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

	//ros::Subscriber sub = h.subscribe("newConfig", 10, configCallback);

	Mat src, dst, imgROI, hsv, gray, imgEdge;
	double x = -1;
	double y = -1;
	ros::Rate loop_rate(1);
	sleep(3);

	//Get input data from webcam or saved image
	/*bool camera = 0; //0=saved image 1=input from camera
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

	while(ros::ok()){
		if(conveyerStopped==1){
			src = imread("lego.png",1); //Use saved test image
			//Extracting the region of interest ROI
			imgROI = src.clone(); //Take a copy of the input

			//Convert to gray scale
			cvtColor(imgROI,hsv,CV_BGR2HSV); //Convert to HSV
			std_msgs::String message;
			message.data="0";
			readyPub.publish(message);
			vector<Mat> HSV_planes;
			split(hsv, HSV_planes);
			gray = HSV_planes[2];

			//afjklasghogtjilsagahilæg =findMarkerLocation(gray);

			//Cut out the part of the image with the circle
			int sizeLeft = 0;
			int sizeRight = 1149;
			gray = gray(Range(0, gray.rows), Range(sizeLeft, sizeRight)); //Define the area of the ROI image
			cout << "0" << endl;

			Mat imgEdge;
			imgEdge = detectEdges(gray, imgEdge);
			getBricks(imgEdge,imgROI, configPub, seenPub, readyPub);
		}

		ros::spinOnce();
		loop_rate.sleep();
	}


	waitKey(0);
	return 0;
}
