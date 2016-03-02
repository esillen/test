/**
 * @file widget_pose.cpp
 * @brief Setting pose of a widget
 * @author Ozan Cagri Tonkal
 */

#include <opencv2/viz/vizcore.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>

using namespace std;

/**
 * @function help
 * @brief Display instructions to use this tutorial program
 */
void help()
{
    cout
    << "--------------------------------------------------------------------------"   << endl
    << "This program shows how to visualize a cube rotated around (1,1,1) and shifted "
    << "using Rodrigues vector."                                                      << endl
    << "Usage:"                                                                       << endl
    << "./widget_pose"                                                                << endl
    << endl;
}

/**
 * @function main
 */
int main()
{
    help();

    /// Create a window
    cv::viz::Viz3d myWindow("Coordinate Frame");

    /// Add coordinate axes
    myWindow.showWidget("Coordinate Widget", cv::viz::WCoordinateSystem());

    /// Add line to represent (1,1,1) axis
    cv::viz::WLine axis(cv::Point3f(-1.0f,-1.0f,-1.0f), cv::Point3f(1.0f,1.0f,1.0f));
    axis.setRenderingProperty(cv::viz::LINE_WIDTH, 4.0);
    myWindow.showWidget("Line Widget", axis);

    /// Construct a cube widget
    cv::viz::WCube cube_widget(cv::Point3f(0.5,0.5,0.0), cv::Point3f(0.0,0.0,-0.5), true, cv::viz::Color::blue());
    cube_widget.setRenderingProperty(cv::viz::LINE_WIDTH, 4.0);
    myWindow.showWidget("Cube Widget", cube_widget);

    /// Rodrigues vector
    cv::Mat rot_vec = cv::Mat::zeros(1,3,CV_32F);
    float translation_phase = 0.0, translation = 0.0;
    while(!myWindow.wasStopped())
    {
        /* Rotation using rodrigues */
        /// Rotate around (1,1,1)
        rot_vec.at<float>(0,0) += CV_PI * 0.01f;
        rot_vec.at<float>(0,1) += CV_PI * 0.01f;
        rot_vec.at<float>(0,2) += CV_PI * 0.01f;

        /// Shift on (1,1,1)
        translation_phase += CV_PI * 0.01f;
        translation = sin(translation_phase);

        cv::Mat rot_mat;
        cv::Rodrigues(rot_vec, rot_mat);

        /// Construct pose
        cv::Affine3f pose(rot_mat, cv::Vec3f(translation, translation, translation));

        myWindow.setWidgetPose("Cube Widget", pose);

        myWindow.spinOnce(1, true);
    }

    return 0;
}