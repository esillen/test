cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )


add_executable(viztest viztest.cpp )
target_link_libraries(viztest ${OpenCV_LIBS})

#add_executable( demo demo.cpp )
#target_link_libraries( demo ${OpenCV_LIBS} )

#add_executable(save_vid save_vid.cpp )
#target_link_libraries( save_vid ${OpenCV_LIBS} )

#add_executable(play_vid play_vid.cpp )
#target_link_libraries( play_vid ${OpenCV_LIBS} )

#add_executable(meanfilter meanfilter.cpp )
#target_link_libraries( meanfilter ${OpenCV_LIBS} )

#add_executable(calibration calibration.cpp )
#target_link_libraries(calibration ${OpenCV_LIBS} )

