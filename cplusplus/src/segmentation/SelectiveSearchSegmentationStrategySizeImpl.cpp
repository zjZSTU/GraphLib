//
// Created by zj on 19-11-23.
//

#include "SelectiveSearchSegmentationStrategySizeImpl.h"

void SelectiveSearchSegmentationStrategySizeImpl::setImage(InputArray img_, InputArray, InputArray sizes_,
                                                           int /* image_id */) {
    Mat img = img_.getMat();
    size_image = img.rows * img.cols;
    sizes = sizes_.getMat();
}

float SelectiveSearchSegmentationStrategySizeImpl::get(int r1, int r2) {

    int size_r1 = sizes.at<int>(r1);
    int size_r2 = sizes.at<int>(r2);

    return max(min(1.0f - (float) (size_r1 + size_r2) / (float) (size_image), 1.0f), 0.0f);
}

void SelectiveSearchSegmentationStrategySizeImpl::merge(int /* r1 */, int /* r2 */) {
    // Nothing to do (sizes are merged at parent level)
}
