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

    void ImageProcessor::findConnectedComponents(const cv::Mat &inputImage, cv::Mat &outputImage, int minSize);

    static double calculatePercentFilled(const cv::Mat &stats, int label);
    static double calculateAspectRatio(const cv::Mat &stats, int label);
    
    void ImageProcessor::saveFeatureVector(const std::vector<double>& features, const std::string& label, const std::string& filename);

    std::vector<double> ImageProcessor::extractFeatures(const cv::Mat &inputImage, int minSize);
};  
    
#endif // IMAGEPROCESSOR_H