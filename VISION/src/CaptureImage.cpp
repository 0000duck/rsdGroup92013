#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <strstream>

using namespace std;
using namespace cv;

int main()
{
	system("v4l2-ctl --set-ctrl white_balance_temperature_auto=0");
	system("v4l2-ctl --set-ctrl brightness=30");
	system("v4l2-ctl --set-ctrl contrast=95");
	system("v4l2-ctl --set-ctrl saturation=100");
	system("v4l2-ctl --set-ctrl hue=0");
	system("v4l2-ctl --set-ctrl gamma=300");
	system("v4l2-ctl --set-ctrl white_balance_temperature=2800");
	system("v4l2-ctl --set-ctrl sharpness=4");
	system("v4l2-ctl --set-ctrl backlight_compensation=2");
	system("v4l2-ctl --set-ctrl exposure_auto=1");
	// Matrice for the video input
	Mat image;
	VideoCapture cap(0); //-1,0 = external camera, 1,2,... = internal camera	
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
	namedWindow("Webcam",0);
	
	

	while(1)
	{
		cap>>image;
		imshow("Webcam",image);
		waitKey(33);
		// Save image if s was keyboard
		char ch = waitKey(25);
		if(ch=='s'){
			cout << "la" << endl;
			imwrite("lego.png",image);
		}
	}



return 0;
}
