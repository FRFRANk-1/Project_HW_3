#include "TaskRunner.h"
#include "ImageProcessor.h"
#include <opencv2/opencv.hpp>
#include <iostream>

void TaskRunner::runTask1(const std::string& imagePath, int kernelSize, int thresholdValue, int maxVal) {
    // Load the image
    cv::Mat frame = cv::imread(imagePath);
    if (frame.empty()) {
        std::cerr << "Error: Image could not be loaded from " << imagePath << std::endl;
        return;
    }

    ImageProcessor processor;
    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Grey", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Blurred", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Threshold", cv::WINDOW_AUTOSIZE);

    // Convert to grayscale
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    
    // Apply blur and custom threshold
    cv::Mat blurred = processor.applyBlur(grayFrame, kernelSize);
    cv::Mat thresholded = processor.applyCustomThreshold(blurred, thresholdValue, maxVal);

    // Display the resulting frames
    cv::imshow("Original", frame);
    cv::imshow("Grey", grayFrame);
    cv::imshow("Threshold", thresholded);
    cv::imshow("Blurred", blurred);

    // Ensure output directory exists
    std::string outputDir = "D:/NEU study file/5330/Project_HW_3/outputs/";

    // Save the processed images
    cv::imwrite(outputDir + "original.jpg", frame);
    cv::imwrite(outputDir + "thresholded_grey.jpg", grayFrame);
    cv::imwrite(outputDir + "blurred.jpg", blurred);
    cv::imwrite(outputDir + "thresholded.jpg", thresholded);


     

    // Wait indefinitely until a key is pressed
    cv::waitKey(0);
}
