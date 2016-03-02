#include <iostream>
#include "opencv2/opencv.hpp"


int main(int, char**)
{
	int height = 100;
	int width = 100;
	double FPS = 10.0;

    cv::VideoCapture cap("output.mov"); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    cv::Mat edges;
    cv::Mat frame;
    cv::namedWindow("edges",1);
    for(;;)
    {
        cap >> frame; // get a new frame from camera
        cv::cvtColor(frame, edges, CV_BGR2GRAY);
        cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
        cv::Canny(edges, edges, 0, 30, 3);
        cv::imshow("edges", edges);
        int key_pressed = cv::waitKey(0);
        if(key_pressed == 27) {
        	std::cout << "user quit program" << std::endl;

        	break;}
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}