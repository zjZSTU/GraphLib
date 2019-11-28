//
// Created by zj on 19-11-28.
//

#include "SelectiveSearchSegmentationStrategy.h"
#include "SelectiveSearchSegmentationStrategyTextureImpl.h"
#include "SelectiveSearchSegmentationStrategyColorImpl.h"
#include "SelectiveSearchSegmentationStrategySizeImpl.h"
#include "SelectiveSearchSegmentationStrategyFillImpl.h"
#include "SelectiveSearchSegmentationStrategyMultipleImpl.h"

std::shared_ptr<SelectiveSearchSegmentationStrategyColor> createSelectiveSearchSegmentationStrategyColor() {
    std::shared_ptr<SelectiveSearchSegmentationStrategyColor> s = std::make_shared<SelectiveSearchSegmentationStrategyColorImpl>();
    return s;
}

std::shared_ptr<SelectiveSearchSegmentationStrategySize> createSelectiveSearchSegmentationStrategySize() {
    std::shared_ptr<SelectiveSearchSegmentationStrategySize> s = std::make_shared<SelectiveSearchSegmentationStrategySizeImpl>();
    return s;
}

std::shared_ptr<SelectiveSearchSegmentationStrategyFill> createSelectiveSearchSegmentationStrategyFill() {
    std::shared_ptr<SelectiveSearchSegmentationStrategyFill> s = std::make_shared<SelectiveSearchSegmentationStrategyFillImpl>();
    return s;
}

std::shared_ptr<SelectiveSearchSegmentationStrategyTexture> createSelectiveSearchSegmentationStrategyTexture() {
    std::shared_ptr<SelectiveSearchSegmentationStrategyTexture> s = std::make_shared<SelectiveSearchSegmentationStrategyTextureImpl>();
    return s;
}

std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple> createSelectiveSearchSegmentationStrategyMultiple() {
    std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple> s = std::make_shared<SelectiveSearchSegmentationStrategyMultipleImpl>();
    return s;
}

// Helpers to quickly create a multiple stragegy with 1 to 4 equal strageries
std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple>
createSelectiveSearchSegmentationStrategyMultiple(std::shared_ptr<SelectiveSearchSegmentationStrategy> s1) {
    std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple> s = makePtr<SelectiveSearchSegmentationStrategyMultipleImpl>();

    s->addStrategy(s1, 1.0f);

    return s;
}

std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple>
createSelectiveSearchSegmentationStrategyMultiple(std::shared_ptr<SelectiveSearchSegmentationStrategy> s1,
                                                  std::shared_ptr<SelectiveSearchSegmentationStrategy> s2) {
    std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple> s = makePtr<SelectiveSearchSegmentationStrategyMultipleImpl>();

    s->addStrategy(s1, 0.5f);
    s->addStrategy(s2, 0.5f);

    return s;
}

std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple>
createSelectiveSearchSegmentationStrategyMultiple(std::shared_ptr<SelectiveSearchSegmentationStrategy> s1,
                                                  std::shared_ptr<SelectiveSearchSegmentationStrategy> s2,
                                                  std::shared_ptr<SelectiveSearchSegmentationStrategy> s3) {
    std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple> s = makePtr<SelectiveSearchSegmentationStrategyMultipleImpl>();

    s->addStrategy(s1, 0.3333f);
    s->addStrategy(s2, 0.3333f);
    s->addStrategy(s3, 0.3333f);

    return s;
}

std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple>
createSelectiveSearchSegmentationStrategyMultiple(std::shared_ptr<SelectiveSearchSegmentationStrategy> s1,
                                                  std::shared_ptr<SelectiveSearchSegmentationStrategy> s2,
                                                  std::shared_ptr<SelectiveSearchSegmentationStrategy> s3,
                                                  std::shared_ptr<SelectiveSearchSegmentationStrategy> s4) {
    std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple> s = makePtr<SelectiveSearchSegmentationStrategyMultipleImpl>();

    s->addStrategy(s1, 0.25f);
    s->addStrategy(s2, 0.25f);
    s->addStrategy(s3, 0.25f);
    s->addStrategy(s4, 0.25f);

    return s;
}