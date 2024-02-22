#include "TaskRunner.h"
#include "ImageProcessor.h"
#include <opencv2/opencv.hpp>
#include <iostream>

void TaskRunner::runTask1(const std::string& imageFolder, int kernelSize, int thresholdValue, int maxVal, int thresholdType) {
    cv::VideoCapture cap(0); // Open the default camera
    if (!cap.isOpened()) {
        std::cerr << "Error: Camera could not be opened." << std::endl;
        return;
    }

    ImageProcessor processor;
    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Processed", cv::WINDOW_AUTOSIZE);

    while (true) {
        cv::Mat frame;
        cap >> frame; // Capture a new frame
        if (frame.empty()) break;

        // Convert to grayscale
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        
        // Larger kernel size for more blurring
        // Larger threshold value for more white areas
        // Larger maxVal for brighter white areas
        // Larger thresholdType for different thresholding methods

        // Apply blur and threshold
        cv::Mat blurred = processor.applyBlur(grayFrame, kernelSize);
        cv::Mat thresholded = processor.applyCustomThreshold(blurred, thresholdValue, maxVal);

        // Display the resulting frames
        cv::imshow("Original", frame);
        cv::imshow("Processed", thresholded);

        if (cv::waitKey(30) >= 0) break; // Wait for a keystroke in the window
    }
}
