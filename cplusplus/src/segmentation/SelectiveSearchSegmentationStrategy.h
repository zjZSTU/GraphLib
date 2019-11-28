//
// Created by zj on 19-11-23.
//

#ifndef CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGY_H
#define CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGY_H

#include <opencv2/opencv.hpp>

using namespace cv;

class SelectiveSearchSegmentationStrategy {
public:
    /** @brief Set a initial image, with a segementation.
        @brief 设置初始图像
        @param img The input image. Any number of channel can be provided
        @param regions A segementation of the image. The parameter must be the same size of img.
        @param sizes The sizes of different regions
        @param image_id If not set to -1, try to cache pre-computations. If the same set og (img, regions, size) is used, the image_id need to be the same.
    */
    virtual void setImage(InputArray img, InputArray regions, InputArray sizes, int image_id = -1) = 0;

    /** @brief Return the score between two regions (between 0 and 1)
        @brief 计算两个区域的相似度，大小在[0,1]之间
        @param r1 The first region
        @param r2 The second region
    */
    virtual float get(int r1, int r2) = 0;

    /** @brief Inform the strategy that two regions will be merged
        @brief 合并两个区域
        @param r1 The first region
        @param r2 The second region
    */
    virtual void merge(int r1, int r2) = 0;
};

// 选择性搜索使用了4种相似度测量策略

class SelectiveSearchSegmentationStrategyColor : public SelectiveSearchSegmentationStrategy {
};

class SelectiveSearchSegmentationStrategySize : public SelectiveSearchSegmentationStrategy {
};

class SelectiveSearchSegmentationStrategyTexture : public SelectiveSearchSegmentationStrategy {
};

class SelectiveSearchSegmentationStrategyFill : public SelectiveSearchSegmentationStrategy {
};

// 创建类Multiple来组合4种相似性度量策略

class SelectiveSearchSegmentationStrategyMultiple : public SelectiveSearchSegmentationStrategy {
public:

    /** @brief Add a new sub-strategy
        @param g The strategy
        @param weight The weight of the strategy
    */
    virtual void addStrategy(std::shared_ptr<SelectiveSearchSegmentationStrategy> g, float weight) = 0;
    /** @brief Remove all sub-strategies
    */
    virtual void clearStrategies() = 0;
};

// 辅助函数

/** @brief Create a new color-based strategy */
std::shared_ptr<SelectiveSearchSegmentationStrategyColor> createSelectiveSearchSegmentationStrategyColor();

/** @brief Create a new size-based strategy */
std::shared_ptr<SelectiveSearchSegmentationStrategySize> createSelectiveSearchSegmentationStrategySize();

/** @brief Create a new size-based strategy */
std::shared_ptr<SelectiveSearchSegmentationStrategyTexture> createSelectiveSearchSegmentationStrategyTexture();

/** @brief Create a new fill-based strategy */
std::shared_ptr<SelectiveSearchSegmentationStrategyFill> createSelectiveSearchSegmentationStrategyFill();

/** @brief Create a new multiple strategy */
std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple> createSelectiveSearchSegmentationStrategyMultiple();

/** @brief Create a new multiple strategy and set one subtrategy
    @param s1 The first strategy
*/
std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple>
createSelectiveSearchSegmentationStrategyMultiple(std::shared_ptr<SelectiveSearchSegmentationStrategy> s1);

/** @brief Create a new multiple strategy and set two subtrategies, with equal weights
    @param s1 The first strategy
    @param s2 The second strategy
*/
std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple>
createSelectiveSearchSegmentationStrategyMultiple(std::shared_ptr<SelectiveSearchSegmentationStrategy> s1,
                                                  std::shared_ptr<SelectiveSearchSegmentationStrategy> s2);


/** @brief Create a new multiple strategy and set three subtrategies, with equal weights
    @param s1 The first strategy
    @param s2 The second strategy
    @param s3 The third strategy
*/
std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple>
createSelectiveSearchSegmentationStrategyMultiple(std::shared_ptr<SelectiveSearchSegmentationStrategy> s1,
                                                  std::shared_ptr<SelectiveSearchSegmentationStrategy> s2,
                                                  std::shared_ptr<SelectiveSearchSegmentationStrategy> s3);

/** @brief Create a new multiple strategy and set four subtrategies, with equal weights
    @param s1 The first strategy
    @param s2 The second strategy
    @param s3 The third strategy
    @param s4 The forth strategy
*/
std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple>
createSelectiveSearchSegmentationStrategyMultiple(std::shared_ptr<SelectiveSearchSegmentationStrategy> s1,
                                                  std::shared_ptr<SelectiveSearchSegmentationStrategy> s2,
                                                  std::shared_ptr<SelectiveSearchSegmentationStrategy> s3,
                                                  std::shared_ptr<SelectiveSearchSegmentationStrategy> s4);

#endif //CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGY_H
