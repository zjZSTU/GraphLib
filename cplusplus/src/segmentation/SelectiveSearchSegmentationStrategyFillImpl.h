//
// Created by zj on 19-11-23.
//

#ifndef CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGYFILLIMPL_H
#define CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGYFILLIMPL_H


#include "SelectiveSearchSegmentationStrategy.h"

class SelectiveSearchSegmentationStrategyFillImpl : public SelectiveSearchSegmentationStrategyFill {
public:
    SelectiveSearchSegmentationStrategyFillImpl() {
        name_ = "SelectiveSearchSegmentationStrategyFill";
    }

    void setImage(InputArray img, InputArray regions, InputArray sizes, int image_id = -1) override;

    float get(int r1, int r2) override;

    void merge(int r1, int r2) override;

private:
    String name_;

    Mat sizes;
    int size_image;
    std::vector<Rect> bounding_rects;
};

#endif //CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGYFILLIMPL_H
