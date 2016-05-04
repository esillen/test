/**
 * @file UEyeCapture.cpp
 * @author Yutaka Kondo <yutaka.kondo@youtalk.jp>
 * @date Apr 20, 2014
 */

 //Written very much for a single purpose.

//This program saves a bunch of images to hard disk along with timestamps


#include <chrono>
#include <ctime>

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
//For imu
 #include <phidget21.h>

FILE * accFile;
FILE * gyrFile;
FILE * imu_timestamps;

std::chrono::time_point<std::chrono::system_clock> start, now;

using namespace rgbd;


//callback that will run if the Spatial generates an error
int CCONV ErrorHandler(CPhidgetHandle spatial, void *userptr, int ErrorCode, const char *unknown)
{
    printf("Error handled. %d - %s \n", ErrorCode, unknown);
    return 0;
}

//callback that will run at datarate
//data - array of spatial event data structures that holds the spatial data packets that were sent in this event
//count - the number of spatial data event packets included in this event
int CCONV SpatialDataHandler(CPhidgetSpatialHandle spatial, void *userptr, CPhidgetSpatial_SpatialEventDataHandle *data, int count)
{
    int i;
    printf("Number of Data Packets in this event: %d\n", count);
    for(i = 0; i < count; i++)
    {
        printf("recorded! \n");
        now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - start;
        double diff = elapsed_seconds.count();
        fprintf (imu_timestamps,"%6f\n", diff);
        fprintf (gyrFile, "%6f %6f %6f\n", data[i]->angularRate[0], data[i]->angularRate[1], data[i]->angularRate[2]);
        fprintf (accFile, "%6f %6f %6f\n", data[i]->acceleration[0], data[i]->acceleration[1], data[i]->acceleration[2]);
    }

    return 0;
}



int main(int argc, char *argv[]) {
    //gflags::ParseCommandLineFlags(&argc, &argv, true);

    accFile = fopen ("./imudata/acc.txt","w");
    gyrFile = fopen ("./imudata/gyr.txt","w");
    imu_timestamps = fopen("./imudata/timestamps.txt","w");


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
    std::ofstream video_timestamps;
    video_timestamps.open ("./videos/timestamps.txt");


    std::cout << "Press any key to start recording. \nThen press escape to save." << std::endl;

    start = std::chrono::system_clock::now();

    //IMU STUFF
    int result;
    const char *err;

    //Declare a spatial handle
    CPhidgetSpatialHandle spatial = 0;

    //create the spatial object
    CPhidgetSpatial_create(&spatial);

    CPhidgetSpatial_set_OnSpatialData_Handler(spatial, SpatialDataHandler, NULL);

    //open the spatial object for device connections
    CPhidget_open((CPhidgetHandle)spatial, -1);

    //get the program to wait for a spatial device to be attached
    printf("Waiting for spatial to be attached.... \n");
    if((result = CPhidget_waitForAttachment((CPhidgetHandle)spatial, 10000)))
    {
        CPhidget_getErrorDescription(result, &err);
        printf("Problem waiting for attachment: %s\n", err);
        return 0;
    }

    
    //Set the data rate for the spatial events
    CPhidgetSpatial_setDataRate(spatial, 16);

    //read spatial event data
    printf("Start?...?...?\n");


    while ((key = cv::waitKey(10)) != 0x1b) {

    

        //clock_gettime(CLOCK_REALTIME, &ts);

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

        //fprintf(pFile, "%lld.%.9ld\n", (long long)ts.tv_sec, ts.tv_nsec); //Prints timestamps to file
        now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - start;
        double diff = elapsed_seconds.count();
        video_timestamps << diff << std::endl;

        picture_number++;
        std::cout << "picture taken, number " << picture_number << std::endl;

    }


    return 0;
}
