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

#add_executable(cplusplus
#        samples/graphsegmentation/graphsegmentation.cpp
#        src/segmentation/GraphSegmentation.cpp
#        src/segmentation/GraphSegmentation.h
#        src/segmentation/GraphSegmentationImpl.cpp
#        src/segmentation/GraphSegmentationImpl.h
#        src/segmentation/PointSet.cpp
#        src/segmentation/PointSet.h)

add_executable(cplusplus
        samples/selectivesearchsegmentation/segmentation.cpp

        src/segmentation/SelectiveSearchSegmentationStrategy.h
        src/segmentation/SelectiveSearchSegmentationStrategyColorImpl.cpp
        src/segmentation/SelectiveSearchSegmentationStrategyColorImpl.h
        src/segmentation/SelectiveSearchSegmentationStrategySizeImpl.cpp
        src/segmentation/SelectiveSearchSegmentationStrategySizeImpl.h
        src/segmentation/SelectiveSearchSegmentationStrategyFillImpl.cpp
        src/segmentation/SelectiveSearchSegmentationStrategyFillImpl.h
        src/segmentation/SelectiveSearchSegmentationStrategyTextureImpl.cpp
        src/segmentation/SelectiveSearchSegmentationStrategyTextureImpl.h

        src/segmentation/SelectiveSearchSegmentationStrategyMultipleImpl.cpp
        src/segmentation/SelectiveSearchSegmentationStrategyMultipleImpl.h
        src/segmentation/SelectiveSearchSegmentationStrategy.cpp

        src/segmentation/SelectiveSearchSegmentation.cpp
        src/segmentation/SelectiveSearchSegmentation.h
        src/segmentation/SelectiveSearchSegmentationImpl.cpp
        src/segmentation/SelectiveSearchSegmentationImpl.h

        src/segmentation/GraphSegmentation.h
        src/segmentation/GraphSegmentation.cpp
        src/segmentation/GraphSegmentationImpl.h
        src/segmentation/GraphSegmentationImpl.cpp
        src/segmentation/PointSet.h
        src/segmentation/PointSet.cpp)
target_link_libraries(cplusplus ${OpenCV_LIBS})