//
// Created by zj on 19-11-23.
//

#ifndef CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGYSIZEIMPL_H
#define CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGYSIZEIMPL_H


#include "SelectiveSearchSegmentationStrategy.h"

class SelectiveSearchSegmentationStrategySizeImpl : public SelectiveSearchSegmentationStrategySize {
public:
    SelectiveSearchSegmentationStrategySizeImpl() {
        name_ = "SelectiveSearchSegmentationStrategySize";
    }

    void setImage(InputArray img, InputArray regions, InputArray sizes, int image_id = -1) override;

    float get(int r1, int r2) override;

    void merge(int r1, int r2) override;

private:
    String name_;

    Mat sizes;
    int size_image;
};


#endif //CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGYSIZEIMPL_H
