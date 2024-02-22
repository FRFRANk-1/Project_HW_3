#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    // Load the image
    Mat image = imread("path_to_image.jpg", IMREAD_COLOR);

    // Check if the image is loaded successfully
    if (image.empty()) {
        cout << "Failed to load the image." << endl;
        return -1;
    }

    // Convert the image to grayscale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // Calculate the moments of the image
    Moments moments = moments(grayImage, true);

    // Calculate the centroid of the image
    double cx = moments.m10 / moments.m00;
    double cy = moments.m01 / moments.m00;

    // Calculate the bounding box of the image
    Rect boundingBox = boundingRect(grayImage);

    // Print the results
    cout << "Centroid: (" << cx << ", " << cy << ")" << endl;
    cout << "Bounding Box: (" << boundingBox.x << ", " << boundingBox.y << ", " << boundingBox.width << ", " << boundingBox.height << ")" << endl;

    return 0;
}
