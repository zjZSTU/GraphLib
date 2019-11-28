//
// Created by zj on 19-11-28.
//

#ifndef CPLUSPLUS_SELECTIVESEARCHSEGMENTATION_H
#define CPLUSPLUS_SELECTIVESEARCHSEGMENTATION_H

#include <opencv2/opencv.hpp>
#include "GraphSegmentation.h"
#include "SelectiveSearchSegmentationStrategy.h"

using namespace cv;

/** @brief Selective search segmentation algorithm
    The class implements the algorithm described in @cite uijlings2013selective.
*/
class SelectiveSearchSegmentation : public Algorithm {
public:

    /** @brief Set a image used by switch* functions to initialize the class
        @param img The image
    */
    virtual void setBaseImage(InputArray img) = 0;

    /** @brief Initialize the class with the 'Single stragegy' parameters describled in @cite uijlings2013selective.
        @param k The k parameter for the graph segmentation
        @param sigma The sigma parameter for the graph segmentation
    */
    virtual void switchToSingleStrategy(int k = 200, float sigma = 0.8f) = 0;

    /** @brief Initialize the class with the 'Selective search fast' parameters describled in @cite uijlings2013selective.
        @param base_k The k parameter for the first graph segmentation
        @param inc_k The increment of the k parameter for all graph segmentations
        @param sigma The sigma parameter for the graph segmentation
    */
    virtual void switchToSelectiveSearchFast(int base_k = 150, int inc_k = 150, float sigma = 0.8f) = 0;

    /** @brief Initialize the class with the 'Selective search fast' parameters describled in @cite uijlings2013selective.
        @param base_k The k parameter for the first graph segmentation
        @param inc_k The increment of the k parameter for all graph segmentations
        @param sigma The sigma parameter for the graph segmentation
    */
    virtual void switchToSelectiveSearchQuality(int base_k = 150, int inc_k = 150, float sigma = 0.8f) = 0;

    /** @brief Add a new image in the list of images to process.
        @param img The image
    */
    virtual void addImage(InputArray img) = 0;

    /** @brief Clear the list of images to process
    */
    virtual void clearImages() = 0;

    /** @brief Add a new graph segmentation in the list of graph segementations to process.
        @param g The graph segmentation
    */
    virtual void addGraphSegmentation(std::shared_ptr<GraphSegmentation> g) = 0;

    /** @brief Clear the list of graph segmentations to process;
    */
    virtual void clearGraphSegmentations() = 0;

    /** @brief Add a new strategy in the list of strategy to process.
        @param s The strategy
    */
    virtual void addStrategy(std::shared_ptr<SelectiveSearchSegmentationStrategy> s) = 0;

    /** @brief Clear the list of strategy to process;
    */
    virtual void clearStrategies() = 0;

    /** @brief Based on all images, graph segmentations and stragies, computes all possible rects and return them
        @param rects The list of rects. The first ones are more relevents than the lasts ones.
    */
    virtual void process(CV_OUT std::vector<Rect> &rects) = 0;
};

// 辅助函数

/** @brief Create a new SelectiveSearchSegmentation class.
 */
std::shared_ptr<SelectiveSearchSegmentation> createSelectiveSearchSegmentation();

// 辅助类

// Represent a regsion
class Region {
public:
    int id;
    int level;
    int merged_to;
    double rank;
    Rect bounding_box;

    Region() : id(0), level(0), merged_to(0), rank(0) {}

    friend std::ostream &operator<<(std::ostream &os, const Region &n);

    bool operator<(const Region &n) const {
        return rank < n.rank;
    }
};

// Comparator to sort cv::rect (used for a std::map).
struct rectComparator {
    bool operator()(const cv::Rect_<int> &a, const cv::Rect_<int> &b) const {
        if (a.x < b.x) {
            return true;
        }
        if (a.x > b.x) {
            return false;
        }
        if (a.y < b.y) {
            return true;
        }
        if (a.y > b.y) {
            return false;
        }
        if (a.width < b.width) {
            return true;
        }
        if (a.width > b.width) {
            return false;
        }
        if (a.height < b.height) {
            return true;
        }
        if (a.height > b.height) {
            return false;
        }
        return false;
    }
};

// Represent a neighboor
class Neighbour {
public:
    int from;
    int to;
    float similarity;

    friend std::ostream &operator<<(std::ostream &os, const Neighbour &n);

    bool operator<(const Neighbour &n) const {
        return similarity < n.similarity;
    }
};

#endif //CPLUSPLUS_SELECTIVESEARCHSEGMENTATION_H
