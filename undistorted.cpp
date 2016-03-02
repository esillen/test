#include "opencv2/opencv.hpp"
using namespace cv;
Mat imageUndistorted;


int main(int argc, char** argv)
{
    VideoCapture cap;

    Mat Camera_Matrix = (Mat_<float>(3,3) << 5.2104341900566453e+02, 0., 3.1263649951268309e+02, 0., 5.2077816286152654e+02, 2.1053218153907682e+02, 0., 0., 1.);
    Mat Distortion_Coefficients = (Mat_<float>(1,5) << 4.9496343266730490e-02, -1.8334311758588576e-01, -1.3620796499488266e-02, 3.2887309890435458e-04, 1.2809182620018483e-01);




    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(1))
        return 0;
    for(;;)
    {
        Mat image;
        cap >> image;

        int rows = image.rows;
        int cols = image.cols;

        if( image.empty() ) break; // end of video stream

        undistort(image, imageUndistorted, Camera_Matrix, Distortion_Coefficients);
        line(image, Point( cols/5, rows/5 ), Point( cols*4/5, rows/5 ), Scalar( 0, 0, 255 ), 2, 8 );
        line(image, Point( cols/5, rows*4/5 ), Point( cols*4/5, rows*4/5 ), Scalar( 0, 0, 255 ), 2, 8 );
        line(image, Point( cols/5, rows/5 ), Point( cols/5, rows*4/5 ), Scalar( 0, 0, 255 ), 2, 8 );
        line(image, Point( cols*4/5, rows/5 ), Point( cols*4/5, rows*4/5 ), Scalar( 0, 0, 255 ), 2, 8 );

        line(imageUndistorted, Point( cols/5, rows/5 ), Point( cols*4/5, rows/5 ), Scalar( 0, 0, 255 ), 2, 8 );
        line(imageUndistorted, Point( cols/5, rows*4/5 ), Point( cols*4/5, rows*4/5 ), Scalar( 0, 0, 255 ), 2, 8 );
        line(imageUndistorted, Point( cols/5, rows/5 ), Point( cols/5, rows*4/5 ), Scalar( 0, 0, 255 ), 2, 8 );
        line(imageUndistorted, Point( cols*4/5, rows/5 ), Point( cols*4/5, rows*4/5 ), Scalar( 0, 0, 255 ), 2, 8 );

        imshow("undistorted image", imageUndistorted);
        imshow("this is you, smile! :)", image);
        if( waitKey(1) == 27 ) break; // stop capturing by pressing ESC 
    }
    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}