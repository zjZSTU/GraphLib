cmake_minimum_required(VERSION 3.13)
project(cplusplus)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_PREFIX_PATH /home/zj/opencv/opencv-4.0.1/install)
find_package(OpenCV REQUIRED)
MESSAGE("OpenCV version: ${OpenCV_VERSION}")
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cplusplus samples/graphsegmentation/segmentation.cpp src/segmentation/GraphSegmentationImpl.cpp
        src/segmentation/GraphSegmentationImpl.h src/segmentation/PointSet.cpp src/segmentation/PointSet.h)
target_link_libraries(cplusplus ${OpenCV_LIBS})