//
// Created by zj on 19-11-5.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "../../src/segmentation/GraphSegmentation.h"

using namespace std;
using namespace cv;

Scalar hsv_to_rgb(Scalar);

Scalar color_mapping(int);

static void help() {
    std::cout << std::endl <<
              "A program demonstrating the use and capabilities of a particular graph based image" << std::endl <<
              "segmentation algorithm described in P. Felzenszwalb, D. Huttenlocher," << std::endl <<
              "             \"Efficient Graph-Based Image Segmentation\"" << std::endl <<
              "International Journal of Computer Vision, Vol. 59, No. 2, September 2004" << std::endl << std::endl <<
              "Usage:" << std::endl <<
              "./graphsegmentation_demo input_image output_image [simga=0.5] [k=300] [min_size=100]" << std::endl;
}

Scalar hsv_to_rgb(Scalar c) {
    Mat in(1, 1, CV_32FC3);
    Mat out(1, 1, CV_32FC3);

    float *p = in.ptr<float>(0);
    p[0] = (float) c[0] * 360.0f;
    p[1] = (float) c[1];
    p[2] = (float) c[2];

    cvtColor(in, out, COLOR_HSV2RGB);

    Scalar t;
    Vec3f p2 = out.at<Vec3f>(0, 0);
    t[0] = (int) (p2[0] * 255);
    t[1] = (int) (p2[1] * 255);
    t[2] = (int) (p2[2] * 255);

    return t;
}

Scalar color_mapping(int segment_id) {
    double base = (double) (segment_id) * 0.618033988749895 + 0.24443434;

    return hsv_to_rgb(Scalar(fmod(base, 1.2), 0.95, 0.80));
}

int main(int argc, char **argv) {
    if (argc < 2 || argc > 6) {
        help();
        return -1;
    }

    shared_ptr<GraphSegmentation> gs = createGraphSegmentation();
    if (argc > 3)
        gs->setSigma(atof(argv[3]));
    if (argc > 4)
        gs->setK((float) atoi(argv[4]));
    if (argc > 5)
        gs->setMinSize(atoi(argv[5]));
    if (!gs) {
        std::cerr << "Failed to create GraphSegmentation Algorithm." << std::endl;
        return -2;
    }

    Mat input, output, output_image;
    input = imread(argv[1]);
    if (!input.data) {
        std::cerr << "Failed to load input image" << std::endl;
        return -3;
    }
    gs->processImage(input, output);

    double min, max;
    minMaxLoc(output, &min, &max);

    int nb_segs = (int) max + 1;
    std::cout << nb_segs << " segments" << std::endl;
    output_image = Mat::zeros(output.rows, output.cols, CV_8UC3);

    uint *p;
    uchar *p2;
    for (int i = 0; i < output.rows; i++) {
        p = output.ptr<uint>(i);
        p2 = output_image.ptr<uchar>(i);

        for (int j = 0; j < output.cols; j++) {
            Scalar color = color_mapping(p[j]);
            p2[j * 3] = (uchar) color[0];
            p2[j * 3 + 1] = (uchar) color[1];
            p2[j * 3 + 2] = (uchar) color[2];
        }
    }
    imwrite(argv[2], output_image);
    std::cout << "Image written to " << argv[2] << std::endl;

    return 0;
}