#include "ImageProcessor.h"
#include <opencv2/opencv.hpp>

// Constructor
ImageProcessor::ImageProcessor() { }

cv::Mat ImageProcessor:: applyBlur(const cv:: Mat &inputImage, int kernelSize) {
    cv::Mat blurredImage;
    cv::GaussianBlur(inputImage, blurredImage, cv::Size(kernelSize, kernelSize), 0);
    return blurredImage;
}

cv::Mat ImageProcessor::applyCustomThreshold(const cv::Mat &inputImage, int thresholdValue, int maxVal) {
    
    cv::Mat thresholdedImage = inputImage.clone(); // create a copy of input image 
    int rows = thresholdedImage.rows;
    int cols = thresholdedImage.cols;

    // check the image if it is a color image or a grayscale image
    bool isColor = thresholdedImage.type() == CV_8UC3;

    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            if(isColor) {

                cv::Vec3b pixel = thresholdedImage.at<cv::Vec3b>(i, j);
                // convert the pixel to grayscale
                int gray = (pixel[0] + pixel[1] + pixel[2]) / 3;
                // if the gray value is greater than the threshold value, set the pixel to maxVal
                int binaryValue = gray > thresholdValue ? maxVal : 0;
                pixel = cv::Vec3b(binaryValue, binaryValue, binaryValue);
            } else {

                uchar& pixel = thresholdedImage.at<uchar>(i, j);
                pixel = pixel > thresholdValue ? maxVal : 0;
            }
        }
    }
    return thresholdedImage;
}
