//
// Created by zj on 19-11-28.
//

#ifndef CPLUSPLUS_GRAPHSEGMENTATION_H
#define CPLUSPLUS_GRAPHSEGMENTATION_H

#include <opencv2/opencv.hpp>

using namespace cv;

/** @brief Graph Based Segmentation Algorithm.
    The class implements the algorithm described in @cite PFF2004 .
 */
class GraphSegmentation {
public:
/** @brief Segment an image and store output in dst
    @param src The input image. Any number of channel (1 (Eg: Gray), 3 (Eg: RGB), 4 (Eg: RGB-D)) can be provided
    @param dst The output segmentation. It's a CV_32SC1 Mat with the same number of cols and rows as input image, with an unique, sequential, id for each pixel.
*/
    virtual void processImage(InputArray src, OutputArray dst) = 0;

    virtual void setSigma(double sigma) = 0;

    virtual double getSigma() = 0;

    virtual void setK(float k) = 0;

    virtual float getK() = 0;

    virtual void setMinSize(int min_size) = 0;

    virtual int getMinSize() = 0;
};

/** @brief Creates a graph based segmentor
    @param sigma The sigma parameter, used to smooth image
    @param k The k parameter of the algorythm
    @param min_size The minimum size of segments
 */
std::shared_ptr<GraphSegmentation> createGraphSegmentation(double sigma = 0.5, float k = 300, int min_size = 100);

#endif //CPLUSPLUS_GRAPHSEGMENTATION_H
