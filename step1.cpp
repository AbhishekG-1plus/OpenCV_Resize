#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat inputImage = cv::imread("/Users/abhishekgadekar/Desktop/deepedge/openCV/G178_2-1080.BMP");

    if (inputImage.empty()) {
        std::cerr << "Error: Unable to load the input image." << std::endl;
        return -1;
    }
    int width = 960;
    int height = 540;

    cv::Mat resized_nearest, resized_linear, resized_cubic;

    cv::resize(inputImage, resized_nearest, cv::Size(width, height), 0, 0, cv::INTER_NEAREST);
    cv::resize(inputImage, resized_linear, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);
    cv::resize(inputImage, resized_cubic, cv::Size(width, height), 0, 0, cv::INTER_CUBIC);

    cv::imshow("Original Image",inputImage);
    cv::imshow("Resized Nearest", resized_nearest);
    cv::imshow("Resized Linear", resized_linear);
    cv::imshow("Resized Cubic", resized_cubic);

    cv::waitKey(0);

    cv::destroyAllWindows();

    return 0;
}
