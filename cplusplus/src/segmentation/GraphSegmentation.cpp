//
// Created by zj on 19-11-28.
//

#include "GraphSegmentation.h"
#include "GraphSegmentationImpl.h"

std::shared_ptr<GraphSegmentation> createGraphSegmentation(double sigma, float k, int min_size) {

    std::shared_ptr<GraphSegmentation> graphseg = std::make_shared<GraphSegmentationImpl>();

    graphseg->setSigma(sigma);
    graphseg->setK(k);
    graphseg->setMinSize(min_size);

    return graphseg;
}
