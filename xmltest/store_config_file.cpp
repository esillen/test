#include "opencv2/opencv.hpp"
#include <time.h>

using namespace cv;

int main(int, char** argv)
{
    FileStorage fs("test.xml", FileStorage::WRITE);

    fs << "number_of_cameras" << 2;
    time_t rawtime; time(&rawtime);
    fs << "calibrationDate" << asctime(localtime(&rawtime));
    
    //Intrinsic parameters
    //fx, fy, cx, cy, k1, k2 , k3 ... the very last parameter is nominal fps (usually 30).
    Mat camera_intrinsics_1 = (Mat_<double>(10,1) << 613.039, 613.039, 375.5, 239.5, -3.7190768207085390e-01, 2.3296805519991015e-01, 0.0, 0.0,-1.1351747838880406e-01, 30.0);
    Mat camera_intrinsics_2 = (Mat_<double>(10,1) << 613.039, 613.039, 375.5, 239.5, -3.7190768207085390e-01, 2.3296805519991015e-01, 0.0, 0.0,-1.1351747838880406e-01, 30.0);
    Mat camera_intrinsics_3 = (Mat_<double>(10,1) << 613.039, 613.039, 375.5, 239.5, -3.7190768207085390e-01, 2.3296805519991015e-01, 0.0, 0.0,-1.1351747838880406e-01, 30.0);
    Mat camera_intrinsics_4 = (Mat_<double>(10,1) << 613.039, 613.039, 375.5, 239.5, -3.7190768207085390e-01, 2.3296805519991015e-01, 0.0, 0.0,-1.1351747838880406e-01, 30.0);
    fs << "camera_intrinsics_1" << camera_intrinsics_1;
    fs << "camera_intrinsics_2" << camera_intrinsics_2;
    fs << "camera_intrinsics_3" << camera_intrinsics_3;
    fs << "camera_intrinsics_4" << camera_intrinsics_4;

    //extrinsics parameters
    //x, y, z, roll, pitch, yaw (meters, degrees)
    //Totally unsure of the correctness of this right now.
    Mat camera_extrinsics_1 = (Mat_<double>(6,1) << 0.2, 0, 0.05, 0, 0, 0);
    Mat camera_extrinsics_2 = (Mat_<double>(6,1) << 0.2, 0, -0.05, 90, 0, 0);
    Mat camera_extrinsics_3 = (Mat_<double>(6,1) << 0.2, 0, 0.05, 0, 0, 0);
    Mat camera_extrinsics_4 = (Mat_<double>(6,1) << 0.2, 0, 0.05, 0, 0, 0);
    fs << "camera_extrinsics_1" << camera_extrinsics_1;
    fs << "camera_extrinsics_2" << camera_extrinsics_2;
    fs << "camera_extrinsics_3" << camera_extrinsics_3;
    fs << "camera_extrinsics_4" << camera_extrinsics_4;

    fs.release();
    return 0;
}