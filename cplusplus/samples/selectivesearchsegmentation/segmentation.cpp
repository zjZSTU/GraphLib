//
// Created by zj on 19-11-7.
//

#include "opencv2/ximgproc/segmentation.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <ctime>

using namespace cv;
using namespace cv::ximgproc::segmentation;

static void help() {
    std::cout << std::endl <<
              "A program demonstrating the use and capabilities of a particular image segmentation algorithm described"
              << std::endl <<
              " in Jasper R. R. Uijlings, Koen E. A. van de Sande, Theo Gevers, Arnold W. M. Smeulders: " << std::endl
              <<
              "                       \"Selective Search for Object Recognition\"" << std::endl <<
              "International Journal of Computer Vision, Volume 104 (2), page 154-171, 2013" << std::endl << std::endl
              <<
              "Usage:" << std::endl <<
              "./selectivesearchsegmentation_demo input_image (single|fast|quality)" << std::endl <<
              "Use a to display less rects, d to display more rects, q to quit" << std::endl;
}


int main(int argc, char **argv) {

    if (argc < 3) {
        help();
        return -1;
    }

    Mat img = imread(argv[1]);

    Ptr<SelectiveSearchSegmentation> gs = createSelectiveSearchSegmentation();
    gs->setBaseImage(img);

    if (argv[2][0] == 's') {
        gs->switchToSingleStrategy();
    } else if (argv[2][0] == 'f') {
        gs->switchToSelectiveSearchFast();
    } else if (argv[2][0] == 'q') {
        gs->switchToSelectiveSearchQuality();
    } else {
        help();
        return -2;
    }

    std::vector<Rect> rects;
    gs->process(rects);

    int nb_rects = 10;

    char c = (char) waitKey();

    while (c != 'q') {

        Mat wimg = img.clone();

        int i = 0;

        for (std::vector<Rect>::iterator it = rects.begin(); it != rects.end(); ++it) {
            if (i++ < nb_rects) {
                rectangle(wimg, *it, Scalar(0, 0, 255));
            }
        }

        imshow("Output", wimg);
        c = (char) waitKey();

        if (c == 'd') {
            nb_rects += 10;
        }

        if (c == 'a' && nb_rects > 10) {
            nb_rects -= 10;
        }
    }

    return 0;
}
