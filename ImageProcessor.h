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
};

#endif // IMAGEPROCESSOR_H