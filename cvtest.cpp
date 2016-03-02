#include "opencv2/opencv.hpp"
int main(int argc, char** argv)
{
    cv::VideoCapture cap;

    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(0))
        return 0;
      cap.set(CV_CAP_PROP_SETTINGS, 1);
    for(;;)
    {
          cv::Mat frame;
          cap >> frame;
          if( frame.empty() ) break; // end of video stream
          cv::imshow("this is you, smile! :)", frame);
          if( cv::waitKey(1) == 27 ) break; // stop capturing by pressing ESC 
    }
    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}