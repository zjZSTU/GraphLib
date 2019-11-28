//
// Created by zj on 19-11-23.
//

#ifndef CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGYMULTIPLEIMPL_H
#define CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGYMULTIPLEIMPL_H


#include "SelectiveSearchSegmentationStrategy.h"

class SelectiveSearchSegmentationStrategyMultipleImpl : public SelectiveSearchSegmentationStrategyMultiple {
public:
    SelectiveSearchSegmentationStrategyMultipleImpl() {
        name_ = "SelectiveSearchSegmentationStrategyMultiple";
        weights_total = 0;
    }

    void setImage(InputArray img, InputArray regions, InputArray sizes, int image_id = -1) override;

    float get(int r1, int r2) override;

    void merge(int r1, int r2) override;

    void addStrategy(std::shared_ptr<SelectiveSearchSegmentationStrategy> g, float weight) override;

    void clearStrategies() override;

private:
    String name_;
    std::vector<std::shared_ptr<SelectiveSearchSegmentationStrategy> > strategies;
    std::vector<float> weights;
    float weights_total;
};

#endif //CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONSTRATEGYMULTIPLEIMPL_H
