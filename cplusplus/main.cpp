#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    std::cout << "Hello, World!" << std::endl;

    cv::Mat img = cv::imread("../lena.jpg");
    cv::imshow("lena", img);
    cv::waitKey(0);

    return 0;
}