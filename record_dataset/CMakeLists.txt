CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(rgbd-grabber)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)
FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(/usr/include)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIR})

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)
LINK_DIRECTORIES(/usr/lib)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
SET(CMAKE_CXX_FLAGS "-std=c++0x -fpermissive -Wno-deprecated -Wno-sign-compare")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
SET(CMAKE_CXX_LINK_FLAGS_DEBUG "-pg")

SET(VERSION "0.9.7")
SET(SOVERSION "0.9")

SET(SRC
  src/camera/ColorCamera.cpp
  src/camera/DistortionCalibrator.cpp
  src/camera/ColorCalibrator.cpp src/camera/ColorRotator.cpp) 

SET(SRC_UEYE
  src/camera/UEye.cpp src/camera/ueye_cam_driver.cpp)

SET(LIB_EXTERNAL
  ${Boost_LIBRARIES} ${OpenCV_LIBS} gflags pthread)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${SRC})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIB_EXTERNAL})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${SOVERSION})

SET(LIB
  ${PROJECT_NAME} ${LIB_EXTERNAL})

INSTALL(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
INSTALL(DIRECTORY include/rgbd DESTINATION include)

  ADD_LIBRARY(${PROJECT_NAME}-ueye SHARED ${SRC_UEYE})
  TARGET_LINK_LIBRARIES(${PROJECT_NAME}-ueye ${LIB})
  SET_TARGET_PROPERTIES(${PROJECT_NAME}-ueye PROPERTIES VERSION ${VERSION} SOVERSION ${SOVERSION})
  ADD_EXECUTABLE(UEyeCapture samples/UEyeCapture.cpp)
  ADD_DEPENDENCIES(UEyeCapture ${SRC} ${SRC_UEYE})
  TARGET_LINK_LIBRARIES(UEyeCapture ${LIB} ${PROJECT_NAME}-ueye ueye_api)
  ADD_EXECUTABLE(UEyeCalibration samples/UEyeCalibration.cpp)
  ADD_DEPENDENCIES(UEyeCalibration ${SRC} ${SRC_UEYE})
  TARGET_LINK_LIBRARIES(UEyeCalibration ${LIB} ${PROJECT_NAME}-ueye ueye_api)


  INSTALL(TARGETS ${PROJECT_NAME}-ueye LIBRARY DESTINATION lib)

