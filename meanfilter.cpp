//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp" 
 
int main( int argc, char** argv )
 {
 
	 cv::VideoCapture cap(0); // open the default camera
   	 if(!cap.isOpened())  // check if we succeeded
        return -1;

     cv::Mat src;
     cv::Mat dst;
     for(;;)
    {
        cap >> src;
     	
     	resize(src, dst, cv::Size(50,50),0,0);
     	cv::medianBlur ( dst, dst, 7 );
     	resize(dst, dst, cv::Size(500,500),0,0);
        cv::imshow("source", src);
     	cv::imshow("result", dst); 

        if(cv::waitKey(30) >= 0) break;
    }
 
     
     
 
     return 0;
 }