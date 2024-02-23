#ifndef ImageProcessor_H
#define ImageProcessor_H

#include <opencv2/core/mat.hpp>

class ImageProcessor {
public:
    // Constructor
    ImageProcessor();

    // Apply Gaussian blur to the input image
    cv::Mat applyBlur(const cv::Mat &inputImage, int kernelSize);

    // Apply thresholding to the input image
    cv::Mat applyCustomThreshold(const cv::Mat &inputImage, int thresholdValue, int maxVal);

    cv::Mat applyDilated(const cv::Mat &inputImage, int dilation_size);

    cv::Mat applyEroded(const cv::Mat &inputImage, int erosion_size);
};

#endif // IMAGEPROCESSOR_H