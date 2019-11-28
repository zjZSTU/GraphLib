cmake_minimum_required(VERSION 3.13)
project(cplusplus)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_PREFIX_PATH /home/zj/opencv/opencv-4.1.0/install)
find_package(OpenCV REQUIRED)

MESSAGE("OpenCV version: ${OpenCV_VERSION}")
MESSAGE("OpenCV OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
MESSAGE("OpenCV OpenCV_LIBS: ${OpenCV_LIBS}")

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/home/zj/opencv/opencv-4.1.0/opencv/modules")
include_directories("/home/zj/opencv/opencv-4.1.0/opencv_contrib/modules")

add_executable(cplusplus
        samples/graphsegmentation/graphsegmentation.cpp
        src/segmentation/GraphSegmentation.cpp
        src/segmentation/GraphSegmentation.h
        src/segmentation/GraphSegmentationImpl.cpp
        src/segmentation/GraphSegmentationImpl.h
        src/segmentation/PointSet.cpp
        src/segmentation/PointSet.h)
target_link_libraries(cplusplus ${OpenCV_LIBS})