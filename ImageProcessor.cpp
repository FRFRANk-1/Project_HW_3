#include "ImageProcessor.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <fstream>

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

void ImageProcessor::findConnectedComponents(const cv::Mat &inputImage, cv::Mat &outputImage, int minSize) {
    cv::Mat labels, stats, centroids;

    // std :: cout << "debug_1 inputImage: " << inputImage << std::endl;

    //lables: output label matrix
    //stats: output statistics matrix
    //centroids: output centroids matrix
    int nLabels = cv::connectedComponentsWithStats(inputImage, labels, stats, centroids, 8, CV_32S);
    
    // std :: cout << "debug_2 inputImage: " << inputImage << std::endl;

    std::vector<cv::Vec3b> colors(nLabels);
    colors[0] = cv::Vec3b(0, 0, 0); // background color
    for(int i = 1; i < nLabels; i++) {
        colors[i] = cv::Vec3b(rand() & 255, rand() & 255, rand() & 255); // random color for each label
    }

    outputImage = cv::Mat::zeros(inputImage.size(), CV_8UC3);
    for(int y = 0; y < labels.rows; y++) {
        for(int x = 0; x < labels.cols; x++) {
            int label = labels.at<int>(y, x);
            int area = stats.at<int>(label, cv::CC_STAT_AREA);
            if (area > minSize) {
                outputImage.at<cv::Vec3b>(y, x) = colors[label];
            }
        }
    }

    std::ofstream report("D:/NEU study file/5330/Project_HW_3/Report_Folder/task_3/task3_report.txt");
    report << "Connected Components Report\n\n";

    for (int label = 1; label < nLabels; ++label) {
        int area = stats.at<int>(label, cv::CC_STAT_AREA);
        if (area > minSize) {
            int left = stats.at<int>(label, cv::CC_STAT_LEFT);
            int top = stats.at<int>(label, cv::CC_STAT_TOP);
            int width = stats.at<int>(label, cv::CC_STAT_WIDTH);
            int height = stats.at<int>(label, cv::CC_STAT_HEIGHT);
            cv::Point centroid(
                static_cast<int>(centroids.at<double>(label, 0)),
                static_cast<int>(centroids.at<double>(label, 1))
            );

            // Write the stats for each component to the file
            report << "Component " << label << ":\n";
            report << " - Area: " << area << "\n";
            report << " - Bounding Box: x=" << left << ", y=" << top
                   << ", width=" << width << ", height=" << height << "\n";
            report << " - Centroid: x=" << centroid.x << ", y=" << centroid.y << "\n\n";
        }
    }

    // Close the file
    report.close();
}

double ImageProcessor::calculatePercentFilled(const cv::Mat &stats, int label) {
    int area = stats.at<int>(label, cv::CC_STAT_AREA);
    int bboxwidth = stats.at<int>(label, cv::CC_STAT_WIDTH);
    int bboxheight = stats.at<int>(label, cv::CC_STAT_HEIGHT);
    double bboxArea = bboxwidth * bboxheight; 
    return (area / bboxArea) * 100;
}

double ImageProcessor::calculateAspectRatio(const cv::Mat &stats, int label) {
    int bboxwidth = stats.at<int>(label, cv::CC_STAT_WIDTH);
    int bboxheight = stats.at<int>(label, cv::CC_STAT_HEIGHT);
    return static_cast<double>(bboxwidth) / bboxheight;
}

