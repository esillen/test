#include "opencv2/opencv.hpp"
#include <iostream>
#include <time.h>

using namespace cv;
using namespace std;

int main(int, char** argv){

    FileStorage fs2("test.xml", FileStorage::READ);
    if (!fs2.isOpened()){
        cout << "failed to open test.xml :(" << endl;
            return 1;
    }

    // first method: use (type) operator on FileNode.
    int frameCount = (int)fs2["frameCount"];

    std::string date;
    // second method: use FileNode::operator >>
    fs2["calibrationDate"] >> date;

    Mat camera_intrinsics_1, camera_intrinsics_2, camera_intrinsics_3, camera_intrinsics_4;
    Mat camera_extrinsics_1, camera_extrinsics_2, camera_extrinsics_3, camera_extrinsics_4;


    fs2["camera_intrinsics_1"] >> camera_intrinsics_1;
    fs2["camera_intrinsics_2"] >> camera_intrinsics_2;
    fs2["camera_intrinsics_3"] >> camera_intrinsics_3;
    fs2["camera_intrinsics_4"] >> camera_intrinsics_4;

    fs2["camera_extrinsics_1"] >> camera_extrinsics_1;
    fs2["camera_extrinsics_2"] >> camera_extrinsics_2;
    fs2["camera_extrinsics_3"] >> camera_extrinsics_3;
    fs2["camera_extrinsics_4"] >> camera_extrinsics_4;


    cout << camera_extrinsics_4 << endl;

    cout << camera_intrinsics_4 << endl;

    //fs2["distCoeffs"] >> distCoeffs2;

    //cout << "frameCount: " << frameCount << endl
     //    << "calibration date: " << date << endl
      //   << "camera matrix: " << cameraMatrix2 << endl
       //  << "distortion coeffs: " << distCoeffs2 << endl;

    FileNode features = fs2["features"];
    FileNodeIterator it = features.begin(), it_end = features.end();
    int idx = 0;
    std::vector<uchar> lbpval;

    // iterate through a sequence using FileNodeIterator
    for( ; it != it_end; ++it, idx++ )
    {
        cout << "feature #" << idx << ": ";
        cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";
        // you can also easily read numerical arrays using FileNode >> std::vector operator.
        (*it)["lbp"] >> lbpval;
        for( int i = 0; i < (int)lbpval.size(); i++ )
            cout << " " << (int)lbpval[i];
        cout << ")" << endl;
    }
    fs2.release();
}