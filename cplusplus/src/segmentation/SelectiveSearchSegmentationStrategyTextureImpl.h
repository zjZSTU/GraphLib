//
// Created by zj on 19-11-23.
//

#ifndef CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGYTEXTUREIMPL_H
#define CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGYTEXTUREIMPL_H


#include "SelectiveSearchSegmentationStrategy.h"

class SelectiveSearchSegmentationStrategyTextureImpl : public SelectiveSearchSegmentationStrategyTexture {
public:
    SelectiveSearchSegmentationStrategyTextureImpl() {
        name_ = "SelectiveSearchSegmentationStrategyTexture";
        last_image_id = -1;
    }

    void setImage(InputArray img, InputArray regions, InputArray sizes, int image_id = -1) override;

    float get(int r1, int r2) override;

    void merge(int r1, int r2) override;

private:
    String name_;

    Mat histograms; //[Region X Histogram]
    Mat sizes;
    int histogram_size;

    int last_image_id; // If the image_id is not equal to -1 and the same as the previous call for setImage, computations are used again
    Mat last_histograms;
};


#endif //CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGYTEXTUREIMPL_H
