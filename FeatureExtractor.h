// ImageProcessor.h
#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/core.hpp>

class ImageProcessor {
public:
    ImageProcessor();
    cv::Mat applyBlur(const cv::Mat &inputImage, int kernelSize = 5);
    cv::Mat applyThreshold(const cv::Mat &inputImage, double threshValue = 127, double maxValue = 255);
};

#endif // IMAGEPROCESSOR_H
