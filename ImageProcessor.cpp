#include "ImageProcessor.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

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

cv::Mat ImageProcessor::applyDilated(const cv::Mat &inputImage, int dilation_size) {
    cv::Mat dilatedImage;
    // create a structuring element
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1), cv::Point(dilation_size, dilation_size));
    
    cv::dilate(inputImage, dilatedImage, element);
    return dilatedImage;
}

cv::Mat ImageProcessor::applyEroded(const cv::Mat &inputImage, int erosion_size) {
    cv::Mat erodedImage;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1), cv::Point(erosion_size, erosion_size));

    cv::erode(inputImage, erodedImage, element);
    return erodedImage;
}
