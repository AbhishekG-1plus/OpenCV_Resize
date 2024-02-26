#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Enum for interpolation methods
enum Interpolation {
    INTER_NEAREST_1,
    INTER_LINEAR_2,
    INTER_CUBIC_3
};

// Nearest Neighbor Interpolation
int nearestNeighbor(const Mat& input, double y, double x) {
    int height = input.rows;
    int width = input.cols;

    int y_rounded = static_cast<int>(round(y));
    int x_rounded = static_cast<int>(round(x));

    if (y_rounded < 0 || y_rounded >= height || x_rounded < 0 || x_rounded >= width)
        return 0; // Out of bounds, return default value

    return input.at<uchar>(y_rounded, x_rounded);
}

// Bilinear Interpolation
double bilinearInterpolation(const Mat& input, double y, double x) {
    int height = input.rows;
    int width = input.cols;

    int y_floor = static_cast<int>(floor(y));
    int x_floor = static_cast<int>(floor(x));
    int y_ceil = static_cast<int>(ceil(y));
    int x_ceil = static_cast<int>(ceil(x));

    double y_fraction = y - y_floor;
    double x_fraction = x - x_floor;

    double top_left = input.at<uchar>(y_floor, x_floor);
    double top_right = input.at<uchar>(y_floor, x_ceil);
    double bottom_left = input.at<uchar>(y_ceil, x_floor);
    double bottom_right = input.at<uchar>(y_ceil, x_ceil);

    double top_interpolation = top_left * (1 - x_fraction) + top_right * x_fraction;
    double bottom_interpolation = bottom_left * (1 - x_fraction) + bottom_right * x_fraction;

    return top_interpolation * (1 - y_fraction) + bottom_interpolation * y_fraction;
}

// Bicubic Interpolation
double cubicInterpolation(double p0, double p1, double p2, double p3, double x) {
    return 0.5 * (
        p1 + (x * (p2 - p0 + x * (2.0 * p0 - 5.0 * p1 + 4.0 * p2 - p3 + x * (3.0 * (p1 - p2) + p3 - p0))))
    );
}

double bicubicInterpolation(const Mat& input, double y, double x) {
    int height = input.rows;
    int width = input.cols;

    int y_floor = static_cast<int>(floor(y));
    int x_floor = static_cast<int>(floor(x));

    double y_fraction = y - y_floor;
    double x_fraction = x - x_floor;

    double interpolated_value = 0.0;
    for (int j = -1; j <= 2; ++j) {
        for (int i = -1; i <= 2; ++i) {
            int yy = min(max(y_floor + j, 0), height - 1);
            int xx = min(max(x_floor + i, 0), width - 1);
            interpolated_value += input.at<uchar>(yy, xx) * cubicInterpolation(
                input.at<uchar>(min(height - 1, max(yy - 1, 0)), xx),
                input.at<uchar>(yy, min(width - 1, max(xx - 1, 0))),
                input.at<uchar>(yy, min(width - 1, max(xx + 1, 0))),
                input.at<uchar>(min(height - 1, max(yy + 1, 0)), xx),
                x - (x_floor + i)
            ) * cubicInterpolation(1, 1, 1, 1, y - (y_floor + j));
        }
    }
    return interpolated_value;
}


void resizeImage(const Mat& input, Mat& output, double scale, Interpolation method) {
    int new_height = static_cast<int>(round(input.rows * scale));
    int new_width = static_cast<int>(round(input.cols * scale));

    output.create(new_height, new_width, CV_8UC1);

    for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            double old_i = i / scale;
            double old_j = j / scale;
            switch (method) {
                case INTER_NEAREST_1:
                    output.at<uchar>(i, j) = nearestNeighbor(input, old_i, old_j);
                    break;
                case INTER_LINEAR_2:
                    output.at<uchar>(i, j) = bilinearInterpolation(input, old_i, old_j);
                    break;
                case INTER_CUBIC_3:
                    output.at<uchar>(i, j) = static_cast<uchar>(bicubicInterpolation(input, old_i, old_j));
                    break;
            }
        }
    }
}

int main() {
    
    Mat input = imread("/Users/abhishekgadekar/Desktop/deepedge/openCV/G178_2-1080.BMP", IMREAD_GRAYSCALE);
    if (input.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    Mat output_nearest, output_linear, output_cubic;
    double scale = 0.5;

    
    resizeImage(input, output_nearest, scale, INTER_NEAREST_1);

   
    resizeImage(input, output_linear, scale, INTER_LINEAR_2);

   
    resizeImage(input, output_cubic, scale, INTER_CUBIC_3);


    cout<<"Reached till here"<<endl;
   
    imshow("Nearest Neighbor Interpolation", output_nearest);
    imshow("Linear Interpolation", output_linear);
    imshow("Cubic Interpolation", output_cubic);

    double time_nearest = 0, time_linear = 0, time_cubic = 0;

    int num_iterations = 1000;

    for (int i = 0; i < num_iterations; ++i) {
        int64 start = cv::getTickCount();

        resizeImage(input, output_nearest, scale, INTER_NEAREST_1);

        time_nearest += (cv::getTickCount() - start) / cv::getTickFrequency();
    }

    for (int i = 0; i < num_iterations; ++i) {
        int64 start = cv::getTickCount();

        resizeImage(input, output_linear, scale, INTER_LINEAR_2);

        time_linear += (cv::getTickCount() - start) / cv::getTickFrequency();
    }

    for (int i = 0; i < num_iterations; ++i) {
        int64 start = cv::getTickCount();

        resizeImage(input, output_cubic, scale, INTER_CUBIC_3);

        time_cubic += (cv::getTickCount() - start) / cv::getTickFrequency();
    }


    cout<<"Step 3"<<endl;

    cout << "Time taken for " << num_iterations << " iteration using custom INTER_NEAREST : " << time_nearest * 1000 << " ms" << std::endl;
    cout << "Time taken for " << num_iterations << " iteration using custom INTER_LINEAR : " << time_linear * 1000 << " ms" << std::endl;
    cout << "Time taken for " << num_iterations << " iteration using custom INTER_CUBIC : " << time_cubic * 1000 << " ms" << std::endl;

    waitKey(0);

    return 0;
}
