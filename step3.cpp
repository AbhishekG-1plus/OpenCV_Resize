#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
enum Interpolation {
    INTER_NEAREST,
    INTER_LINEAR,
    INTER_CUBIC
};

// Nearest Neighbor Interpolation
int nearestNeighbor(const vector< vector<int>>& input, double y, double x) {
    int height = input.size();
    int width = input[0].size();

    int y_rounded = static_cast<int>( round(y));
    int x_rounded = static_cast<int>( round(x));

    if (y_rounded < 0 || y_rounded >= height || x_rounded < 0 || x_rounded >= width)
        return 0; // Out of bounds, return default value

    return input[y_rounded][x_rounded];
}

//Bi-Linear Interpolation
double bilinearInterpolation(const  vector< vector<int>>& input, double y, double x) {
    int height = input.size();
    int width = input[0].size();

    int y_floor = static_cast<int>( floor(y));
    int x_floor = static_cast<int>( floor(x));
    int y_ceil = static_cast<int>( ceil(y));
    int x_ceil = static_cast<int>( ceil(x));

    double y_fraction = y - y_floor;
    double x_fraction = x - x_floor;

    double top_left = input[y_floor][x_floor];
    double top_right = input[y_floor][x_ceil];
    double bottom_left = input[y_ceil][x_floor];
    double bottom_right = input[y_ceil][x_ceil];

    double top_interpolation = top_left * (1 - x_fraction) + top_right * x_fraction;
    double bottom_interpolation = bottom_left * (1 - x_fraction) + bottom_right * x_fraction;

    return top_interpolation * (1 - y_fraction) + bottom_interpolation * y_fraction;
}

//Bi-Cubic Interpolation
double cubicInterpolation(double p0, double p1, double p2, double p3, double x) {
    return 0.5 * (
        p1 + (x * (p2 - p0 + x * (2.0 * p0 - 5.0 * p1 + 4.0 * p2 - p3 + x * (3.0 * (p1 - p2) + p3 - p0))))
    );
}

double bicubicInterpolation(const  vector< vector<int>>& input, double y, double x) {
    int height = input.size();
    int width = input[0].size();

    int y_floor = static_cast<int>( floor(y));
    int x_floor = static_cast<int>( floor(x));

    double y_fraction = y - y_floor;
    double x_fraction = x - x_floor;

    double interpolated_value = 0.0;
    for (int j = -1; j <= 2; ++j) {
        for (int i = -1; i <= 2; ++i) {
            int yy =  min( max(y_floor + j, 0), height - 1);
            int xx =  min( max(x_floor + i, 0), width - 1);
            interpolated_value += input[yy][xx] * cubicInterpolation(
                input[ min(height - 1,  max(yy - 1, 0))][xx],
                input[yy][ min(width - 1,  max(xx - 1, 0))],
                input[yy][ min(width - 1,  max(xx + 1, 0))],
                input[ min(height - 1,  max(yy + 1, 0))][xx],
                x - (x_floor + i)
            ) * cubicInterpolation(1, 1, 1, 1, y - (y_floor + j));
        }
    }
    return interpolated_value;
}

// Function to resize an input image with different interpolation methods
void resizeImage(const  vector< vector<int>>& input,  vector< vector<int>>& output, double scale, Interpolation method) {
    // Calculate dimensions of resized image
    int new_height = static_cast<int>( round(input.size() * scale));
    int new_width = static_cast<int>( round(input[0].size() * scale));

    // Resize output image
    output.resize(new_height,  vector<int>(new_width));

    // Perform interpolation based on the selected method
    for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            double old_i = i / scale;
            double old_j = j / scale;
            switch (method) {
                case INTER_NEAREST:
                    output[i][j] = nearestNeighbor(input, old_i, old_j);
                    break;
                case INTER_LINEAR:
                    output[i][j] = bilinearInterpolation(input, old_i, old_j);
                    break;
                case INTER_CUBIC:
                    output[i][j] = static_cast<int>(bicubicInterpolation(input, old_i, old_j));
                    break;
            }
        }
    }
}

int main() {
    std::vector<std::vector<int>> input;
    int width, height, channels;
    unsigned char *img_data = stbi_load("input_image.jpg", &width, &height, &channels, 0);
    
    // Convert image data to vector of vectors
    for (int i = 0; i < height; ++i) {
        std::vector<int> row;
        for (int j = 0; j < width; ++j) {
            row.push_back(img_data[i * width + j]);
        }
        input.push_back(row);
    }
    
    stbi_image_free(img_data); // Free the loaded image data
    vector<vector<int>> output_nearest, output_linear, output_cubic;
    double scale = 0.5;

    // Resize with INTER_NEAREST
    resizeImage(input, output_nearest, scale, INTER_NEAREST);

    // Resize with INTER_LINEAR
    resizeImage(input, output_linear, scale, INTER_LINEAR);

    // Resize with INTER_CUBIC
    resizeImage(input, output_cubic, scale, INTER_CUBIC);

    // Display resized images
    cout << "Nearest Neighbor Interpolation:" << endl;
    for (const auto& row : output_nearest) {
        for (int pixel : row) {
             cout << pixel << " ";
        }
         cout <<  endl;
    }

    cout << "\nLinear Interpolation:" <<endl;
    for (const auto& row : output_linear) {
        for (int pixel : row) {
            cout << pixel << " ";
        }
        cout << endl;
    }

    cout << "\nCubic Interpolation:" << endl;
    for (const auto& row : output_cubic) {
        for (int pixel : row) {
            cout << pixel << " ";
        }
        cout << endl;
    }

    return 0;
}
