//
// Created by zj on 19-11-28.
//

#ifndef CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONIMPL_H
#define CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONIMPL_H

#include <opencv2/opencv.hpp>
#include "SelectiveSearchSegmentation.h"

using namespace cv;

class SelectiveSearchSegmentationImpl : public SelectiveSearchSegmentation {
public:
    SelectiveSearchSegmentationImpl() {
        name_ = "SelectiveSearchSegmentation";
    }

    ~SelectiveSearchSegmentationImpl() override {
    };

    void write(FileStorage &fs) const override {
        fs << "name" << name_;
    }

    virtual void read(const FileNode &fn) override {
        CV_Assert((String) fn["name"] == name_);
    }

    virtual void setBaseImage(InputArray img) override;

    virtual void switchToSingleStrategy(int k = 200, float sigma = 0.8) override;

    virtual void switchToSelectiveSearchFast(int base_k = 150, int inc_k = 150, float sigma = 0.8) override;

    virtual void switchToSelectiveSearchQuality(int base_k = 150, int inc_k = 150, float sigma = 0.8) override;

    virtual void addImage(InputArray img) override;

    virtual void clearImages() override;

    virtual void addGraphSegmentation(std::shared_ptr<GraphSegmentation> g) override;

    virtual void clearGraphSegmentations() override;

    virtual void addStrategy(std::shared_ptr<SelectiveSearchSegmentationStrategy> s) override;

    virtual void clearStrategies() override;

    virtual void process(std::vector<Rect> &rects) override;


private:
    String name_;

    Mat base_image;
    std::vector<Mat> images;
    std::vector<std::shared_ptr<GraphSegmentation> > segmentations;
    std::vector<std::shared_ptr<SelectiveSearchSegmentationStrategy> > strategies;

    void hierarchicalGrouping(const Mat &img, std::shared_ptr<SelectiveSearchSegmentationStrategy> &s, const Mat &img_regions,
                              const Mat_<char> &is_neighbour, const Mat_<int> &sizes, int &nb_segs,
                              const std::vector<Rect> &bounding_rects, std::vector<Region> &regions, int region_id);
};


#endif //CPLUSPLUS_SELECTIVESEARCHSEGMENTATIONIMPL_H
