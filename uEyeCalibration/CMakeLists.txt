cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )


add_executable(calibration calibration.cpp )
target_link_libraries(calibration ${OpenCV_LIBS} )

