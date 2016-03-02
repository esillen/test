#include <iostream>
#include <cstdlib>

#include "opencv2/opencv.hpp"


int main(int argc, char  *argv[])
{
    int cam_number = 0;
    if(argc < 2) {
        printf("Setting default camera");
    }
    else{
        cam_number = atoi(argv[1]);
    }

    cv::VideoCapture cap(cam_number); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    double FPS = 10.0;
    int width = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_HEIGHT));

    cv::Mat frame;
    cv::VideoWriter out("output.mov", CV_FOURCC('m','p', '4', 'v'), FPS, cv::Size(width, height));
    if(!out.isOpened()) {
         std::cout <<"Error! Unable to open video file for output." << std::endl;
         std::exit(-1);
     }
    for(;;)
    {
        cap >> frame; // get a new frame from camera
        out << frame;
        cv::imshow("Camera feed", frame);
        if(cv::waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}