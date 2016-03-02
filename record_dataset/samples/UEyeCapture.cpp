/**
 * @file UEyeCapture.cpp
 * @author Yutaka Kondo <yutaka.kondo@youtalk.jp>
 * @date Apr 20, 2014
 */

 //Written very much for a single purpose.

//This program saves a bunch of images to hard disk along with timestamps


#include <sys/time.h>

#include <iostream>
#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <gflags/gflags.h>
#include "rgbd/camera/UEye.h"
#include "rgbd/camera/DistortionCalibrator.h"
#include "rgbd/camera/ColorCalibrator.h"
#include "rgbd/camera/ColorRotator.h"
 //For file output
#include <fstream>
#include <stdio.h>


using namespace rgbd;

//DEFINE_int32(id, 0, "camera id");
//DEFINE_string(conf, "data/ueye-conf.ini", "camera configuration");
//DEFINE_string(intrinsics, "data/ueye-calib.xml", "camera intrinsic data");

int main(int argc, char *argv[]) {
    //gflags::ParseCommandLineFlags(&argc, &argv, true);


    std::shared_ptr<UEye> original1;
    std::shared_ptr<UEye> original2;
    std::shared_ptr<UEye> original3;
    std::shared_ptr<UEye> original4;


    cv::Mat raw;
    cv::Mat raw2;


    bool start1 = true;
    bool start2 = true;
    bool start3 = false;
    bool start4 = false;

  
    //std::shared_ptr<rgbd::DistortionCalibrator> undistorted(
      //      new rgbd::DistortionCalibrator(original, FLAGS_intrinsics));
    //std::shared_ptr<rgbd::ColorCalibrator> camera(
      //      new rgbd::ColorCalibrator(undistorted));
//    std::shared_ptr<rgbd::ColorRotator> camera(
//            new rgbd::ColorRotator(calibrated, 90));
    if(start1){
        original1.reset(new UEye(1, "data/ueye-conf.ini"));
        original1->start();
        std::cout << "Initialized camera 1!" << std::endl;
    }

    if(start2){
        original2.reset(new UEye(2, "data/ueye-conf.ini"));
        original2->start();
        std::cout << "Initialized camera 2!" << std::endl;
        //raw2 = cv::Mat::zeros(original2->colorSize(), CV_8UC1);
        //cv::namedWindow("Raw2", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    }

    if(start3){
        original3.reset(new UEye(3, "data/ueye-conf.ini"));
        original3->start();
        std::cout << "Initialized camera 3!" << std::endl;
        //raw3 = cv::Mat::zeros(original3->colorSize(), CV_8UC1);
        //cv::namedWindow("Raw3", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    }

    if(start4){
        original4.reset(new UEye(4, "data/ueye-conf.ini"));
        original4->start();
        std::cout << "Initialized camera 4!" << std::endl;
        //raw4 = cv::Mat::zeros(original4->colorSize(), CV_8UC1);
        //cv::namedWindow("Raw4", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    }
    raw = cv::Mat::zeros(original1->colorSize(), CV_8UC1);
    raw2 = cv::Mat::zeros(original2->colorSize(), CV_8UC1);
    
    cv::namedWindow("Window", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);

    int key = 0;
    int picture_number = 0;

    //std::ofstream myfile ("./videos/timestamps.txt");
    FILE * pFile;
    pFile = fopen ("./videos/timestamps.txt","w");

    
    timespec ts;
    
    while ((key = cv::waitKey(10)) != 0x1b) {

        clock_gettime(CLOCK_REALTIME, &ts);

        if(start1) original1->captureColor(raw);
        if(start2) original2->captureColor(raw2);
        else if(start3) original3->captureColor(raw);
        else if(start4) original4->captureColor(raw);
        //cv::imshow("Camera 1", raw);
        //cv::imshow("Camera 2", raw2);

        std::stringstream stream;
        stream.str();
        stream << "./videos/cam1/xx" << picture_number << ".jpg";
        cv::imwrite(stream.str(), raw);

        std::stringstream stream2;
        stream2.str();
        stream2 << "./videos/cam2/xx" << picture_number << ".jpg";
        cv::imwrite(stream2.str(), raw2);

        fprintf(pFile, "%lld.%.9ld\n", (long long)ts.tv_sec, ts.tv_nsec); //Prints timestamps to file

        picture_number++;
        std::cout << picture_number << std::endl;

    }
    fclose (pFile);


    return 0;
}
