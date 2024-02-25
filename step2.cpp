#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Load the input image
    cv::Mat inputImage = cv::imread("/Users/abhishekgadekar/Desktop/deepedge/openCV/G178_2-1080.BMP");
    cv::Mat resized_nearest, resized_linear, resized_cubic;

    if (inputImage.empty()) {
        std::cerr << "Error: Unable to load the input image." << std::endl;
        return -1;
    }

    int width = 960;
    int height = 540;

    double time_nearest = 0, time_linear = 0, time_cubic = 0;

    int num_iterations = 1000;

    for (int i = 0; i < num_iterations; ++i) {
        int64 start = cv::getTickCount();

        cv::resize(inputImage,resized_nearest, cv::Size(width, height), 0, 0, cv::INTER_NEAREST);

        time_nearest += (cv::getTickCount() - start) / cv::getTickFrequency();
    }

    for (int i = 0; i < num_iterations; ++i) {
        int64 start = cv::getTickCount();

        cv::resize(inputImage,resized_linear, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);

        time_linear += (cv::getTickCount() - start) / cv::getTickFrequency();
    }

    for (int i = 0; i < num_iterations; ++i) {
        int64 start = cv::getTickCount();

        cv::resize(inputImage,resized_cubic, cv::Size(width, height), 0, 0, cv::INTER_CUBIC);

        time_cubic += (cv::getTickCount() - start) / cv::getTickFrequency();
    }

    // If we need average time, we can execute below lines
    // time_nearest /= num_iterations;
    // time_linear /= num_iterations;
    // time_cubic /= num_iterations;

    std::cout << "Time taken for " << num_iterations << " iteration using INTER_NEAREST : " << time_nearest * 1000 << " ms" << std::endl;
    std::cout << "Time taken for " << num_iterations << " iteration using INTER_LINEAR : " << time_linear * 1000 << " ms" << std::endl;
    std::cout << "Time taken for " << num_iterations << " iteration using INTER_CUBIC : " << time_cubic * 1000 << " ms" << std::endl;

    return 0;
}
