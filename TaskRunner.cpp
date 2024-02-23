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

void TaskRunner::runTask2(const std::string& imagePath, int dilation_size, int erosion_size) {
    // Load the image
    cv::Mat frame = cv::imread(imagePath);
    if (frame.empty()) {
        std::cerr << "Error: Image could not be loaded from " << imagePath << std::endl;
        return;
    }

    ImageProcessor processor;
    cv::namedWindow("Original_thresholded_image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Dilation_image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Erosion_image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Dilated+Eroded", cv::WINDOW_AUTOSIZE);
    
    cv::Mat thresholded = processor.applyCustomThreshold(frame, 125, 255); // Example thresholding

    // Apply dilation and erosion
    cv::Mat dilatedImage = processor.applyDilated(thresholded, dilation_size);
    cv::Mat erodedImage = processor.applyEroded(thresholded, erosion_size);
    cv::Mat dilated_eroded = processor.applyEroded(dilatedImage, erosion_size); 

    // Display the resulting frames
    cv::imshow("Original_thresholded_image", thresholded); // Corrected from "Original"
    cv::imshow("Dilation_image", dilatedImage);
    cv::imshow("Erosion_image", erodedImage);
    cv::imshow("Dilated+Eroded", dilated_eroded);

    // Ensure output directory exists
    std::string outputDir = "D:/NEU study file/5330/Project_HW_3/outputs/";

    // Save the processed images
    cv::imwrite(outputDir + "original_thresholded.jpg", thresholded); // Save the thresholded image as "original" for context
    cv::imwrite(outputDir + "dilated.jpg", dilatedImage);
    cv::imwrite(outputDir + "eroded.jpg", erodedImage);
    cv::imwrite(outputDir + "dilated_eroded.jpg", dilated_eroded);

    // Wait indefinitely until a key is pressed
    cv::waitKey(0);
}
