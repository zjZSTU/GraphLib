//
// Created by zj on 19-11-23.
//

#include "SelectiveSearchSegmentationStrategyMultipleImpl.h"

void SelectiveSearchSegmentationStrategyMultipleImpl::addStrategy(
        std::shared_ptr<SelectiveSearchSegmentationStrategy> g, float weight) {
    strategies.push_back(g);
    weights.push_back(weight);
    weights_total += weight;
}

void SelectiveSearchSegmentationStrategyMultipleImpl::clearStrategies() {
    strategies.clear();
    weights.clear();
    weights_total = 0;
}

void SelectiveSearchSegmentationStrategyMultipleImpl::setImage(
        InputArray img_, InputArray regions_, InputArray sizes_, int image_id) {
    for (unsigned int i = 0; i < strategies.size(); i++) {
        strategies[i]->setImage(img_, regions_, sizes_, image_id);
    }
}

float SelectiveSearchSegmentationStrategyMultipleImpl::get(int r1, int r2) {
    float tt = 0;

    for (unsigned int i = 0; i < strategies.size(); i++) {
        tt += weights[i] * strategies[i]->get(r1, r2);
    }

    return tt / weights_total;
}

void SelectiveSearchSegmentationStrategyMultipleImpl::merge(int r1, int r2) {
    for (unsigned int i = 0; i < strategies.size(); i++) {
        strategies[i]->merge(r1, r2);
    }
}