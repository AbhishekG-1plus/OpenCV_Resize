#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

int main() {
    // Load the input image
    cv::Mat inputImage = cv::imread("/Users/abhishekgadekar/Desktop/deepedge/openCV/G178_2-1080.BMP");
    cv::Mat resized_nearest, resized_linear, resized_cubic;

    if (inputImage.empty()) {
        cerr << "Error: Unable to load the input image." << endl;
        return -1;
    }

    int width = 960;
    int height = 540;

    double time_nearest = 0, time_linear = 0, time_cubic = 0;

    int num_iterations = 1000;

    int64 start = cv::getTickCount();
    for (int i = 0; i < num_iterations; ++i) {
        cv::resize(inputImage,resized_nearest, cv::Size(width, height), 0, 0, cv::INTER_NEAREST);
    }
    time_nearest = (cv::getTickCount() - start) / cv::getTickFrequency();

    int64 start_l = cv::getTickCount();
    for (int i = 0; i < num_iterations; ++i) {
        cv::resize(inputImage,resized_linear, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);
    }
    time_linear = (cv::getTickCount() - start_l) / cv::getTickFrequency();

    int64 start_c = cv::getTickCount();
    for (int i = 0; i < num_iterations; ++i) {
        cv::resize(inputImage,resized_cubic, cv::Size(width, height), 0, 0, cv::INTER_CUBIC);
    }
    time_cubic = (cv::getTickCount() - start_c) / cv::getTickFrequency();

    cout<<"Step 2"<<endl;
    cout << "Time taken for " << num_iterations << " iteration using INTER_NEAREST : " << time_nearest * 1000 << " ms" << std::endl;
    cout << "Time taken for " << num_iterations << " iteration using INTER_LINEAR : " << time_linear * 1000 << " ms" << std::endl;
    cout << "Time taken for " << num_iterations << " iteration using INTER_CUBIC : " << time_cubic * 1000 << " ms" << std::endl;

    return 0;
}
