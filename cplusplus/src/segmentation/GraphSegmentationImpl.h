//
// Created by zj on 19-11-5.
//

#ifndef CPLUSPLUS_GRAPHSEGMENTATIONIMPL_H
#define CPLUSPLUS_GRAPHSEGMENTATIONIMPL_H

#include <iostream>
#include <cstring>
#include <opencv2/core/mat.hpp>
#include "PointSet.h"
#include "GraphSegmentation.h"

using namespace cv;

class Edge {
public:
    int from;
    int to;
    float weight;

    bool operator<(const Edge &e) const {
        return weight < e.weight;
    }
};

class GraphSegmentationImpl : public GraphSegmentation {
public:
    GraphSegmentationImpl() {
        sigma = 0.5;
        k = 300;
        min_size = 100;
        name_ = "GraphSegmentation";
    }

    ~GraphSegmentationImpl() = default;

    void processImage(InputArray src, OutputArray dst);

    void setSigma(double sigma_) {
        if (sigma_ <= 0) { sigma_ = 0.001; }
        sigma = sigma_;
    }

    double getSigma() { return sigma; }

    void setK(float k_) { k = k_; }

    float getK() { return k; }

    void setMinSize(int min_size_) { min_size = min_size_; }

    int getMinSize() { return min_size; }

    void write(FileStorage &fs) const {
        fs << "name" << name_
           << "sigma" << sigma
           << "k" << k
           << "min_size" << (int) min_size;
    }

    void read(const FileNode &fn) {
        CV_Assert((String) fn["name"] == name_);

        sigma = (double) fn["sigma"];
        k = (float) fn["k"];
        min_size = (int) (int) fn["min_size"];
    }

private:
    double sigma;
    float k;
    int min_size;
    std::string name_;

    // Pre-filter the image
    void filter(const Mat &img, Mat &img_filtered);

    // Build the graph between each pixels
    void buildGraph(Edge **edges, int &nb_edges, const Mat &img_filtered);

    // Segment the graph
    void segmentGraph(Edge *edges, const int &nb_edges, const Mat &img_filtered, PointSet **es);

    // Remove areas too small
    void filterSmallAreas(Edge *edges, const int &nb_edges, PointSet *es);

    // Map the segemented graph to a Mat with uniques, sequentials ids
    void finalMapping(PointSet *es, Mat &output);
};


#endif //CPLUSPLUS_GRAPHSEGMENTATIONIMPL_H
